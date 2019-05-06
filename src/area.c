
#include <area.h>

#include "area.h"
#include <stdlib.h>

/* center is expected to be at [0], full size at [1], returns x - size/2 */
float cm_area_reduce_half_size_fn(float const values[], uint16_t values_count, void * priv) {
  (void) priv;
  if (values_count < 2) return 0.0f;
  return values[0] - values[1]/2;
}

struct cm_value_reduce cm_area_reduce_half_size = {
  .reduce_fn = cm_area_reduce_half_size_fn,
  .reduce_data = NULL
};

void cm_area_construct(struct cm_area * area) {
  cm_value_construct(&area->left);
  cm_value_construct(&area->top);
  cm_value_construct(&area->right);
  cm_value_construct(&area->bottom);
  cm_value_construct_reduce(&area->width, cm_reduce_0_minus_1);
  cm_value_construct_reduce(&area->height, cm_reduce_0_minus_1);

  cm_value_construct_average(&area->center.x);
  cm_value_construct_average(&area->center.y);

  cm_value_link_add(&area->center.x, &area->right);
  cm_value_link_add(&area->center.x, &area->left);

  cm_value_link_add(&area->center.y, &area->bottom);
  cm_value_link_add(&area->center.y, &area->top);

  cm_value_link_add(&area->width, &area->right);
  cm_value_link_add(&area->width, &area->left);

  cm_value_link_add(&area->height, &area->bottom);
  cm_value_link_add(&area->height, &area->top);
}

void cm_area_destruct(struct cm_area * area) {
  cm_value_destruct(&area->center.y);
  cm_value_destruct(&area->center.x);
  cm_value_destruct(&area->height);
  cm_value_destruct(&area->width);
  cm_value_destruct(&area->bottom);
  cm_value_destruct(&area->right);
  cm_value_destruct(&area->top);
  cm_value_destruct(&area->left);
}

void
cm_area_construct_set(
  struct cm_area * area,
  float left,
  float top,
  float right,
  float bottom) {
  cm_area_construct(area);
  cm_area_set(area, left, top, right, bottom);
}

void
cm_area_set(struct cm_area * area, float left, float top, float right, float bottom) {
  cm_value_set(&area->left, left);
  cm_value_set(&area->top, top);
  cm_value_set(&area->right, right);
  cm_value_set(&area->bottom, bottom);
}

struct cm_rect cm_area_to_rect(struct cm_area const * area) {
  struct cm_rect result;
  cm_rect_set(&result,
              area->left.absolute,
              area->top.absolute,
              area->right.absolute,
              area->bottom.absolute);
  return result;
}

void cm_area_fill(
  struct cm_area * area,
  struct cm_area * target,
  struct cm_rect offset
) {
  cm_value_link(&area->left, &target->left, offset.left);
  cm_value_link(&area->top, &target->top, offset.top);
  cm_value_link(&area->right, &target->right, offset.right);
  cm_value_link(&area->bottom, &target->bottom, offset.bottom);
}

void cm_area_center_at(
  struct cm_area * area,
  struct cm_value * x,
  struct cm_value * y,
  struct cm_value * width,
  struct cm_value * height
) {
  cm_value_unlink_all_upstream(&area->left);
  cm_value_unlink_all_upstream(&area->top);
  cm_value_unlink_all_upstream(&area->right);
  cm_value_unlink_all_upstream(&area->bottom);

  cm_value_set_reduce(&area->right, cm_reduce_sum);
  cm_value_link_add(&area->right, &area->left);
  cm_value_link_add(&area->right, width);

  cm_value_set_reduce(&area->left, cm_area_reduce_half_size);
  cm_value_link_add(&area->left, x);
  cm_value_link_add(&area->left, width);

  cm_value_set_reduce(&area->bottom, cm_reduce_sum);
  cm_value_link_add(&area->bottom, &area->top);
  cm_value_link_add(&area->bottom, height);

  cm_value_set_reduce(&area->top, cm_area_reduce_half_size);
  cm_value_link_add(&area->top, y);
  cm_value_link_add(&area->top, height);
}


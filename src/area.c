
#include <area.h>

#include "area.h"

float cm_area_reduce_subtract(float const values[], uint16_t value_count) {
  if (value_count < 2) return 0;
  return values[0] - values[1];
}

void cm_area_construct(struct cm_area * area) {
  cm_value_construct(&area->left);
  cm_value_construct(&area->top);
  cm_value_construct(&area->right);
  cm_value_construct(&area->bottom);
  cm_value_construct_reduce(&area->width, cm_area_reduce_subtract);
  cm_value_construct_reduce(&area->height, cm_area_reduce_subtract);

  cm_value_construct_average(&area->center.x);
  cm_value_construct_average(&area->center.y);

  cm_value_link(&area->center.x, &area->right);
  cm_value_link(&area->center.x, &area->left);

  cm_value_link(&area->center.y, &area->bottom);
  cm_value_link(&area->center.y, &area->top);

  cm_value_link(&area->width, &area->left);
  cm_value_link(&area->width, &area->right);

  cm_value_link(&area->height, &area->top);
  cm_value_link(&area->height, &area->bottom);
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

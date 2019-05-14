#include "area.h"
#include "math.h"

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

  cm_area_set_tag(area, " area");
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

int cm_area_render(
  struct cm_area const * area,
  struct cm_tileset const * tileset,
  struct cm_render_queue * queue,
  struct cm_tile center_tile
) {
  float width = cm_value_get(&area->width),
    height = cm_value_get(&area->height);
  struct cm_render_command cmd;
  struct cm_rect target;
  struct cm_rect area_rect;

  if (width < 0.01 || height < 0.01) return 0;

  cm_render_command_construct(&cmd);
  cm_rect_construct(&target);
  area_rect = cm_area_to_rect(area);

  /* flooring is important because of less-than-pixel values */
  area_rect.left = floorf(area_rect.left);
  area_rect.top = floorf(area_rect.top);
  area_rect.right = floorf(area_rect.right);
  area_rect.bottom = floorf(area_rect.bottom);

  /* produce left */
  target.left = area_rect.left;
  target.top = area_rect.top + tileset->tile_height;
  target.right = area_rect.left + tileset->tile_width;
  target.bottom = area_rect.bottom - tileset->tile_height;
  cm_render_command_set_tile(&cmd, cm_tile_left_of(&center_tile), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce top-left, target.left and target.right from left */
  target.top = area_rect.top;
  target.bottom = area_rect.top + tileset->tile_height;
  cm_render_command_set_tile(&cmd, cm_tile_top_left_of(&center_tile), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce top; target.top and target.bottom from top-left */
  target.left = target.right;
  target.right = area_rect.right - tileset->tile_width;
  cm_render_command_set_tile(&cmd, cm_tile_top_of(&center_tile), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce top-right, target.top and target.bottom from top */
  target.left = target.right;
  target.right = area_rect.right;
  cm_render_command_set_tile(&cmd, cm_tile_top_right_of(&center_tile), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce right, target.left and target.right from top-right */
  target.top = target.bottom;
  target.bottom = area_rect.bottom - tileset->tile_height;
  cm_render_command_set_tile(&cmd, cm_tile_right_of(&center_tile), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce bottom-right, target.left and target.right  from right */
  target.top = target.bottom;
  target.bottom = area_rect.bottom;
  cm_render_command_set_tile(&cmd, cm_tile_bottom_right_of(&center_tile), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce bottom, target.top and target.bottom from bottom-right */
  target.left = area_rect.left + tileset->tile_width;
  target.right = area_rect.right - tileset->tile_width;
  cm_render_command_set_tile(&cmd, cm_tile_bottom_of(&center_tile), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce bottom-left, target.top and target.bottom from bottom */
  target.left = area_rect.left;
  target.right = area_rect.left + tileset->tile_width;
  cm_render_command_set_tile(&cmd, cm_tile_bottom_left_of(&center_tile), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce center */
  target.left = area_rect.left + tileset->tile_width;
  target.top = area_rect.top + tileset->tile_height;
  target.right = area_rect.right - tileset->tile_width;
  target.bottom = area_rect.bottom - tileset->tile_height;
  cm_render_command_set_tile(&cmd, center_tile, target);
  cm_render_queue_enqueue(queue, &cmd);

  return 9;
}

#define dv(v, d) ((v) ? (v) : (d))

void cm_area_set_tag(struct cm_area * area, const char tag[5]) {
  char vtag[8] = {
    dv(tag[0], ' '),
    dv(tag[1], ' '),
    dv(tag[2], ' '),
    dv(tag[3], ' '),
    dv(tag[4], ' '), '.', ' ', '\0' };
  vtag[6] = 'l'; cm_value_set_tag(&area->left, vtag);
  vtag[6] = 't'; cm_value_set_tag(&area->top, vtag);
  vtag[6] = 'r'; cm_value_set_tag(&area->right, vtag);
  vtag[6] = 'b'; cm_value_set_tag(&area->bottom, vtag);
  vtag[6] = 'x'; cm_value_set_tag(&area->center.x, vtag);
  vtag[6] = 'y'; cm_value_set_tag(&area->center.y, vtag);
  vtag[6] = 'w'; cm_value_set_tag(&area->width, vtag);
  vtag[6] = 'h'; cm_value_set_tag(&area->height, vtag);
}


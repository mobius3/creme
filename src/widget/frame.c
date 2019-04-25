#include "widget/frame.h"
#include "tileset.h"
#include "render-queue.h"
#include <math.h>

static void cmw_frame_set_area_from_ptr(
  struct cmw_frame * frame,
  struct cm_rect const * area
);

void
cmw_frame_construct_set_area(struct cmw_frame * frame, struct cm_rect area) {
  cmw_frame_construct(frame);
  cmw_frame_set_area_from_ptr(frame, &area);
}

void
cmw_frame_construct(struct cmw_frame * frame) {
  cm_area_construct(&frame->area);
}

void
cmw_frame_set_area(struct cmw_frame * frame, struct cm_rect area) {
  cmw_frame_set_area_from_ptr(frame, &area);
}

void
cmw_frame_set_area_from_ptr(struct cmw_frame * frame, struct cm_rect const * area) {
  cm_value_set(&frame->area.left, area->left);
  cm_value_set(&frame->area.top, area->top);
  cm_value_set(&frame->area.right, area->right);
  cm_value_set(&frame->area.bottom, area->bottom);
}

extern uint16_t cmw_frame_render(
  struct cmw_frame * frame,
  struct cm_tileset const * tileset,
  struct cm_render_queue * queue
) {
  float width = cm_value_get(&frame->area.width),
        height = cm_value_get(&frame->area.height);
  struct cm_render_command cmd;
  struct cm_tile const * center;
  struct cm_rect target;
  struct cm_rect area_rect;

  if (width < 0.01 || height < 0.01) return 0;

  cm_render_command_construct(&cmd);
  cm_rect_construct(&target);
  area_rect = cm_area_to_rect(&frame->area);

  /* flooring is important because of less-than-pixel values */
  area_rect.left = (float) floor((double) area_rect.left);
  area_rect.top = (float) floor((double) area_rect.top);
  area_rect.right = (float) floor((double) area_rect.right);
  area_rect.bottom = (float) floor((double) area_rect.bottom);
  center = &tileset->frame;

  /* TODO: create utiility function to render tiled 'frames' */

  /* produce left */
  target.left = area_rect.left;
  target.top = area_rect.top + tileset->tile_height;
  target.right = area_rect.left + tileset->tile_width;
  target.bottom = area_rect.bottom - tileset->tile_height;
  cm_render_command_set_tile(&cmd, cm_tile_left_of(center), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce top-left, target.left and target.right from left */
  target.top = area_rect.top;
  target.bottom = area_rect.top + tileset->tile_height;
  cm_render_command_set_tile(&cmd, cm_tile_top_left_of(center), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce top; target.top and target.bottom from top-left */
  target.left = target.right;
  target.right = area_rect.right - tileset->tile_width;
  cm_render_command_set_tile(&cmd, cm_tile_top_of(center), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce top-right, target.top and target.bottom from top */
  target.left = target.right;
  target.right = area_rect.right;
  cm_render_command_set_tile(&cmd, cm_tile_top_right_of(center), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce right, target.left and target.right from top-right */
  target.top = target.bottom;
  target.bottom = area_rect.bottom - tileset->tile_height;
  cm_render_command_set_tile(&cmd, cm_tile_right_of(center), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce bottom-right, target.left and target.right  from right */
  target.top = target.bottom;
  target.bottom = area_rect.bottom;
  cm_render_command_set_tile(&cmd, cm_tile_bottom_right_of(center), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce bottom, target.top and target.bottom from bottom-right */
  target.left = area_rect.left + tileset->tile_width;
  target.right = area_rect.right - tileset->tile_width;
  cm_render_command_set_tile(&cmd, cm_tile_bottom_of(center), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce bottom-left, target.top and target.bottom from bottom */
  target.left = area_rect.left;
  target.right = area_rect.left + tileset->tile_width;
  cm_render_command_set_tile(&cmd, cm_tile_bottom_left_of(center), target);
  cm_render_queue_enqueue(queue, &cmd);

  /* produce center */
  target.left = area_rect.left + tileset->tile_width;
  target.top = area_rect.top + tileset->tile_height;
  target.right = area_rect.right - tileset->tile_width;
  target.bottom = area_rect.bottom - tileset->tile_height;
  cm_render_command_set_tile(&cmd, *center, target);
  cm_render_queue_enqueue(queue, &cmd);

  return 9;
}
#include "widget/frame.h"
#include "tileset.h"
#include "render-queue.h"

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
  struct cm_tileset * tileset,
  struct cm_render_queue * queue
) {
  float width = cm_value_get(&frame->area.width),
        height = cm_value_get(&frame->area.height);
  struct cm_render_command cmd;
  struct cm_tile tile;

  cm_render_command_construct(&cmd, cm_render_command__tile);

  if (width < 0.01 || height < 0.01) return 0;
  struct cm_rect area_rect = cm_area_to_rect(&frame->area);
  struct cm_rect top_left_rect = {
    .left = area_rect.left,
    .top = area_rect.top,
    .right = tileset->tile_width,
    .bottom = tileset->tile_height
  };

  cm_render_command_set_tile(&cmd, cm_tile_top_left_of(&tileset->frame), top_left_rect);
  cm_render_queue_enqueue(queue, &cmd);

  return 1;
}
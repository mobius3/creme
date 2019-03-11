
#include <widget/frame.h>

#include "widget/frame.h"

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



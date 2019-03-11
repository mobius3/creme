#ifndef CREME_WIDGET_FRAME_H
#define CREME_WIDGET_FRAME_H

#include "area.h"
#include "rect.h"

#ifdef __cplusplus
extern "C" {
#endif

struct cmw_frame {
  struct cm_area area;
};

extern void cmw_frame_construct_set_area(
  struct cmw_frame * frame,
  struct cm_rect area
);

extern void cmw_frame_construct(
  struct cmw_frame * frame
);

extern void cmw_frame_set_area(struct cmw_frame * frame, struct cm_rect area);

#ifdef __cplusplus
}
#endif

#endif
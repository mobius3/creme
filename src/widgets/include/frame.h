#ifndef CREME_WIDGET_FRAME_H
#define CREME_WIDGET_FRAME_H

#include "creme-core.h"

#ifdef __cplusplus
extern "C" {
#endif

struct cm_tileset;
struct cm_render_queue;

struct cmw_frame
{
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

extern uint16_t cmw_frame_render(
  struct cmw_frame * frame,
  struct cm_tileset const * tileset,
  struct cm_render_queue * queue
);

#ifdef __cplusplus
}
#endif

#endif
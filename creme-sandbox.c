#include <stdio.h>

#include "area.h"
#include "tile.h"

#include "render-queue.h"

#include "widget/frame.h"

struct cm_tileset
{
  struct cm_tile frame;
  struct cm_tile button;
};



int main(int argc, char * argv[]) {
  struct cmw_frame frame;
  struct cm_render_command cmd[128];
  struct cm_render_queue queue;

  cm_render_queue_construct(&queue, cmd, 128);

  cmw_frame_construct_set_area(&frame, cm_rect_make(0, 0, 100, 100));
  return 0;
}
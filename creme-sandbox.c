#include <stdio.h>

#include "area.h"
#include "tile.h"
#include "tileset.h"

#include "render-queue.h"
#include "widget/frame.h"

int main(int argc, char * argv[]) {
  struct cmw_frame frame;
  struct cm_render_command cmd[128];
  struct cm_render_queue queue;

  struct cm_tileset tileset = {
    .frame = {
      .column = 10,
      .row = 10
    },
    .button = {
      .column = 10,
      .row = 10
    },
    .tile_height = 24,
    .tile_width = 24,
    .row_count = 10,
    .column_count = 10
  };

  cm_render_queue_construct(&queue, cmd, 128);
  cmw_frame_construct_set_area(&frame, cm_rect_make(0, 0, 100, 100));
  cmw_frame_render(&frame, &tileset, &queue);

  return 0;
}
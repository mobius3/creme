#ifndef CREME_TILESET_H
#define CREME_TILESET_H

#include "tile.h"

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * A `cm_tileset` structure indicates the center tile in a tileset to
   * render widgets. Widgets usually
   * tell (via their documentation) which tiles it is going to use in a tileset.
   *
   * The most useful information in this structure is the `tile_width` and
   * `tile_height` variables as they are used to calculate target width and
   * height for render commands.
   */
struct cm_tileset {
  struct cm_tile frame;
  struct cm_tile button;

  uint16_t tile_width;
  uint16_t tile_height;
  uint16_t row_count;
  uint16_t column_count;
};

#ifdef __cplusplus
};
#endif

#endif // CREME_TILESET_H
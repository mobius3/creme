#ifndef CREME_TILESET_H
#define CREME_TILESET_H

#include "tile.h"

#ifdef __cplusplus
extern "C" {
#endif

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
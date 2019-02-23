#include "tile.h"

struct cm_tile cm_tile_make(uint16_t column, uint16_t row) {
  struct cm_tile result;
  cm_tile_set(&result, column, row);
  return result;
}

void cm_tile_set(struct cm_tile * tile, uint16_t column, uint16_t row) {
  tile->column = column;
  tile->row = row;
}

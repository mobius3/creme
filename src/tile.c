
#include <tile.h>

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

struct cm_tile cm_tile_left_of(struct cm_tile const * center) {
  struct cm_tile result = cm_tile_make((uint16_t) (center->column - 1),
                                       center->row);
  if (center->column == 0) result.column = 0; //underflow
  return result;
}

struct cm_tile cm_tile_top_left_of(struct cm_tile const * center) {
  struct cm_tile result = cm_tile_make((uint16_t) (center->column - 1),
                                       (uint16_t) (center->row - 1));
  if (center->column == 0) result.column = 0; //underflow
  if (center->row == 0) result.row = 0; //underflow
  return result;
}

struct cm_tile cm_tile_top_of(struct cm_tile const * center) {
  struct cm_tile result = cm_tile_make(center->column,
                                       (uint16_t) (center->row - 1));
  if (center->row == 0) result.row = 0; //underflow
  return result;
}

struct cm_tile cm_tile_top_right_of(struct cm_tile const * center) {
  struct cm_tile result = cm_tile_make((uint16_t) (center->column + 1),
                                       (uint16_t) (center->row - 1));
  if (center->row == 0) result.row = 0; //underflow
  if (result.column < center->column) result.column = center->column; //overflow
  return result;
}

struct cm_tile cm_tile_right_of(struct cm_tile const * center) {
  struct cm_tile result = cm_tile_make((uint16_t) (center->column + 1),
                                       center->row);
  if (result.column < center->column) result.column = center->column; //overflow
  return result;
}

struct cm_tile cm_tile_bottom_right_of(struct cm_tile const * center) {
  struct cm_tile result = cm_tile_make((uint16_t) (center->column + 1),
                                       (uint16_t) (center->row + 1));
  if (result.column < center->column) result.column = center->column; //overflow
  if (result.row < center->row) result.row = center->row; //overflow
  return result;
}

struct cm_tile cm_tile_bottom_of(struct cm_tile const * center) {
  struct cm_tile result = cm_tile_make(center->column,
                                       (uint16_t) (center->row + 1));
  if (result.row < center->row) result.row = center->row; //overflow
  return result;
}

struct cm_tile cm_tile_bottom_left_of(struct cm_tile const * center) {
  struct cm_tile result = cm_tile_make((uint16_t) (center->column - 1),
                                       (uint16_t) (center->row + 1));
  if (center->column == 0) result.column = 0; //underflow
  if (result.row < center->row) result.row = center->row; //overflow
  return result;
}

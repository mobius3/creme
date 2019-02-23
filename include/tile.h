#ifndef CREME_TILE_H
#define CREME_TILE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A cm_tile structure represents a tile in a given tileset at given
 * column and row.
 */
struct cm_tile {
  uint16_t column;
  uint16_t row;
};


/**
 * Constructs a cm_tile and returns it.
 * @param column The column of this tile
 * @param row The row of this tile
 * @return A cm_tile instance
 */
extern struct cm_tile cm_tile_make(uint16_t column, uint16_t row);

/**
 * Sets the value of column and row of a tile.
 * @param tile The cm_tile instance
 * @param column The column of this tile
 * @param row The row of this tile
 */
extern void cm_tile_set(struct cm_tile * tile, uint16_t column, uint16_t row);

#ifdef __cplusplus
}
#endif

#endif //CREME_TILE_H

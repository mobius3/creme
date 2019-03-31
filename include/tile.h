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

/**
 * Creates and returns a tile that is at the left position of a center tile
 * @param center The center tile
 * @return Tile left relative to center
 */
extern struct cm_tile cm_tile_left_of(struct cm_tile const * center);

/**
 * Creates and returns a tile that is at the top-left position of a center tile
 * @param center The center tile
 * @return Tile top-left relative to center
 */
extern struct cm_tile cm_tile_top_left_of(struct cm_tile const * center);

/**
 * Creates and returns a tile that is at the top position of a center tile
 * @param center The center tile
 * @return Tile top relative to center
 */
extern struct cm_tile cm_tile_top_of(struct cm_tile const * center);

/**
 * Creates and returns a tile that is at the top-right position of a center tile
 * @param center The center tile
 * @return Tile top-right relative to center
 */
extern struct cm_tile cm_tile_top_right_of(struct cm_tile const * center);

/**
 * Creates and returns a tile that is at the right position of a center tile
 * @param center The center tile
 * @return Tile right relative to center
 */
extern struct cm_tile cm_tile_right_of(struct cm_tile const * center);

/**
 * Creates and returns a tile that is at the bottom-right position of a center tile
 * @param center The center tile
 * @return Tile bottom-right relative to center
 */
extern struct cm_tile cm_tile_bottom_right_of(struct cm_tile const * center);

/**
 * Creates and returns a tile that is at the bottom position of a center tile
 * @param center The center tile
 * @return Tile bottom relative to center
 */
extern struct cm_tile cm_tile_bottom_of(struct cm_tile const * center);

/**
 * Creates and returns a tile that is at the bottom-left position of a center tile
 * @param center The center tile
 * @return Tile bottom-left relative to center
 */
extern struct cm_tile cm_tile_bottom_left_of(struct cm_tile const * center);

#ifdef __cplusplus
}
#endif

#endif //CREME_TILE_H

#ifndef CREME_TILE_H
#define CREME_TILE_H

#include <stdint.h>
#include "core-exports.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A `cm_tile` structure represents a tile in a given tileset at given
 * column and row.
 */
struct cm_tile {
  uint16_t column;
  uint16_t row;
};


/**
 * Constructs a `cm_tile` value with the column and row passed in
 * and then returns it.
 *
 * @param column The column of this tile
 * @param row The row of this tile
 * @return A `cm_tile` value
 */
CORE_API extern struct cm_tile cm_tile_make(uint16_t column, uint16_t row);

/**
 * Sets the value of `column` and `row` of a `cm_tile` value pointed by `tile`.
 *
 * @param tile A pointer to a `cm_tile` value
 * @param column The column of this tile
 * @param row The row of this tile
 */
CORE_API extern void cm_tile_set(struct cm_tile * tile, uint16_t column, uint16_t row);

/**
 * Creates and returns a `cm_tile` value that is at the
 * left position of a center tile
 *
 * @param center A pointer to a `cm_tile` value representing the center
 * @return A `cm_tile` value with row and column left relative to center
 */
CORE_API extern struct cm_tile cm_tile_left_of(struct cm_tile const * center);

/**
 * Creates and returns a `cm_tile` value that is at the
 * top-left position of a center tile
 *
 * @param center A pointer to a `cm_tile` value representing the center
 * @return A `cm_tile` value with row and column top-left relative to center
 */
CORE_API extern struct cm_tile cm_tile_top_left_of(struct cm_tile const * center);

/**
 * Creates and returns a `cm_tile` value that is at the
 * top position of a center tile
 *
 * @param center A pointer to a `cm_tile` value representing the center
 * @return A `cm_tile` value with row and column top relative to center
 */
CORE_API extern struct cm_tile cm_tile_top_of(struct cm_tile const * center);

/**
 * Creates and returns a `cm_tile` value that is at the
 * top-right position of a center tile
 *
 * @param center A pointer to a `cm_tile` value representing the center
 * @return A `cm_tile` value with row and column top-right relative to center
 */
CORE_API extern struct cm_tile cm_tile_top_right_of(struct cm_tile const * center);

/**
 * Creates and returns a `cm_tile` value that is at the
 * right position of a center tile
 *
 * @param center A pointer to a `cm_tile` value representing the center
 * @return A `cm_tile` value with row and column right relative to center
 */
CORE_API extern struct cm_tile cm_tile_right_of(struct cm_tile const * center);

/**
 * Creates and returns a `cm_tile` value that is at the
 * bottom-right position of a center tile
 *
 * @param center A pointer to a `cm_tile` value representing the center
 * @return A `cm_tile` value with row and column bottom-right relative to center
 */
CORE_API extern struct cm_tile cm_tile_bottom_right_of(struct cm_tile const * center);

/**
 * Creates and returns a `cm_tile` value that is at the
 * bottom position of a center tile
 *
 * @param center A pointer to a `cm_tile` value representing the center
 * @return A `cm_tile` value with row and column bottom relative to center
 */
CORE_API extern struct cm_tile cm_tile_bottom_of(struct cm_tile const * center);

/**
 * Creates and returns a `cm_tile` value that is at the
 * bottom-left position of a center tile
 *
 * @param center A pointer to a `cm_tile` value representing the center
 * @return A `cm_tile` value with row and column bottom-left relative to center
 */
CORE_API extern struct cm_tile cm_tile_bottom_left_of(struct cm_tile const * center);

#ifdef __cplusplus
}
#endif

#endif /* CREME_TILE_H */

#ifndef CREME_RENDER_COMMAND_H
#define CREME_RENDER_COMMAND_H

#include <stdint.h>
#include "tile.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Specifies the type of render command.
 */
enum cm_render_command_type
{
  cm_render_command__tile
};

/**
 * A render command contains the target area and command-specific information
 * to be used as parameters for rendering.
 */
struct cm_render_command
{
  enum cm_render_command_type type;
  union
  {
    /** Tile-rendering specific information */
    struct cm_tile tile;
  };

  /** The target coordinates ("canvas"-wise) Creme expect this to be rendered */
  struct
  {
    float left, top, right, bottom;
  } target;
};

/**
 * Construct a tile render command. This is equivalent to
 * cm_render_command_construct and cm_render_command_set_tile.
 * @param command The cm_render_command instance
 * @param tile_x The x coordinate in the tile set
 * @param tile_y The y coordinate in the tile set
 * @param left The left target coordinate
 * @param top  The top target coordinate
 * @param right The right target coordinate
 * @param bottom The bottom target coordinate
 */
extern void cm_render_command_construct_tile(
  struct cm_render_command * command,
  struct cm_tile tile,
  float left, float top, float right, float bottom);

/**
 * Sets this command as a tile command.
 * @param command The cm_render_command instance
 * @param tile_x The x coordinate in the tile set
 * @param tile_y The y coordinate in the tile set
 * @param left The left target coordinate
 * @param top  The top target coordinate
 * @param right The right target coordinate
 * @param bottom The bottom target coordinate
 */
extern void cm_render_command_set_tile(
  struct cm_render_command * command,
  struct cm_tile tile,
  float left, float top, float right, float bottom);

/**
 * Construct a command with a type. No other value is altered.
 * @param command The cm_render_command instance.
 * @param type The cm_render_command_type instance.
 */
extern void cm_render_command_construct(
  struct cm_render_command * command,
  enum cm_render_command_type type);

#ifdef __cplusplus
}
#endif

#endif //CREME_RENDER_COMMAND_H

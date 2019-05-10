#ifndef CREME_RENDER_COMMAND_H
#define CREME_RENDER_COMMAND_H

#include <stdint.h>
#include "tile.h"
#include "rect.h"
#include "size.h"
#include "core-exports.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Specifies the type of render command.
 */
enum cm_render_command_type {
  cm_render_command__noop,
  cm_render_command__tile,
  cm_render_command__text
};

/**
 * A `cm_render_command` structure contains the target area and command-specific
 * information to be used as parameters for rendering.
 */
struct cm_render_command {
  enum cm_render_command_type type;
  union {
    /** Tile-rendering specific information */
    struct cm_tile tile;

    /** Text-rendering specific information */
    struct {
      struct cm_size size;
      unsigned char const * value;
    } text;
  } data;

  /** The target coordinates ("canvas"-wise) Creme would like you to render to
   * to make things looks as intended. */
  struct cm_rect target;
};

/**
 * Sets a `cm_render_command` value as a tile command.
 *
 * @param command A pointer to a `cm_render_command` value
 * @param tile A `cm_tile` value containing column and row in the tileset
 * @param rect A `cm_rect` value indicating the target rectangle
 */
CORE_API extern void cm_render_command_set_tile(
  struct cm_render_command * command,
  struct cm_tile tile,
  struct cm_rect rect
);

/**
 * Sets a `cm_render_command` value as a text command.
 *
 * @param command A pointer to a `cm_render_command` value
 * @param value A pointer to a constant character array
 * @param size A `cm_size` value representing width and height of the text
 * @param target A `cm_rect` value indicating the target rectangle
 */
CORE_API void cm_render_command_set_text(
  struct cm_render_command * command,
  unsigned char const * value,
  struct cm_size size,
  struct cm_rect target
);

/**
 * Construct a `cm_render_command` value with type being
 * `cm_render_command__noop`. It basically initializes the command with
 * zeroed values.
 *
 * @param command A pointer to a `cm_render_command` value.
 */
CORE_API extern void
cm_render_command_construct(struct cm_render_command * command);

#ifdef __cplusplus
}
#endif

#endif /* CREME_RENDER_COMMAND_H */

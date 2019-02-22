#include "render-command.h"

void cm_render_command_construct(
  struct cm_render_command * command,
  enum cm_render_command_type type) {
  command->type = type;
}


void
cm_render_command_construct_set_tile(
  struct cm_render_command * command,
  uint16_t tile_x,
  uint16_t tile_y,
  float left,
  float top,
  float right,
  float bottom)
{
  command->type = cm_render_command__tile;
  command->target.left = left;
  command->target.top = top;
  command->target.right = right;
  command->target.bottom = bottom;
  command->tile.x = tile_x;
  command->tile.y = tile_y;
}


void
cm_render_command_construct_tile(
  struct cm_render_command * command,
  uint16_t tile_x,
  uint16_t tile_y,
  float left,
  float top,
  float right,
  float bottom)
{
  cm_render_command_construct(command, cm_render_command__tile);
  cm_render_command_set_tile(
    command,
    tile_x,
    tile_y,
    left, top, right, bottom
    );
}

#include "render-command.h"

void cm_render_command_construct(
  struct cm_render_command * command,
  enum cm_render_command_type type) {
  command->type = type;
  cm_rect_construct(&command->target, 0, 0, 0, 0);
  command->tile.column = 0;
  command->tile.row = 0;
}


void
cm_render_command_construct_set_tile(
  struct cm_render_command * command,
  struct cm_tile tile,
  struct cm_rect rect)
{
  command->type = cm_render_command__tile;
  command->target = rect;
  command->tile = tile;
}


void
cm_render_command_construct_tile(
  struct cm_render_command * command,
  struct cm_tile tile,
  struct cm_rect rect)
{
  cm_render_command_construct(command, cm_render_command__tile);
  cm_render_command_set_tile(
    command,
    tile,
    rect
    );
}

#include "render-command.h"

void cm_render_command_construct(struct cm_render_command * command) {
  command->type = cm_render_command__noop;
  cm_rect_set(&command->target, 0, 0, 0, 0);
  command->tile.column = 0;
  command->tile.row = 0;
}

void
cm_render_command_set_tile(
  struct cm_render_command * command,
  struct cm_tile tile,
  struct cm_rect rect)
{
  command->type = cm_render_command__tile;
  command->target = rect;
  command->tile = tile;
}

#include "render-command.h"

void cm_render_command_construct(
  struct cm_render_command * command,
  enum cm_render_command_type type) {
  command->type = type;
}


void
cm_render_command_construct_set_tile(
  struct cm_render_command * command,
  struct cm_tile tile,
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
  command->tile = tile;
}


void
cm_render_command_construct_tile(
  struct cm_render_command * command,
  struct cm_tile tile,
  float left,
  float top,
  float right,
  float bottom)
{
  cm_render_command_construct(command, cm_render_command__tile);
  cm_render_command_set_tile(
    command,
    tile,
    left, top, right, bottom
    );
}

#include "render-queue.h"
#include "render-command.h"
#include "tileset.h"
#include "render.h"
#include "SDL.h"


static void render_tile(
  struct cm_render_command const * command,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture);

void
cmx_sdl2_render(
  struct cm_render_queue * queue,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture) {

  struct cm_render_command cmd;

  while (!cm_render_queue_is_empty(queue)) {
    cm_render_queue_dequeue(queue, &cmd);
    switch (cmd.type) {
      case cm_render_command__tile:
        render_tile(&cmd, tileset, renderer, tileset_texture);
        break;
      default:
        break;
    }
  }
}

void render_tile(
  struct cm_render_command const * command,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture) {
  SDL_Rect src = {
    .x = command->tile.column * tileset->tile_width,
    .y = command->tile.row * tileset->tile_height,
    .w = tileset->tile_width,
    .h = tileset->tile_height
  };
  SDL_Rect dst = {
    .x = (int) command->target.left,
    .y = (int) command->target.top,
    .w = (int) cm_rect_width(&command->target),
    .h = (int) cm_rect_height(&command->target)
  };
  SDL_RenderCopy(renderer, tileset_texture, &src, &dst);
}

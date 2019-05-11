#include "command-rendering.h"
#include "renderer.h"

void cmx_sdl2_render_text_command(
  struct cm_render_command const * command,
  struct cmx_truetype_font const * font,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * font_texture
) {
  cmx_sdl2_render_text(
    renderer,
    font, font_texture,
    command->target,
    command->data.text.value
  );
}

void cmx_sdl2_render_tile_command(
  struct cm_render_command const * command,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture
) {
  SDL_Rect src = {
    .x = command->data.tile.column * tileset->tile_width,
    .y = command->data.tile.row * tileset->tile_height,
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


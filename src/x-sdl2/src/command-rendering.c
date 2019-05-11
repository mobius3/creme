#include "command-rendering.h"

void cmx_sdl2_render_text_command(
  struct cm_render_command const * command,
  struct cmx_truetype_font const * font,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * font_texture
) {
  unsigned char const * text = command->data.text.value;
  size_t len = strlen((char const *) text);
  struct cmx_truetype_character_mapping * mapping = malloc(
    (len + 1) * sizeof(*mapping));
  SDL_Rect src, dst;

  cmx_truetype_font_render(font, (uint8_t *) command->data.text.value, len, mapping);
  for (size_t i = 0; i < len +1; i++) {
    src.x = (int) (mapping[i].source.left * font->pixels.dimensions.width);
    src.y = (int) (mapping[i].source.top * font->pixels.dimensions.height);
    src.w = (int) (cm_rect_width(&mapping[i].source) * font->pixels.dimensions.width);
    src.h = (int) (cm_rect_height(&mapping[i].source) * font->pixels.dimensions.height);
    dst.x = (int) (mapping[i].target.left + command->target.left);
    dst.y = (int) (mapping[i].target.top + command->target.top);
    dst.w = (int) cm_rect_width(&mapping[i].target);
    dst.h = (int) cm_rect_height(&mapping[i].target);
    SDL_RenderCopy(renderer, font_texture, &src, &dst);
  }
  free(mapping);
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


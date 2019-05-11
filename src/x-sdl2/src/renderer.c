#include "renderer.h"
#include "creme-core.h"
#include "SDL.h"

struct SDL_Renderer * cmx_sdl2_renderer_make(struct SDL_Window * window,
                                             struct cm_color color) {
  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  cmx_sdl2_renderer_set_color(renderer, color);
  return renderer;
}

struct cm_color cmx_sdl2_renderer_get_color(SDL_Renderer * renderer) {
  struct cm_color color;
  SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
  return color;
}

void
cmx_sdl2_renderer_set_color(SDL_Renderer * renderer, struct cm_color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void cmx_sdl2_render_text(
  SDL_Renderer * renderer,
  struct cmx_truetype_font const * font,
  SDL_Texture * font_texture,
  struct cm_rect target,
  unsigned char const * text
) {
  size_t len = strlen((char const *) text);
  struct cmx_truetype_character_mapping * mapping = malloc(
    (len + 1) * sizeof(*mapping));
  SDL_Rect src, dst;

  cmx_truetype_font_render(font, text, len, mapping);
  for (size_t i = 0; i < len + 1; i++) {
    src.x = (int) (mapping[i].source.left * font->pixels.dimensions.width);
    src.y = (int) (mapping[i].source.top * font->pixels.dimensions.height);
    src.w = (int) (cm_rect_width(&mapping[i].source) *
                   font->pixels.dimensions.width);
    src.h = (int) (cm_rect_height(&mapping[i].source) *
                   font->pixels.dimensions.height);
    dst.x = (int) (mapping[i].target.left + target.left);
    dst.y = (int) (mapping[i].target.top + target.top);
    dst.w = (int) cm_rect_width(&mapping[i].target);
    dst.h = (int) cm_rect_height(&mapping[i].target);
    SDL_RenderCopy(renderer, font_texture, &src, &dst);
  }
  free(mapping);
}

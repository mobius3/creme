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

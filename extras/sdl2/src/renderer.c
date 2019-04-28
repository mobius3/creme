#include "renderer.h"
#include "SDL.h"

struct SDL_Renderer * cmx_sdl2_renderer_make(struct SDL_Window * window) {
  return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

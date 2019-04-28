#include "window.h"
#include "SDL.h"


SDL_Window * cmx_sdl2_window_make(char const * title, struct cm_size size) {
  return SDL_CreateWindow(
    title,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    (int) size.width,
    (int) size.height,
    SDL_WINDOW_RESIZABLE
  );
}

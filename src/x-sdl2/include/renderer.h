#ifndef CREME_EXTRAS_SDL2_RENDERER_H
#define CREME_EXTRAS_SDL2_RENDERER_H

#include "SDL.h"
#include "color.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct SDL_Renderer * cmx_sdl2_renderer_make(
  struct SDL_Window * window,
  struct cm_color color
);

extern struct cm_color cmx_sdl2_renderer_get_color(SDL_Renderer * renderer);
extern void cmx_sdl2_renderer_set_color(
  SDL_Renderer * renderer,
  struct cm_color color
);

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_SDL2_RENDERER_H */

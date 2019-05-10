#ifndef CREME_EXTRAS_SDL2_RENDERER_H
#define CREME_EXTRAS_SDL2_RENDERER_H

#include "creme-core.h"
#include "SDL.h"
#include "x-sdl2-exports.h"

#ifdef __cplusplus
extern "C" {
#endif

X_SDL2_API extern struct SDL_Renderer * cmx_sdl2_renderer_make(
  struct SDL_Window * window,
  struct cm_color color
);

X_SDL2_API extern struct cm_color cmx_sdl2_renderer_get_color(SDL_Renderer * renderer);
X_SDL2_API extern void cmx_sdl2_renderer_set_color(
  SDL_Renderer * renderer,
  struct cm_color color
);

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_SDL2_RENDERER_H */

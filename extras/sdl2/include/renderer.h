#ifndef CREME_EXTRAS_SDL2_RENDERER_H
#define CREME_EXTRAS_SDL2_RENDERER_H

#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct SDL_Renderer * cmx_sdl2_renderer_make(
  struct SDL_Window * window
);

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_SDL2_RENDERER_H */

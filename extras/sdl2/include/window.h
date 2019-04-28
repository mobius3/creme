
#ifndef CREME_EXTRAS_SDL2_WINDOW_H
#define CREME_EXTRAS_SDL2_WINDOW_H

#include "size.h"
#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif

extern SDL_Window * cmx_sdl2_window_make(char const * title, struct cm_size size);

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_SDL2_WINDOW_H */

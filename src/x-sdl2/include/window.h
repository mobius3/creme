
#ifndef CREME_EXTRAS_SDL2_WINDOW_H
#define CREME_EXTRAS_SDL2_WINDOW_H

#include "creme-core.h"
#include "SDL.h"
#include "x-sdl2-exports.h"

#ifdef __cplusplus
extern "C" {
#endif

X_SDL2_API extern SDL_Window * cmx_sdl2_window_make(char const * title, struct cm_size size);

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_SDL2_WINDOW_H */

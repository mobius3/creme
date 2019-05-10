#ifndef CREME_EXTRAS_SDL2_TEXTURE_H
#define CREME_EXTRAS_SDL2_TEXTURE_H

#include "creme-core.h"
#include "SDL.h"
#include "x-sdl2-exports.h"

#ifdef __cplusplus
extern "C" {
#endif

X_SDL2_API extern SDL_Texture * cmx_sdl2_texture_make_from_image_data(
  SDL_Renderer * renderer,
  unsigned char const * image_data,
  size_t image_data_size
);

X_SDL2_API extern SDL_Texture * cmx_sdl2_texture_make_from_pixel_data(
  SDL_Renderer * renderer,
  unsigned char * pixel_data,
  struct cm_size dimensions
);

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_SDL2_TEXTURE_H */

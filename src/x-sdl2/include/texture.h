#ifndef CREME_EXTRAS_SDL2_TEXTURE_H
#define CREME_EXTRAS_SDL2_TEXTURE_H

#include "SDL.h"
#include "size.h"

#ifdef __cplusplus
extern "C" {
#endif

extern SDL_Texture * cmx_sdl2_texture_make_from_image_data(
  SDL_Renderer * renderer,
  unsigned char const * image_data,
  size_t image_data_size
);

extern SDL_Texture * cmx_sdl2_texture_make_from_pixel_data(
  SDL_Renderer * renderer,
  unsigned char * pixel_data,
  struct cm_size dimensions
);

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_SDL2_TEXTURE_H */

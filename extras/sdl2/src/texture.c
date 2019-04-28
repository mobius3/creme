#include "texture.h"
#include "stb_image.h"

SDL_Texture * cmx_sdl2_texture_make_from_image_data(
  SDL_Renderer * renderer,
  unsigned char const * image_data,
  size_t image_data_size
) {
  int x, y;
  unsigned char * pixels = stbi_load_from_memory(
    image_data, image_data_size, &x, &y,
    NULL, 4
  );
  SDL_Texture * result = cmx_sdl2_texture_make_from_pixel_data(
    renderer,
    pixels,
    cm_size_make(x, y)
  );
  stbi_image_free(pixels);
  return result;
}

SDL_Texture * cmx_sdl2_texture_make_from_pixel_data(
  SDL_Renderer * renderer,
  unsigned char * pixel_data,
  struct cm_size dimensions
) {

  Uint32 rmask, gmask, bmask, amask;
  int x = (int) dimensions.width, y = (int) dimensions.height;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  SDL_Surface * surface = SDL_CreateRGBSurfaceFrom(
    (void *) pixel_data,
    x, y, 32, x * 4, rmask, gmask, bmask, amask
  );
  SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);

  if (surface == NULL) {
    return NULL;
  }

  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture != NULL) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  }
  SDL_FreeSurface(surface);
  return texture;
}

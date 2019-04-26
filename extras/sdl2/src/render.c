#include "stb_image.h"
#include "render-queue.h"
#include "render-command.h"
#include "tileset.h"
#include "render.h"
#include "SDL.h"

static void render_tile(
  struct cm_render_command const * command,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture);

void
cmx_sdl2_render(
  struct cm_render_queue * queue,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture) {

  struct cm_render_command cmd;

  while (!cm_render_queue_is_empty(queue)) {
    cm_render_queue_dequeue(queue, &cmd);
    switch (cmd.type) {
      case cm_render_command__tile:
        render_tile(&cmd, tileset, renderer, tileset_texture);
        break;
      default:
        break;
    }
  }
}

void render_tile(
  struct cm_render_command const * command,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture) {
  SDL_Rect src = {
    .x = command->tile.column * tileset->tile_width,
    .y = command->tile.row * tileset->tile_height,
    .w = tileset->tile_width,
    .h = tileset->tile_height
  };
  SDL_Rect dst = {
    .x = (int) command->target.left,
    .y = (int) command->target.top,
    .w = (int) cm_rect_width(&command->target),
    .h = (int) cm_rect_height(&command->target)
  };
  SDL_RenderCopy(renderer, tileset_texture, &src, &dst);
}


struct SDL_Texture *
cmx_sdl2_texture_from_bytes(
  SDL_Renderer * renderer,
  unsigned char const * bytes,
  unsigned int length
) {
  int x, y;
  unsigned char * image_data = stbi_load_from_memory(bytes, length, &x, &y,
                                                     NULL, 4);
  Uint32 rmask, gmask, bmask, amask;

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
    image_data,
    x, y, 32, x * 4, rmask, gmask, bmask, amask
  );
  SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);

  if (surface == NULL) {
    stbi_image_free(image_data);
    return NULL;
  }

  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture != NULL) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  }
  stbi_image_free(image_data);
  SDL_FreeSurface(surface);
  return texture;
}

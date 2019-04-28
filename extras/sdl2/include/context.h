#ifndef CREME_EXTRAS_SDL2_CONTEXT_H
#define CREME_EXTRAS_SDL2_CONTEXT_H

#include "tileset.h"
#include "area.h"
#include "render-queue.h"
#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif

struct cmx_sdl2_context {
  SDL_Window * window;
  SDL_Renderer * renderer;
  SDL_Texture * tileset_texture;
  struct cm_tileset tileset;
  struct cm_area area;
  struct cm_render_queue queue;

  struct cm_value * left, * top, * right, * bottom, * center;
};

extern void cmx_sdl2_context_init(struct cmx_sdl2_context * context);
extern void cmx_sdl2_context_update(struct cmx_sdl2_context * context);
extern void cmx_sdl2_context_render(struct cmx_sdl2_context * context);
extern void cmx_sdl2_context_destruct(struct cmx_sdl2_context * context);

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_SDL2_CONTEXT_H */

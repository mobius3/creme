#ifndef CREME_EXTRAS_SDL2_RENDERER_H
#define CREME_EXTRAS_SDL2_RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

struct SDL_Renderer;
struct SDL_Texture;
struct cm_render_queue;
struct cm_tileset;

extern void cmx_sdl2_render(
  struct cm_render_queue * queue,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture);

extern struct SDL_Texture *
cmx_sdl2_texture_from_bytes(
  struct SDL_Renderer * renderer,
  unsigned char const * bytes,
  unsigned int length
);

#ifdef __cplusplus
};
#endif

#endif /* CREME_EXTRAS_SDL2_RENDERER_H */

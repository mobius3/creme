#ifndef CREME_EXTRAS_SDL2_RENDERER_H
#define CREME_EXTRAS_SDL2_RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

struct SDL2_Renderer;
struct cm_render_queue;

void cmx_sdl2_render(
  struct SDL2_Renderer * renderer,
  struct cm_render_queue * queue);

#ifdef __cplusplus
};
#endif

#endif //CREME_EXTRAS_SDL2_RENDERER_H

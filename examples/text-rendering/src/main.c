#include "SDL.h"
#include "c-rez/tilesets.h"

#include "widget/frame.h"
#include "cmx-sdl2.h"

int main(int argc, const char * argv[]) {
  /* initializes SDL2. */
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  /* initializes the cmx_sdl2_context value */
  struct cm_render_command buffer[256];
  struct cmx_sdl2_context context = {
    .window = cmx_sdl2_window_make("cmex: text-rendering", cm_size_make(320, 240)),
    .renderer = cmx_sdl2_renderer_make(context.window, cm_color_blue),
    .tileset_texture = NULL,
    .queue = cm_render_queue_make(buffer, 256),
    .tileset = {}
  };

  /* this initializes other stuff that can't be initialized as above */
  cmx_sdl2_context_init(&context);

  /* main program loop */
  while (!SDL_QuitRequested()) {
    SDL_Delay(16);

    cmx_sdl2_context_update(&context);
    cm_render_queue_flush(&context.queue);
    SDL_RenderClear(context.renderer);
    cmx_sdl2_context_render(&context);
    SDL_RenderPresent(context.renderer);
  }

  cmx_sdl2_context_destruct(&context);
  SDL_Quit();
  return 0;
}

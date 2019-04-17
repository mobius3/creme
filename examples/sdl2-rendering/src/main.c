
#include <render.h>
#include "widget/frame.h"
#include "render-queue.h"
#include "tileset.h"
#include "state.h"

#include "SDL.h"
#include "c-rez/tilesets.h"
#include "stb_image.h"


int main(int argc, const char * argv[]) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  struct cmex_sdl2_state state;

  cmex_sdl2_state_construct(
    &state,
    cm_rect_make(0, 0, 320, 240),
    "A SDL2 Rendering example"
  );

  struct cm_tileset tileset = {
    .tile_height = 8,
    .tile_width = 8,
    .column_count = 80,
    .row_count = 50,
    .frame = {
      .column = 4,
      .row = 4
    }
  };

  cmex_sdl2_state_load_tileset(&state, tilesets_kiwi_png.data,
                               tilesets_kiwi_png.length);

  struct cmw_frame frame1;
  cmw_frame_construct(&frame1);
  cm_value_link(&frame1.area.right, &state.area.right);
  cm_value_link(&frame1.area.bottom, &state.area.bottom);

  cm_value_offset_set(&frame1.area.left, -100);
  cm_value_link(&frame1.area.left, &frame1.area.right);

  cm_value_offset_set(&frame1.area.top, -100);
  cm_value_link(&frame1.area.top, &frame1.area.bottom);

  struct cmw_frame frame2;
  cmw_frame_construct(&frame2);

  cm_value_offset_set(&frame2.area.right, 50);
  cm_value_link(&frame2.area.right, &frame1.area.left);

  cm_value_offset_set(&frame2.area.bottom, 50);
  cm_value_link(&frame2.area.bottom, &frame1.area.top);

  cm_value_offset_set(&frame2.area.top, -100);
  cm_value_link(&frame2.area.top, &frame2.area.bottom);

/*  cm_value_offset_set(&frame2.area.left, -100); */
  cm_value_link(&frame2.area.left, &state.area.left);

  struct cm_render_command buffer[256];
  struct cm_render_queue queue;
  cm_render_queue_construct(&queue, buffer, 256);

  while (!SDL_QuitRequested()) {
    SDL_Delay(16);

    cmex_sdl2_state_update(&state);
    cm_render_queue_flush(&queue);
    cmw_frame_render(&frame1, &tileset, &queue);
    cmw_frame_render(&frame2, &tileset, &queue);

    SDL_RenderClear(state.sdl_renderer);

    cmx_sdl2_render(&queue, &tileset, state.sdl_renderer, state.tileset_texture);

    SDL_RenderPresent(state.sdl_renderer);
  }

  cmex_sdl2_state_destruct(&state);
  SDL_Quit();
  return 0;
}

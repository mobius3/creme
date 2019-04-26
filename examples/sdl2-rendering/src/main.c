
#include <render.h>
#include "widget/frame.h"
#include "render-queue.h"
#include "tileset.h"
#include "state.h"

#include "SDL.h"
#include "c-rez/tilesets.h"


int main(int argc, const char * argv[]) {
  struct cmex_sdl2_state state;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

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
      .column = 1,
      .row = 1
    }
  };


  /* creates four frames */
  struct cmw_frame top_left;
  struct cmw_frame top_right;
  struct cmw_frame bottom_right;
  struct cmw_frame bottom_left;

  /* initializes state */
  cmex_sdl2_state_load_tileset(&state, tilesets_kiwi_png.data,
                               tilesets_kiwi_png.length);

  /* construct frames */
  cmw_frame_construct(&top_left);
  cmw_frame_construct(&top_right);
  cmw_frame_construct(&bottom_right);
  cmw_frame_construct(&bottom_left);

  /* link frames */
  cm_value_link(&top_left.area.left, &state.area.left);
  cm_value_link(&top_left.area.top, &state.area.top);
  cm_value_link(&top_left.area.right, &state.area.center.x);
  cm_value_link(&top_left.area.bottom, &state.area.center.y);

  cm_value_link(&top_right.area.left, &top_left.area.right);
  cm_value_link(&top_right.area.top, &state.area.top);
  cm_value_link(&top_right.area.right, &state.area.right);
  cm_value_link(&top_right.area.bottom, &state.area.center.y);

  cm_value_link(&bottom_right.area.left, &state.area.center.x);
  cm_value_link(&bottom_right.area.top, &top_left.area.bottom);
  cm_value_link(&bottom_right.area.right, &state.area.right);
  cm_value_link(&bottom_right.area.bottom, &state.area.bottom);

  cm_value_link(&bottom_left.area.left, &state.area.left);
  cm_value_link(&bottom_left.area.top, &state.area.center.y);
  cm_value_link(&bottom_left.area.right, &bottom_right.area.left);
  cm_value_link(&bottom_left.area.bottom, &state.area.bottom);

  struct cm_render_command buffer[256];
  struct cm_render_queue queue;
  cm_render_queue_construct(&queue, buffer, 256);

  while (!SDL_QuitRequested()) {
    SDL_Delay(16);

    cmex_sdl2_state_update(&state);
    cm_render_queue_flush(&queue);

    cmw_frame_render(&top_left, &tileset, &queue);
    cmw_frame_render(&top_right, &tileset, &queue);
    cmw_frame_render(&bottom_right, &tileset, &queue);
    cmw_frame_render(&bottom_left, &tileset, &queue);

    SDL_RenderClear(state.sdl_renderer);

    cmx_sdl2_render(&queue, &tileset, state.sdl_renderer, state.tileset_texture);

    SDL_RenderPresent(state.sdl_renderer);
  }

  cmex_sdl2_state_destruct(&state);
  SDL_Quit();
  return 0;
}

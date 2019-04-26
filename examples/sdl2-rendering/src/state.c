
#include "render.h"
#include "state.h"
#include "SDL.h"

void cmex_sdl2_state_construct(
  struct cmex_sdl2_state * state,
  struct cm_rect bounds,
  char const title[]
) {
  SDL_Rect window_rect = {
    .w = (int) cm_rect_width(&bounds),
    .h = (int) cm_rect_height(&bounds),
    .x = SDL_WINDOWPOS_CENTERED,
    .y = SDL_WINDOWPOS_CENTERED
  };

  SDL_Window * sdl_window = SDL_CreateWindow(
    title,
    window_rect.x, window_rect.y,
    window_rect.w, window_rect.h,
    SDL_WINDOW_RESIZABLE
  );

  SDL_Renderer * sdl_renderer = SDL_CreateRenderer(
    sdl_window,
    0,
    SDL_RENDERER_ACCELERATED
  );

  SDL_SetRenderDrawColor(sdl_renderer, 38, 43, 51, 0xFF);
  SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
  SDL_GetWindowSize(state->sdl_window, &window_rect.w, &window_rect.h);

  state->sdl_renderer = sdl_renderer;
  state->sdl_window = sdl_window;
  cm_area_construct(&state->area);
  cm_area_set(&state->area, 0, 0,
              (float) window_rect.w,
              (float) window_rect.h
  );
  state->tileset_texture = NULL;
}

void cmex_sdl2_state_destruct(struct cmex_sdl2_state * state) {
  if (state->tileset_texture != NULL) {
    SDL_DestroyTexture(state->tileset_texture);
    state->tileset_texture = NULL;
  }
  SDL_DestroyRenderer(state->sdl_renderer);
  SDL_DestroyWindow(state->sdl_window);
}

void cmex_sdl2_state_update(struct cmex_sdl2_state * state) {
  int window_w, window_h;
  SDL_GetWindowSize(state->sdl_window, &window_w, &window_h);
  cm_value_set(&state->area.right, (float) window_w);
  cm_value_set(&state->area.bottom, (float) window_h);

  SDL_PumpEvents();
}

void cmex_sdl2_state_load_tileset(
  struct cmex_sdl2_state * state,
  unsigned char const * data, int length
) {
  if (state->tileset_texture != NULL)
    SDL_DestroyTexture(state->tileset_texture);

  state->tileset_texture = cmx_sdl2_texture_from_bytes(
    state->sdl_renderer,
    data,
    length);
}
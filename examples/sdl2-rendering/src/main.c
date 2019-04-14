
#include "state.h"

#include "SDL.h"

int main(int argc, const char * argv[]) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  struct cmex_sdl2_state state;
  cmex_sdl2_state_construct(
    &state,
    cm_rect_make(0, 0, 320, 240),
    "A SDL2 Rendering example"
  );

  while (!SDL_QuitRequested()) {
    SDL_Delay(16);

    cmex_sdl2_state_update(&state);

    SDL_RenderClear(state.sdl_renderer);
    SDL_RenderPresent(state.sdl_renderer);
  }

  cmex_sdl2_state_destruct(&state);
  SDL_Quit();
}


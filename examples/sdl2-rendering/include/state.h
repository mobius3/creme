#ifndef CREME_EXAMPLE_SDL2_RENDERING_STATE_H
#define CREME_EXAMPLE_SDL2_RENDERING_STATE_H

#include "rect.h"
#include "area.h"

struct SDL_Window;
struct SDL_Renderer;

/**
 * This struct holds important variables about the example state, including
 * SDL's state.
 */
struct cmex_sdl2_state
{
  struct SDL_Window * sdl_window;
  struct SDL_Renderer * sdl_renderer;
  struct cm_area window_area;
};

/**
 * Constructs a `cmex_sdl2_state` value.
 *
 * This mainly initializes SDL, loads all assets and sets default options.
 * @param state The state to construct
 * @sa state_destruct
 */
void cmex_sdl2_state_construct(
  struct cmex_sdl2_state * state,
  struct cm_rect bounds,
  char const title[]
);

/**
 * Destructs a `cmex_sdl2_state` value.
 *
 * It closes and destroy the SDL window and renderer, free all resources.
 * @param state The state to destruct
 */
void cmex_sdl2_state_destruct(struct cmex_sdl2_state * state);

/**
 * Pumps input and also checks for new window size.
 * @param state The state to update
 */
void cmex_sdl2_state_update(struct cmex_sdl2_state * state);

#endif /* CREME_EXAMPLE_SDL2_RENDERING_STATE_H */

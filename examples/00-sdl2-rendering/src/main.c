/* Creme 00-sdl2-rendering example
 *
 * This example shows how to integrate your program with creme::x-sdl2 library.
 * You still need to link your program against SDL2 (and SDLmain if you are on
 * windows).
 */

#include "SDL.h"
#include "c-rez/tilesets.h"
#include "creme-core.h"
#include "creme-widgets.h"
#include "creme-x-sdl2.h"

int main(int argc, char * argv[]) {

  /* initializes SDL2. creme::x-sdl does not initialize nor quits SDL */
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  /* initializes the cmx_sdl2_context value with its relevant variables.
   * with the exception of the context.area variable, all other fields should
   * be initialized by you.
   *
   * creme::x-sdl2 has helper functions to aid in render/window creation and
   * texture loading. you should free them later as well. */
  struct cm_render_command buffer[256];
  struct cmx_sdl2_context context = {
    .window = cmx_sdl2_window_make(
      "cmex: 00-sdl2-rendering",
      cm_size_make(320, 240)
    ),
    .renderer = cmx_sdl2_renderer_make(
      context.window,
      cm_color_0x_rgb(0xEEE8D5)
    ),
    .tileset_texture = cmx_sdl2_texture_make_from_image_data(
      context.renderer, tilesets_kiwi_png.data, tilesets_kiwi_png.length
    ),
    .queue = cm_render_queue_make(buffer, 256),
    .tileset = {
      .tile_height = 8,
      .tile_width = 8,
      .column_count = 80,
      .row_count = 50,
      .frame = {
        .column = 1,
        .row = 1
      }
    }
  };

  /* this initializes other stuff that can't be initialized as above. calling
   * this is mandatory. */
  cmx_sdl2_context_init(&context);

  /* creates and constructs a frame widget and makes its edges anchored
   * at window edges with 10px inset */
  struct cmw_frame frame;
  cmw_frame_construct(&frame);
  cm_area_fill(
    &frame.area,
    &context.area,
    cm_rect_make_inset_of(&cm_rect_zero, 10)
  );

  /* main program loop */
  while (!SDL_QuitRequested()) {
    SDL_Delay(16);
    SDL_RenderClear(context.renderer);

    cmx_sdl2_context_update(&context); /* pump events and update window size */
    cm_render_queue_flush(&context.queue); /* empty the render queue */

    /* enqueues all rendering commands for this cmw_frame into the queue */
    cmw_frame_render(&frame, &context.tileset, &context.queue);

    /* for every enqueued command in context.queue, processes and renders it */
    cmx_sdl2_context_render(&context);

    SDL_RenderPresent(context.renderer);
  }

  cmx_sdl2_context_destruct(&context);
  SDL_Quit();

  /* removes unused warnings */
  (void) argc;
  (void) argv;

  return 0;
}

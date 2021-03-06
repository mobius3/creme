#include "SDL.h"
#include "c-rez/tilesets.h"
#include "creme-core.h"
#include "creme-widgets.h"
#include "creme-x-sdl2.h"

int main(int argc, char * argv[]) {
  (void) argc;
  (void) argv;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  struct cm_render_command buffer[256];
  struct cmx_sdl2_context context = {
    .window = cmx_sdl2_window_make("cmex: 00-sdl2-rendering", cm_size_make(320, 240)),
    .renderer = cmx_sdl2_renderer_make(context.window, cm_color_make(238, 232, 213, 0)),
    .tileset_texture = cmx_sdl2_texture_make_from_image_data(
      context.renderer, tilesets_creme_png.data, tilesets_creme_png.length
    ),
    .queue = cm_render_queue_make(buffer, 256),
    .tileset = {
      .tile_height = 16,
      .tile_width = 16,
      .column_count = 512/16,
      .row_count = 512/16,
      .frame = {
        .column = 1,
        .row = 1
      }
    }
  };
  /* this initializes other stuff that can't be initialized as above */
  cmx_sdl2_context_init(&context);

  /* creates and constructs four frame widgets */
  struct cmw_frame top_left;
  cmw_frame_construct(&top_left);

  struct cmw_frame top_right;
  cmw_frame_construct(&top_right);

  struct cmw_frame bottom_right;
  cmw_frame_construct(&bottom_right);

  struct cmw_frame bottom_left;
  cmw_frame_construct(&bottom_left);

  /* link all frames */
  cm_value_link(&top_left.area.left, context.left, 0.0f);
  cm_value_link(&top_left.area.top, context.top, 0.0f);
  cm_value_link(&top_left.area.right, &context.area.center.x, 0.0f);
  cm_value_link(&top_left.area.bottom, &context.area.center.y, 0.0f);

  cm_value_link(&top_right.area.left, &top_left.area.right, 0.0f);
  cm_value_link(&top_right.area.top, context.top, 0.0f);
  cm_value_link(&top_right.area.right, context.right, 0.0f);
  cm_value_link(&top_right.area.bottom, &context.area.center.y, 0.0f);

  cm_value_link(&bottom_right.area.left, &context.area.center.x, 0.0f);
  cm_value_link(&bottom_right.area.top, &top_left.area.bottom, 0.0f);
  cm_value_link(&bottom_right.area.right, context.right, 0.0f);
  cm_value_link(&bottom_right.area.bottom, context.bottom, 0.0f);

  cm_value_link(&bottom_left.area.left, context.left, 0.0f);
  cm_value_link(&bottom_left.area.top, &context.area.center.y, 0.0f);
  cm_value_link(&bottom_left.area.right, &bottom_right.area.left, 0.0f);
  cm_value_link(&bottom_left.area.bottom, context.bottom, 0.0f);

  /* main program loop */
  while (!SDL_QuitRequested()) {
    SDL_Delay(16);

    cmx_sdl2_context_update(&context);
    cm_render_queue_flush(&context.queue);

    cmw_frame_render(&top_left, &context.tileset, &context.queue);
    cmw_frame_render(&top_right, &context.tileset, &context.queue);
    cmw_frame_render(&bottom_right, &context.tileset, &context.queue);
    cmw_frame_render(&bottom_left, &context.tileset, &context.queue);

    SDL_RenderClear(context.renderer);
    cmx_sdl2_context_render(&context);
    SDL_RenderPresent(context.renderer);
  }
  cmx_sdl2_context_destruct(&context);
  SDL_Quit();
  return 0;
}

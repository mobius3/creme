#include "SDL.h"
#include "c-rez/fonts.h"
#include "c-rez/tilesets.h"

#include "widget/label.h"
#include "widget/frame.h"

#include "cmx-sdl2.h"
#include "cmx-font.h"

#include "stb_truetype.h"

int main(int argc, const char * argv[]) {
  /* initializes SDL2. */
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  /* initializes and pack used font */
  struct cmx_font_unicode_block blocks[] = {
    cmx_font_unicode_block_basic_latin,
    cmx_font_unicode_block_emoticons,
    cmx_font_unicode_block_cyrillic
  };
  struct cmx_font font;
  cmx_font_construct(&font, fonts_jost_600_semi_ttf.data, cmx_font_size_px(28), cm_color_make(109, 112, 196, 0));
  cmx_font_pack(&font, blocks, sizeof(blocks)/sizeof(*blocks));

  /* initializes the cmx_sdl2_context value */
  struct cm_render_command buffer[256];
  struct cmx_sdl2_context context = {
    .window = cmx_sdl2_window_make("cmex: text-rendering", cm_size_make(320, 240)),
    .renderer = cmx_sdl2_renderer_make(context.window, cm_color_make(231, 225, 206, 0)),
    .tileset_texture = NULL,
    .queue = cm_render_queue_make(buffer, 256),
    .tileset = {},
    .font = &font,
    .font_texture = cmx_sdl2_texture_make_from_pixel_data(context.renderer, font.pixels.data, font.pixels.dimensions)
  };

  /* this initializes other stuff that can't be initialized as above */
  cmx_sdl2_context_init(&context);

  struct cmw_label label;
  cmw_label_construct(&label);
  cmw_label_set_text(&label, "Oi, mundo!");

  cm_value_link(&label.area.left, &context.area.center.x, 0.0f);

  /* main program loop */
  while (!SDL_QuitRequested()) {
    SDL_Delay(16);
    cmx_sdl2_context_update(&context);
    cm_render_queue_flush(&context.queue);
    SDL_RenderClear(context.renderer);
    cmw_label_render(&label, &context.tileset, &context.queue);
    cmx_sdl2_context_render(&context);
    SDL_RenderPresent(context.renderer);
  }

  cmx_sdl2_context_destruct(&context);
  cmx_font_destruct(&font);
  SDL_Quit();
  return 0;
}

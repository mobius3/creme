#include "SDL.h"
#include "c-rez/fonts.h"
#include "c-rez/tilesets.h"

#include "creme-core.h"
#include "creme-widgets.h"

#include "creme-x-sdl2.h"
#include "creme-x-truetype.h"

static struct cm_size text_size(
  unsigned char const * text,
  size_t len,
  void * priv
) {
  return cmx_truetype_text_size(priv, text, len);
}

int main(int argc, const char * argv[]) {
  (void) argc;
  (void) argv;

  /* initializes SDL2. */
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  /* initializes and pack used font */
  struct cmx_truetype_unicode_block blocks[] = {
    cmx_truetype_unicode_block_basic_latin,
    cmx_truetype_unicode_block_latin_1_supplement,
    cmx_truetype_unicode_block_emoticons
  };
  struct cmx_truetype_font font;
  cmx_truetype_font_construct(
    &font, fonts_jost_500_medium_ttf.data,
    cmx_truetype_font_size_px(18), cm_color_make(109, 112, 196, 0)
  );
  cmx_truetype_font_pack(&font, blocks, sizeof(blocks) / sizeof(*blocks));

  /* initializes the cmx_sdl2_context value */
  struct cm_render_command buffer[256];
  struct cmx_sdl2_context context = {
    .window = cmx_sdl2_window_make(
      "cmex: 01-text-rendering",
      cm_size_make(320, 240)),
    .renderer = cmx_sdl2_renderer_make(
      context.window,
      cm_color_make(231, 225, 206, 0)),
    .queue = cm_render_queue_make(buffer, 256),
    .font = &font,
    .font_texture = cmx_sdl2_texture_make_from_pixel_data(
      context.renderer,
      font.pixels.data,
      font.pixels.dimensions
    ),
    .tileset = {
      .tile_height = 16,
      .tile_width = 16,
      .column_count = 512/16,
      .row_count = 512/16,
      .frame = {
        .column = 1,
        .row = 1
      }
    },
    .tileset_texture = cmx_sdl2_texture_make_from_image_data(
      context.renderer, tilesets_creme_png.data, tilesets_creme_png.length
    ),
  };

  /* this initializes other stuff that can't be initialized as above */
  cmx_sdl2_context_init(&context);

  struct cmw_label label;
  cmw_label_construct(&label);
  cmw_label_set_text(&label, (uint8_t *) "Olá, mundão!");
  cmw_label_set_size_fn(&label, text_size, &font);
  cm_area_center_at(
    &label.area,
    &context.area.center.x,
    &context.area.center.y,
    &label.text_width,
    &label.text_height
  );

  struct cmw_frame frame;
  cmw_frame_construct(&frame);
  cm_area_fill(
    &frame.area,
    &label.area,
    cm_rect_make_outset_of(&cm_rect_zero, 20)
  );

  /* main program loop */
  while (!SDL_QuitRequested()) {
    SDL_Delay(16);
    cmx_sdl2_context_update(&context);
    cm_render_queue_flush(&context.queue);
    SDL_RenderClear(context.renderer);
    cmw_frame_render(&frame, &context.tileset, &context.queue);
    cmw_label_render(&label, &context.tileset, &context.queue);
    cmx_sdl2_context_render(&context);
    SDL_RenderPresent(context.renderer);
  }

  cmx_sdl2_context_destruct(&context);
  cmx_truetype_font_destruct(&font);
  SDL_Quit();
  return 0;
}

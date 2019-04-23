
#include <font.h>

#include "font.h"
#include "stb_truetype.h"

void cmx_font_construct(struct cmx_font * font) {
  (void) font;
}

void cmx_font_load_ttf(struct cmx_font * font, const char * path) {
  (void) font;
  (void) path;
}

void cmx_font_generate_pixels(
  struct cmx_font const * font,
  struct cmx_font_pixels * pixels
) {
  (void) font;
  (void) pixels;

}

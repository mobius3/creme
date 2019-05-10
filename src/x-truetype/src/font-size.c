#include "font-size.h"

struct cmx_truetype_font_size cmx_truetype_font_size_pt(float value) {
  struct cmx_truetype_font_size result = {value, cmx_truetype_size_type__pt};
  return result;
}

struct cmx_truetype_font_size cmx_truetype_font_size_px(float value) {
  struct cmx_truetype_font_size result = {value, cmx_truetype_size_type__px};
  return result;
}
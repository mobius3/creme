#include "font-size.h"

struct cmx_font_size cmx_font_size_pt(float value) {
  struct cmx_font_size result = {value, cmx_font_size_type__pt};
  return result;
}

struct cmx_font_size cmx_font_size_px(float value) {
  struct cmx_font_size result = {value, cmx_font_size_type__px};
  return result;
}
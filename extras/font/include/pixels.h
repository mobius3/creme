#ifndef CREME_EXTRAS_FONT_PIXELS_H
#define CREME_EXTRAS_FONT_PIXELS_H

#include "rect.h"
#include "size.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cmx_font_pixels {
  unsigned char const * pixels;
  size_t length;
  struct cm_size size;
};

#ifdef __cplusplus
}
#endif

#endif
#ifndef CREME_EXTRAS_FONT_H
#define CREME_EXTRAS_FONT_H

#include "rect.h"
#include "size.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cmx_font {

};

struct cmx_font_pixels;

extern void cmx_font_construct(struct cmx_font * font);
extern void cmx_font_load_ttf(struct cmx_font * font, char const path[]);
extern void cmx_font_generate_pixels(struct cmx_font const * font, struct cmx_font_pixels * pixels);

#ifdef __cplusplus
};
#endif

#endif
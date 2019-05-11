#ifndef CREME_COLOR_H
#define CREME_COLOR_H

#include "core-exports.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cm_color {
  uint8_t r, g, b, a;
};

CORE_API extern void cm_color_construct(struct cm_color * color);
CORE_API extern void cm_color_construct_set(
  struct cm_color * color,
  uint8_t r,
  uint8_t g,
  uint8_t b,
  uint8_t a
);

CORE_API extern struct cm_color cm_color_make(
  uint8_t r, uint8_t g, uint8_t b, uint8_t a
);

CORE_API extern struct cm_color cm_color_0x_rgb(uint32_t hex);
CORE_API extern struct cm_color cm_color_0x_rgba(uint32_t hex);

CORE_API extern struct cm_color cm_color_red;
CORE_API extern struct cm_color cm_color_green;
CORE_API extern struct cm_color cm_color_blue;
CORE_API extern struct cm_color cm_color_white;
CORE_API extern struct cm_color cm_color_black;

#ifdef __cplusplus
}
#endif

#endif /* CREME_COLOR_H */

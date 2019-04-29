#include "color.h"

struct cm_color cm_color_red = {255, 0, 0, 255};
struct cm_color cm_color_green = {0, 255, 0, 255};
struct cm_color cm_color_blue = {0, 0, 255, 255};
struct cm_color cm_color_white = {255, 255, 255, 255};
struct cm_color cm_color_black = {0, 0, 0, 255};

struct cm_color cm_color_make(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  struct cm_color result = {r, g, b, a};
  return result;
}

void cm_color_construct(struct cm_color * color) {
  color->r = color->g = color->b;
  color->a = 255;
}

void cm_color_construct_set(
  struct cm_color * color,
  uint8_t r,
  uint8_t g,
  uint8_t b,
  uint8_t a
) {
  color->r = r;
  color->g = g;
  color->b = b;
  color->a = a;
}


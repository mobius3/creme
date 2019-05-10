#ifndef CREME_COLOR_H
#define CREME_COLOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cm_color {
  uint8_t r, g, b, a;
};

extern void cm_color_construct(struct cm_color * color);
extern void cm_color_construct_set(struct cm_color * color, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
extern struct cm_color cm_color_make(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

extern struct cm_color cm_color_red;
extern struct cm_color cm_color_green;
extern struct cm_color cm_color_blue;
extern struct cm_color cm_color_white;
extern struct cm_color cm_color_black;

#ifdef __cplusplus
}
#endif

#endif /* CREME_COLOR_H */

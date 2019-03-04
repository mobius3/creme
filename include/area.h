#ifndef CREME_AREA_H
#define CREME_AREA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "value.h"
#include "rect.h"

/**
 * Describes an area starting at left, top and ending at right, bottom.
 *
 * width, height, center.x and center.y are calculated values (and should be
 * treated read only!) linked to left, top, right and bottom.
 *
 * Note that right and bottom are *not* equivalent to width and height.
 *
 * You can (and should!) link these both as down and upstream values of
 * other values.
 */
struct cm_area
{
  struct cm_value left;
  struct cm_value right;
  struct cm_value top;
  struct cm_value bottom;
  struct cm_value width;
  struct cm_value height;
  struct
  {
    struct cm_value x;
    struct cm_value y;
  } center;
};

void cm_area_construct(struct cm_area * area);

void
cm_area_construct_set(
  struct cm_area * area,
  float left,
  float top,
  float right,
  float bottom);

void
cm_area_set(
  struct cm_area * area,
  float left,
  float top,
  float right,
  float bottom);

void cm_area_destruct(struct cm_area * area);

struct cm_rect cm_area_to_rect(struct cm_area const * area);

#ifdef __cplusplus
}
#endif

#endif //CREME_AREA_H

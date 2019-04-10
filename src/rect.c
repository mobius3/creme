
#include <rect.h>

#include "rect.h"

struct cm_rect cm_rect_make(float left, float top, float right, float bottom) {
  struct cm_rect result;
  cm_rect_set(&result, left, top, right, bottom);
  return result;
}

void
cm_rect_set(struct cm_rect * rect,
            float left, float top, float right, float bottom) {
  rect->left = left;
  rect->top = top;
  rect->right = right;
  rect->bottom = bottom;
}

float cm_rect_width(struct cm_rect const * rect) {
  return rect->right - rect->left;
}

float cm_rect_height(struct cm_rect const * rect) {
  return rect->bottom - rect->top;
}

void cm_rect_construct(struct cm_rect * rect) {
  cm_rect_set(rect, 0, 0, 0, 0);
}
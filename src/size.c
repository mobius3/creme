
#include <size.h>

#include "size.h"


void cm_size_construct(struct cm_size * size) {
  size->width = 0;
  size->height = 0;
}


void cm_size_set(struct cm_size * size, float width, float height) {
  size->width = width;
  size->height = height;
}

struct cm_size cm_size_make(float width, float height) {
  struct cm_size result = { width, height };
  return result;
}

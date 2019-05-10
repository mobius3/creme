#ifndef CREME_SIZE_H
#define CREME_SIZE_H

#include "core-exports.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A `cm_size` value contains width and height as floats.
 */
struct cm_size {
  float width;
  float height;
};


/**
 * Constructs a `cm_size` value with 0 width and 0 height
 * @param size A pointer to a `cm_size` value to construct
 */
CORE_API extern void cm_size_construct(struct cm_size * size);

/**
 * Sets both the width and height of a `cm_size` value.
 * @param size A pointer to a `cm_size` value to set width and height
 * @param width The width to set
 * @param height The height to set
 */
CORE_API extern void cm_size_set(struct cm_size * size, float width, float height);

/**
 * Constructs and returns a `cm_size` value and sets width and height to the
 * values passed.
 * @param width The width value to set
 * @param height The height value to set
 * @return A `cm_size` value
 */
CORE_API extern struct cm_size cm_size_make(float width, float height);

#ifdef __cplusplus
};
#endif

#endif /* CREME_SIZE_H */

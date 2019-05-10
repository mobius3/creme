#ifndef CREME_RECT_H
#define CREME_RECT_H

#include "core-exports.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A `cm_rect` struct represents a rectangle with `left`, `top`, `right` and
 * bottom `float` values
 */
struct cm_rect
{
  float left, top, right, bottom;
};

CORE_API extern struct cm_rect const cm_rect_zero;

/**
 * Creates a `cm_rect` value by copying `left`, `top`, `right` and `bottom`.
 *
 * This is mostly useful to create temporary values to pass as argument to
 * functions requiring a `cm_rect` value.
 *
 * @param left The `left` member value
 * @param top The `top` member value
 * @param right The `right` member value
 * @param bottom The `bottom` member value
 * @return A `cm_rect` value
 */
CORE_API extern struct cm_rect
cm_rect_make(float left, float top, float right, float bottom);

/**
 * Creates another reclangle that is padded by `inset_amount`. This allows you
 * to create rectangles that inset or offset another one. This means
 * that the new rectangle will have:
 * - left = rect->left + pad_amount
 * - top = rect->top + pad_amount
 * - right = rect->right - pad_amount
 * - bottom = rect->bottom - pad_amount
 *
 * @param rect A pointer to another `cm_rect` value that will be used as a base.
 * @param pad_amount How much inset padding to add
 * @return A `cm_rect` value with the padding applied.
 */
CORE_API extern struct cm_rect cm_rect_make_inset_of(struct cm_rect const * rect, float inset_amount);

/**
 * This is literally `cm_rect_make_inset_of` but passing a negative
 * inset_amount. This is here just for the sake of completeness.
 *
 * @param rect A pointer to another `cm_rect` value that will be used as a base.
 * @param pad_amount How much outset padding to add
 * @return A `cm_rect` value with the padding applied.
 */
CORE_API extern struct cm_rect cm_rect_make_outset_of(struct cm_rect const * rect, float outset_amount);

/**
 * Constructs a `cm_rect` value with all its values zeroed.
 *
 * This is equivalent to `cm_rect_set(rect, 0, 0, 0, 0)`
 *
 * @param rect A pointer to a `cm_rect` value to construct
 * @sa cm_rect_set
 */
CORE_API extern void cm_rect_construct(struct cm_rect * rect);

/**
 * Sets a `cm_rect` value by setting its four coordinates.
 *
 * @param rect A pointer to a `cm_rect` value to set
 * @param left The `left` value
 * @param top The `top` value
 * @param right The `right` value
 * @param bottom The `bottom` value
 */
CORE_API extern void cm_rect_set(
  struct cm_rect * rect,
  float left,
  float top,
  float right,
  float bottom
);

/**
 * Calculates and returns the width of a rect represented by a `cm_rect` value.
 * This is equivalent to `(rect->right - rect->left)`
 *
 * @param rect A pointer to a `cm_rect` value to calculate width
 * @return The calculated width
 * @sa cm_rect_height
 */
CORE_API extern float cm_rect_width(struct cm_rect const * rect);

/**
 * Calculates and returns the height of a rect represented by a `cm_rect` value.
 * This is equivalent to `(rect->bottom - rect->top)`
 *
 * @param rect A pointer to a `cm_rect` value to calculate height
 * @return The calculated height
 * @sa cm_rect_width
 */
CORE_API extern float cm_rect_height(struct cm_rect const * rect);

#ifdef __cplusplus
}
#endif

#endif /* CREME_RECT_H */

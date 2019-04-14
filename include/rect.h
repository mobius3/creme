#ifndef CREME_RECT_H
#define CREME_RECT_H

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
extern struct cm_rect
cm_rect_make(float left, float top, float right, float bottom);

/**
 * Constructs a `cm_rect` value with all its values zeroed.
 *
 * This is equivalent to `cm_rect_set(rect, 0, 0, 0, 0)`
 *
 * @param rect A pointer to a `cm_rect` value to construct
 * @sa cm_rect_set
 */
extern void cm_rect_construct(struct cm_rect * rect);

/**
 * Sets a `cm_rect` value by setting its four coordinates.
 *
 * @param rect A pointer to a `cm_rect` value to set
 * @param left The `left` value
 * @param top The `top` value
 * @param right The `right` value
 * @param bottom The `bottom` value
 */
extern void cm_rect_set(
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
extern float cm_rect_width(struct cm_rect const * rect);

/**
 * Calculates and returns the height of a rect represented by a `cm_rect` value.
 * This is equivalent to `(rect->bottom - rect->top)`
 *
 * @param rect A pointer to a `cm_rect` value to calculate height
 * @return The calculated height
 * @sa cm_rect_width
 */
extern float cm_rect_height(struct cm_rect const * rect);

#ifdef __cplusplus
}
#endif

#endif /* CREME_RECT_H */
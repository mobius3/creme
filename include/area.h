#ifndef CREME_AREA_H
#define CREME_AREA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "value.h"
#include "rect.h"

/**
 * A `cm_area` struct describes an area starting at
 * `left`, `top` and ending at `right`, `bottom`.
 *
 * Areas are mostly useful if you think about them as widget anchors, so you
 * can link a `widget1.area.left` to `widget2.area.right`, effectively anchoring
 * them together and expressing a dependency between those edges.
 *
 * `width`, `height`, `center.x` and `center.y` are calculated values
 * (and should be mostly treated as read only!) linked to `left`, `top`, `right`
 * and `bottom`. It is okay to link them as upstream to other values but linking
 * them as downstream is nonsense and breaks their functionality (and also would
 * make wild pandas very sad).
 *
 * Note that `right` and `bottom` are *not* equivalent to `width` and `height`.
 *
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

/**
 * Constructs an `cm_area` value and all its `cm_value`s.
 *
 * Calling this function (or its variants) *is* required to make a `cm_area`
 * value work properly. This ties up width, height and center values.
 *
 * If a `cm_area` value is already constructed, its `cm_value`s would also be
 * constructed again.
 *
 * @param area A pointer to a `cm_area` to construct
 */
void cm_area_construct(struct cm_area * area);

/**
 * Resets all `cm_value`s of an area to the absolute values passed in.
 *
 * Note that this
 * *will not* break upstream nor downstream links. It will merely call
 * `cm_value_set` on each respective `cm_value`. If you wish to break
 * upstream links you have to do so on each individual member.
 *
 * @param area A pointer to a `cm_area` value
 * @param left A float value to assign to `left` member
 * @param top A float value to assign to `top` member
 * @param right A float value to assign to `right` member
 * @param bottom A float value to assign to `bottom` member
 */
void
cm_area_set(
  struct cm_area * area,
  float left,
  float top,
  float right,
  float bottom);

/**
 * Destructs and breaks all uplinks and downlinks of a `cm_area`.
 *
 * It doesn't free any memory, as none of `cm_area` functions allocate any.
 * If you are using dynamic memory, you will have
 * to free it yourself (also upstream and downstream!) if you need to.
 *
 * Afterwards, it is safe to call `cm_area_construct` again on this
 * `cm_area` pointer.
 *
 * @param area A pointer to a `cm_area` value to destroy
 */
void cm_area_destruct(struct cm_area * area);

/**
 * Creates a `cm_rect` value from a pointer to a `cm_area` value.
 * A `cm_rect` has no links and has only absolute values.
 *
 * @param area A pointer to a `cm_area` value to convert to a `cm_rect` value
 * @return A `cm_rect` value
 * @sa cm_rect
 */
struct cm_rect cm_area_to_rect(struct cm_area const * area);

#ifdef __cplusplus
}
#endif

#endif //CREME_AREA_H

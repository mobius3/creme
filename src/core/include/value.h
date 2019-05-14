#ifndef CREME_VALUE_H
#define CREME_VALUE_H

#include <stdint.h>
#include "core-exports.h"
#include "value-reduce.h"

#ifndef CREME_MAX_VALUE_UPSTREAM
#define CREME_MAX_VALUE_UPSTREAM 16
#endif

#ifndef CREME_MAX_VALUE_DOWNSTREAM
#define CREME_MAX_VALUE_DOWNSTREAM 16
#endif

#if CREME_MAX_VALUE_DOWNSTREAM > 32
#error "A value cannot have more than 32 downstreams"
#endif

#if CREME_MAX_VALUE_UPSTREAM > 32
#error "A value cannot have more than 32 upstreams"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** The result of the link process */
enum cm_value_link_result {
  /** Linking occurred normally */
    cm_value_link__ok = 0,
  /** Upstream cannot have any more downstream  */
    cm_value_link__upstream_full,
  /** Value cannot have any more upstream */
    cm_value_link__too_many_upstreams,
  /** Would result in a 1st-grade cycle  */
    cm_value_link__cyclic_link
};


/**
 * A `cm_value` structure represents values whose changes can be chained
 * and propagated to other values.
 *
 * They are useful when you want to update a value in regards to other values,
 * keeping it updated whenever these other values change. Their main use in
 * Creme is to create anchors that you can link your widgets to (say, link the
 * right edge of a widget to the left edge of another plus some offset).
 *
 * Every `cm_value` has a reduce function. They receive an array of all
 * of its upstream values and should produce a single value that is going to
 * be assigned to the `cm_value` and then offset by the offset value. Afterwards
 * downstream values will get updated.
 *
 * This means that if a `cm_value` has other values downstream, they will
 * have their reduce function called to update their values, going recursively
 * down the chain of linked values.
 *
 * Offsets are applied *after* values are calculated and this is done regardless
 * of the reduce function.
 *
 * If any update results in cyclical iteration, updates are stopped and a
 * message is printed in the `stderr` console. If you are interested in
 * debugging cyclical updates, compile creme with `-DCREME_DEBUG_UPDATE_CYCLE`
 * and cyclical updates will crash at an assertion.
 *
 * You should treat all members of this structure private, things can get real
 * messy if you don't.
 */
struct cm_value {
  float absolute;
  float offset;
  struct cm_value * upstream[CREME_MAX_VALUE_UPSTREAM];
  struct cm_value * downstream[CREME_MAX_VALUE_DOWNSTREAM];
  uint8_t upstream_count;
  uint8_t downstream_count;
  uint8_t index_at_downstream[CREME_MAX_VALUE_DOWNSTREAM];
  int update_token;
  uint32_t update_seen;
  struct cm_value_reduce reduce;
  char tag[8];
};

/**
 * Constructs a `cm_value` value with 0 offset and 0 absolute.
 *
 * By default, `cm_value`s will have their value equal to its first direct
 * upstream value + offset. In other words, the default `cm_reduce_fn`
 * of a `cm_value` is `cm_reduce_first`.
 *
 * @param value A pointer to a `cm_value` value.
 */
CORE_API extern void cm_value_construct(struct cm_value * value);


/**
 * Constructs a `cm_value` value with 0 offset and the argument given
 * as absolute.
 *
 * This is equivalent to calling `cm_value_construct` and `cm_value_set`
 *
 * @param value A pointer to a `cm_value` value.
 */
CORE_API extern void
cm_value_construct_set(struct cm_value * value, float absolute);

/**
 * Construct a `cm_value` value with 0 offset and 0 absolute. It also sets a
 * custom reduce function that should be able to receive upstream absolute
 * values and output a calculated result.
 *
 * @param value A pointer to a `cm_value` value to be constructed
 * @param reduce_fn the reduce function.
 */
CORE_API extern void cm_value_construct_reduce(
  struct cm_value * value,
  struct cm_value_reduce reduce
);

/**
 * Constructs a `cm_value` value with 0 offset and 0 absolute. It's absolute
 * value is calculated by taking the average value of its upstream values.
 *
 * @param value A pointer to a `cm_value` value to be constructed
 */
CORE_API extern void cm_value_construct_average(struct cm_value * value);

/**
 * Constructs a `cm_value` value with 0 offset and 0 absolute. It's absolute
 * value is calculated by taking the highest value in its upstream values.
 *
 * @param value A pointer to a `cm_value` value to be constructed
 */
CORE_API extern void cm_value_construct_max(struct cm_value * value);

/**
 * Constructs a `cm_value` value with 0 offset and 0 absolute. It's absolute
 * value is calculated by taking the lowest value in its upstream values.
 *
 * @param value A pointer to a `cm_value` value to be constructed
 */
CORE_API extern void cm_value_construct_min(struct cm_value * value);

/**
 * Sets the absolute value of a `cm_value`, regardless of its offset or
 * direct upstream links.
 *
 * This *will not* break any direct upstream or direct downstream links and
 * if any upstream value changes, it will get recalculated.
 *
 * If you wish to break direct upstream links,
 * call `cm_value_unlink_all_upstream`.
 *
 * Note that setting absolute values directly might result in inconsistent
 * states in regards to offset and upstream values.
 *
 * @param value A pointer to a `cm_value` value
 * @param absolute the absolute value to set
 * @sa cm_value_unlink_all_upstream
 */
CORE_API extern void cm_value_set(struct cm_value * value, float absolute);

/**
 * Returns the value of a cm_value. This is equal to `value->absolute`. No
 * further calculation is done.
 *
 * @param value A pointer to a `cm_value` value
 * @return value->absolute
 */
CORE_API extern float cm_value_get(struct cm_value const * value);

/**
 * Calculates the value of a cm_value considering its direct upstreams,
 * reduce function  and offset.
 *
 * This function is automatically called whenever upstream changes or a new
 * link is made, but you can forcefully trigger it if you must.
 *
 * @param value A pointer to a `cm_value` value
 * @return the updated absolute value
 */
CORE_API extern float cm_value_update(struct cm_value * value);

/**
 * Links a `cm_value` to another `cm_value` as an upstream value.
 *
 * Whenever an upstream `cm_value` updates its absolute value, this `cm_value`
 * gets recalculated based on all direct upstreams.
 *
 * Direct cyclic links (value -> up and up -> value) will fail, but this
 * function does not walk through all streams to detect cycles. After
 * cm_value_update is called you will get an error in stderr if
 * there's any cycle downstream.
 *
 * This function **WILL** break all upstream links and its equivalent to calling
 * `cm_value_unlink_all_upstream`, `value->offset = offset` and
 * `cm_value_link_add`. It is meant as a
 * shortcut when you only want one upstream.
 *
 * @param value A pointer to a `cm_value` value
 * @param up A pointer to a `cm_value` that will be a direct upstream of this
 *           `value`
 * @return the result of linking.
 * @sa cm_value_link_result
 */
CORE_API extern enum cm_value_link_result
cm_value_link(struct cm_value * value, struct cm_value * up, float offset);

/**
 * Adds `up` as upstream of `up`. The maximum number of upstream values
 * in a `cm_link` value is governed by the compile-time definition
 * CREME_MAX_VALUE_UPSTREAM.
 *
 * @param value A pointer to a `cm_value` value
 * @param up A pointer to a `cm_value` that will be the only
 *           direct upstream of this `value`
 * @return the result of linking.
 * @sa cm_value_link_result
 * @sa cm_value_link
 */
CORE_API extern enum cm_value_link_result
cm_value_link_add(struct cm_value * value, struct cm_value * up);

/**
 * Sets the offset amount of a value and triggers `cm_value_update`.
 *
 * @param value A pointer to a `cm_value` value
 * @param offset the offset amount
 */
CORE_API extern void cm_value_offset_set(struct cm_value * value, float offset);

/**
 * Gets the offset value of a `cm_value`.
 *
 * This is equivalent to accessing value->offset directly (you shouldn't change
 * it directly, though).
 *
 * @param value A pointer to a `cm_value` value
 * @return value->offset
 */
CORE_API extern float cm_value_offset_get(struct cm_value * value);

/**
 * Breaks the link between a `cm_value` and a direct upstream `cm_value`.
 * This will trigger value updates.
 *
 * If this is the last direct upstream, the absolute value will remain
 * what it was before the upstream was removed.
 *
 * This function never fails, if @p up is not upstream of @p value then nothing
 * happens. If it is, it is removed and values are recalculated.
 *
 * @param value A pointer to a `cm_value` that is a direct downsteam of `up`
 * @param up A pointer to a `cm_value` that is a direct upstream of `value`
 */
CORE_API extern void
cm_value_unlink(struct cm_value * value, struct cm_value * up);

/**
 * Break all direct upstream links of a `cm_value`.
 *
 * Last absolute value is kept.
 * This function never fails, even if there is no upstream linked.
 *
 * @param value A ponter to a `cm_value` value
 */
CORE_API extern void
cm_value_unlink_all_upstream(struct cm_value * value);

/**
 * Break all direct downstream links of a `cm_value`.
 *
 * This is equivalent of calling `cm_value_unlink(downstream, value)` on every
 * downstream link of `value`.
 *
 * This function never fails, even if there is no downstream linked.
 *
 * @param value A ponter to a `cm_value` value
 */
CORE_API extern void
cm_value_unlink_all_downstream(struct cm_value * value);

/**
 * Removes all direct upstream and direct downstream links of a `cm_value`.
 *
 * All downstream values will be recalculated. You *must* call this function
 * before a `cm_value` leaves scope or before freeing its memory (if using
 * dynamic memory). Not doing so will have serious random consequences.
 *
 * @param value A pointer to a `cm_value` value
 */
CORE_API extern void cm_value_destruct(struct cm_value * value);

CORE_API extern void
cm_value_set_reduce(struct cm_value * value, struct cm_value_reduce reduce);

CORE_API extern void cm_value_set_tag(struct cm_value * value, const char tag[8]);

#ifdef __cplusplus
}
#endif

#endif /* CREME_VALUE_H */

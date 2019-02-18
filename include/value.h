#ifndef CREME_VALUE_H
#define CREME_VALUE_H

#include <stdint.h>

#ifndef CREME_MAX_VALUE_UPSTREAM
#define CREME_MAX_VALUE_UPSTREAM 16
#endif

#ifndef CREME_MAX_VALUE_DOWNSTREAM
#define CREME_MAX_VALUE_DOWNSTREAM 16
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** The result of the link process */
enum cm_value_link_result
{
  /** Linking occurred normally */
  cm_value_link__ok = 0,
  /** Upstream cannot have any more downstream  */
  cm_value_link__upstream_full,
  /** Value cannot have any more upstream */
  cm_value_link__too_many_upstreams,
  /** Would result in a 1st-grade cycle  */
  cm_value_link__cyclic_link
};

typedef float (* cm_reduce_fn)(float const values[], uint16_t values_count);

float cm_reduce_first(float const values[], uint16_t values_count);
float cm_reduce_average(float const values[], uint16_t values_count);
float cm_reduce_max(float const values[], uint16_t values_count);
float cm_reduce_min(float const values[], uint16_t values_count);

/**
 * cm_value represents values that can be chained and propagated
 * to other values.
 *
 * They are useful when you want to update a value in regards to other values,
 * keeping it updated whenever these other values change. Their main use in
 * Creme is to create anchors that you can link your widgets to (say, link the
 * right edge of a widget to the left edge of another plus some offset).
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
struct cm_value
{
  float absolute;
  float offset;
  struct cm_value * upstream[16];
  struct cm_value * downstream[16];
  uint16_t upstream_count;
  uint16_t downstream_count;
  cm_reduce_fn reduce_fn;
  int update_token;
};

/**
 * Constructs a cm_value with 0 offset and 0 absolute.
 *
 * By default, cm_values will have their value equal to its first upstream
 * value + offset. In other words, the default cm_reduce_fn of a cm_value is
 * cm_reduce_first.
 *
 * @param value the `cm_value` instance.
 */
void cm_value_construct(struct cm_value * value);


/**
 * Constructs a cm_value with 0 offset and the argument given as absolute.
 *
 * This is equivalent to calling cm_value_construct and cm_value_set
 *
 * @param value the `cm_value` instance.
 */
void cm_value_construct_set(struct cm_value * value, float absolute);

/**
 * Construct a cm_value with 0 offset and 0 absolute. It also sets a custom
 * reduce function that should be able to receive upstream absolute values and
 * output a calculated result.
 *
 * @param value the `cm_value` instance to be constructed
 * @param reduce_fn the reduce function.
 */
void cm_value_construct_reduce(struct cm_value * value, cm_reduce_fn reduce_fn);

/**
 * Constructs a cm_value with 0 offset and 0 absolute. It's value is calculated
 * by taking the average value of its upstream values.
 *
 * @param value the `cm_value` instance to be constructed
 */
void cm_value_construct_average(struct cm_value * value);

/**
 * Constructs a cm_value with 0 offset and 0 absolute. It's value is calculated
 * by taking the highest value in its upstream values.
 *
 * @param value the `cm_value` instance to be constructed
 */
void cm_value_construct_max(struct cm_value * value);

/**
 * Constructs a cm_value with 0 offset and 0 absolute. It's value is calculated
 * by taking the lowest value in its upstream values.
 *
 * @param value the `cm_value` instance to be constructed
 */
void cm_value_construct_min(struct cm_value * value);

/**
 * Sets the absolute value of a cm_value, regardless of its offset or upstream
 * links.
 *
 * This *will not* break any upstream or downstream links and if a upstream
 * value changes, it will get recalculated.
 *
 * @param value the cm_value instance
 * @param absolute the absolute value to set
 */
void cm_value_set(struct cm_value * value, float absolute);

/**
 * Returns the value of a cm_value. This is equal to `value->absolute`. No
 * further calculation is done.
 *
 * @param value The cm_value instance
 * @return value->absolute
 */
float cm_value_get(struct cm_value * value);

/**
 * Calculates the value of a cm_value considering its upstreams, reduce function
 * and offset.
 *
 * This function is automatically called whenever upstream changes or a new
 * link is made.
 *
 * @param value The cm_value instance
 * @return the updated absolute value
 */
float cm_value_update(struct cm_value * value);

/**
 * Links a value to an upstream value.
 *
 * Whenever an upstream updates its absolute value, this value gets recalculated
 * based on all upstreams.
 *
 * Direct cyclic links (value -> up and up -> value) will fail, but this
 * function does not walk through all streams to detect cycles. Since after
 * linking cm_value_update is called you will get an error in stderr if
 * there's any cycle downstream (because cm_value_update does detect indirect
 * cycles).
 *
 * @param value The cm_value instance
 * @param up The cm_value upstream instance
 * @return the result of linking.
 * @sa cm_value_link_result
 */
enum cm_value_link_result
cm_value_link(struct cm_value * value, struct cm_value * up);

/**
 * Break the link between a value and an upstream value. This will trigger
 * value updates.
 *
 * If this is the last upstream, the absolute value will remain
 * what it was before the upstream was removed.
 *
 * This function never fails, if @p up is not upstream of @p value then nothing
 * happens. If it is, it is removed and values are recalculated.
 *
 * @param value The cm_value instance
 * @param up The cm_value upstream instance
 */
void
cm_value_unlink(struct cm_value * value, struct cm_value * up);

/**
 * Break all upstream links of a value.
 *
 * Last absolute value is kept.
 *
 * This function never fails, even if there is no upstream linked.
 *
 * @param value The cm_value instance
 */
void
cm_value_unlink_all_upstream(struct cm_value * value);

/**
 * Break all downstream links of a value.
 *
 * This is equivalent of calling cm_value_unlink(downstream, value) on every
 * downstream link of `value`.
 *
 * This function never fails, even if there is no downstream linked.
 *
 * @param value The cm_value instance
 */
void
cm_value_unlink_all_downstream(struct cm_value * value);

/**
 * Removes all upstream and downstream links of a cm_value.
 *
 * All downstream values will be recalculated. You *must* call this function
 * before a cm_value leaves scope or before freeing its memory (if using
 * dynamic memory). Not doing so will have serious random consequences.
 * @param value The cm_value instance
 */
void cm_value_destruct(struct cm_value * value);


#ifdef __cplusplus
}
#endif

#endif //CREME_VALUE_H

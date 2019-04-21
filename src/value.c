#include "value.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#ifdef CREME_DEBUG_UPDATE_CYCLE
#include <assert.h>
#endif


float cm_value_update_with_token(struct cm_value * value, int token, int parent_index);

void
cm_value_set_with_token(struct cm_value * value, float absolute, int token);


void
cm_value_construct_reduce(struct cm_value * value, cm_reduce_fn reduce_fn) {
  cm_value_construct(value);
  value->reduce_fn = reduce_fn;
}

void cm_value_construct_average(struct cm_value * value) {
  cm_value_construct_reduce(value, cm_reduce_average);
}

void cm_value_construct_max(struct cm_value * value) {
  cm_value_construct_reduce(value, cm_reduce_max);
}


void cm_value_construct_min(struct cm_value * value) {
  cm_value_construct_reduce(value, cm_reduce_min);
}


void cm_value_construct(struct cm_value * value) {
  int i = 0;
  value->absolute = 0;
  for (i = 0; i < 16; i++) value->upstream[i] = NULL;
  for (i = 0; i < 16; i++) value->downstream[i] = NULL;
  value->upstream_count = 0;
  value->downstream_count = 0;
  value->reduce_fn = NULL;
}

void cm_value_construct_set(struct cm_value * value, float absolute) {
  cm_value_construct(value);
  cm_value_set(value, absolute);
}

void cm_value_destruct(struct cm_value * value) {
  cm_value_unlink_all_downstream(value);
  cm_value_unlink_all_upstream(value);
}

enum cm_value_link_result
cm_value_link_add(struct cm_value * value, struct cm_value * up) {
  uint16_t i = 0;
  if (up->downstream_count >= CREME_MAX_VALUE_DOWNSTREAM)
    return cm_value_link__upstream_full;

  if (value->upstream_count >= CREME_MAX_VALUE_UPSTREAM)
    return cm_value_link__too_many_upstreams;

  for (i = 0; i < value->upstream_count; i++) {
    if (value->upstream[i] == up) return cm_value_link__ok;
  }

  for (i = 0; i < value->downstream_count; i++) {
    if (value->downstream[i] == up) return cm_value_link__cyclic_link;
  }

  value->upstream[value->upstream_count] = up;
  up->downstream[up->downstream_count] = value;
  up->index_at_downstream[up->downstream_count] = value->upstream_count;
  value->upstream_count += 1;
  up->downstream_count += 1;

  cm_value_update(value);

  return cm_value_link__ok;
}

enum cm_value_link_result
cm_value_link(struct cm_value * value, struct cm_value * up) {
  cm_value_unlink_all_upstream(value);
  return cm_value_link_add(value, up);
}

void cm_value_offset_set(struct cm_value * value, float offset) {
  value->offset = offset;
  cm_value_update(value);
}

float cm_value_offset_get(struct cm_value * value) {
  return value->offset;
}

void cm_value_unlink(struct cm_value * value, struct cm_value * up) {
  uint8_t up_i = 0, down_i = 0;


  /* find `value` index in `up` downstream array */
  for (down_i = 0; down_i < up->downstream_count; down_i++) {
    if (up->downstream[down_i] == value) break;
  }

  /* we could not find `value` as downstream of `up`. nothing else to do.
   * (there could be the case where `up` is upstream of `value` but `value`
   * not down of `up`. If this is happening probably someone else messed up
   * with link values and indexes. good luck tracking that down. */
  if (down_i == up->downstream_count) return;

  /* gets upstream index of `up` in `value` */
  up_i = up->index_at_downstream[down_i];

  value->upstream[up_i] = value->upstream[value->upstream_count - 1];
  value->upstream_count--;

  /* this makes the value in downstream occupy the empty space, making
   * sure there is no holes. */
  up->downstream[down_i] = up->downstream[up->downstream_count - 1];
  up->index_at_downstream[down_i] = up->index_at_downstream[up->downstream_count -1];
  up->downstream_count--;

  /* trigger an update, this is important because of values having multiple-up
   * reduce functions */
  cm_value_update(value);
}

void cm_value_unlink_all_upstream(struct cm_value * value) {
  int i = 0;
  int j = 0;
  struct cm_value * up;
  for (i = 0; i < value->upstream_count; value++) {
    up = value->upstream[i];
    /* looks up our index in `up`s downstream array */
    for (j = 0; j < up->downstream_count; j++) {
      if (up->downstream[j] == value) break;
    }
    /* if we found `value` in `up`, unlink. else, something is broken,
     * but this function does not care, specially because `up` does not know
     * about us and is never going to touch about us, so its safe to pretend
     * the link never happened. */
    if (j != up->downstream_count) {
      up->downstream[j] = up->downstream[up->downstream_count - 1];
      up->index_at_downstream[j] = up->index_at_downstream[up->downstream_count - 1];
      up->downstream_count--;
    }
  }
  value->upstream_count = 0;
}


void cm_value_unlink_all_downstream(struct cm_value * value) {
  while (value->downstream_count > 0)
    cm_value_unlink(value->downstream[0], value);
}

float cm_value_update(struct cm_value * value) {
  int token = rand();
  return cm_value_update_with_token(value, token, -1);
}

/* The most important job of this function is to check and stop update cycles.
 * How it does this is twofold: it receives a token generated by the function
 * that triggered this update and the parent index that triggered it.
 * The token is used to check if this value is being updated again in the same
 * update stream and the index is used to check if we are being updated twice
 * by the same parent. If this is the case, we are in a cycle.
 *
 * If the update token is different from what is stored in the value being
 * updated then this is the first time we update this value. The token is stored
 * in the value.
 *
 * If the update token is equal from what is stored, this function checks the
 * stored bitmask of seen parents. If this particular parent index is set, the
 * update cycle is stopped and the current absolute value is returned.
 *
 * If the token is different and/or the parent_index was not set, it gets set
 * and the update continues downstream.
 */
float cm_value_update_with_token(struct cm_value * value, int token, int parent_index) {
  cm_reduce_fn reduce = value->reduce_fn;
  float values[CREME_MAX_VALUE_UPSTREAM];
  uint16_t i = 0;

  if (value->update_token != token) {
    value->update_token = token;
    value->update_seen = 0;
  }
  else if (parent_index != -1 && value->update_seen & (0x1 << parent_index)) {
    fprintf(stderr, "Cyclic update detected.\n");
#ifdef CREME_DEBUG_UPDATE_CYCLE
    assert(
      (value->update_token != token) &&
      ((value->update_seen & (0x1 << parent_index)) == 0)
    );
#endif
    return value->absolute;
  }

  value->update_seen |= 0x1 << parent_index;

  if (reduce == NULL) reduce = cm_reduce_first;
  for (i = 0; i < value->upstream_count; i++) {
    values[i] = value->upstream[i]->absolute;
  }
  cm_value_set_with_token(value,
                          reduce(values, value->upstream_count) + value->offset,
                          token);
  return value->absolute;
}


void cm_value_set(struct cm_value * value, float absolute) {
  /* we actually don't care if its 100% random or if its truly unique
   * in each program execution.
   * we just care its different each time this function is called */
  int token = rand();
  value->update_token = token;
  return cm_value_set_with_token(value, absolute, token);
}

void cm_value_set_with_token(
  struct cm_value * value,
  float absolute,
  int token
) {
  /* prevent changing if absolute is the same */
  if (value->absolute == absolute) return;
  value->absolute = absolute;
  uint16_t i = 0;
  for (i = 0; i < value->downstream_count; i++)
    cm_value_update_with_token(
      value->downstream[i],
      token,
      value->index_at_downstream[i]
    );
}

float cm_value_get(struct cm_value const * value) {
  return value->absolute;
}

float cm_reduce_first(const float * values, uint16_t values_count) {
  if (values_count == 0) return 0;
  return values[0];
}

float cm_reduce_average(const float * values, uint16_t values_count) {
  float acc = 0.0f;
  uint16_t i = 0;
  for (i = 0; i < values_count; i++) acc += values[i];
  return acc / values_count;
}

float cm_reduce_max(const float * values, uint16_t values_count) {
  int i = 0;
  float max = 0.0f;
  if (values_count == 0) return 0.0f;
  for (i = 0; i < values_count; i++)
    if (values[i] > max) max = values[i];
  return max;
}

float cm_reduce_min(const float * values, uint16_t values_count) {
  int i = 0;
  float min = 0.0f;
  if (values_count == 0) return 0.0f;
  for (i = 0; i < values_count; i++)
    if (values[i] < min) min = values[i];
  return min;
}




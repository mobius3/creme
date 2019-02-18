#include "value.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#ifdef CREME_DEBUG_UPDATE_CYCLE
#include <assert.h>
#endif


float cm_value_update_with_token(struct cm_value * value, int token);

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

enum cm_value_link_result
cm_value_link(struct cm_value * value, struct cm_value * up) {
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
  value->upstream_count += 1;
  up->downstream_count += 1;

  cm_value_update(value);

  return cm_value_link__ok;
}


void cm_value_unlink(struct cm_value * value, struct cm_value * up) {
  uint16_t up_i = 0, down_i = 0;

  // find up index in value's upstream;
  for (up_i = 0; up_i < value->upstream_count; up_i++) {
    if (value->upstream[up_i] == up) break;
  }
  // up is not an upstream of value
  if (up_i == value->upstream_count) return;
  value->upstream[up_i] = value->upstream[value->upstream_count - 1];
  value->upstream_count--;

  // find value index in up downstream
  for (down_i = 0; down_i < up->downstream_count; down_i++) {
    if (up->downstream[down_i] == value) break;
  }
  // wat, value is not a downstream of up, something is broken;
  if (down_i == up->downstream_count) return;
  up->downstream[down_i] = up->downstream[up->downstream_count - 1];
  up->downstream_count--;

  if (value->downstream_count == 0) return;
  else cm_value_update(value);
}

void cm_value_unlink_all_upstream(struct cm_value * value) {
  int i = 0;
  int j = 0;
  struct cm_value * up;
  for (i = 0; i < value->upstream_count; value++) {
    up = value->upstream[i];
    for (j = 0; j < up->downstream_count; j++) {
      if (up->downstream[j] == value) break;
    }
    if (j != up->downstream_count) {
      up->downstream[j] = up->downstream[up->downstream_count - 1];
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
  return cm_value_update_with_token(value, token);
}


float cm_value_update_with_token(struct cm_value * value, int token) {
  cm_reduce_fn reduce = value->reduce_fn;
  float values[CREME_MAX_VALUE_UPSTREAM];
  uint16_t i = 0;

  if (value->update_token == token) {
    fprintf(stderr, "Cyclic update detected.\n");
#ifdef CREME_DEBUG_UPDATE_CYCLE
    assert(value->update_token != token);
#endif
    return value->absolute;
  }
  value->update_token = token;

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
  int token = rand();
  value->update_token = token;
  return cm_value_set_with_token(value, absolute, token);
}

void cm_value_set_with_token(
  struct cm_value * value,
  float absolute,
  int token
) {
  value->absolute = absolute;
  uint16_t i = 0;
  for (i = 0; i < value->downstream_count; i++)
    cm_value_update_with_token(value->downstream[i], token);
}

float cm_value_get(struct cm_value * value) {
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




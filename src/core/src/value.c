#include "value.h"


#ifdef CREME_DEBUG_UPDATE_CYCLE
#include <math.h>
#include <stdio.h>
#endif


static void cm_value_set_recursive(
  struct cm_value * value,
  float absolute,
  int parent_index,
  uint32_t depth
);
static float cm_value_calculate_absolute(struct cm_value * value);
static void cm_value_debug_print(const struct cm_value * value, uint32_t depth);

void
cm_value_construct_reduce(
  struct cm_value * value,
  struct cm_value_reduce reduce
) {
  cm_value_construct(value);
  value->reduce = reduce;
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
  value->offset = 0;
  for (i = 0; i < 16; i++) value->upstream[i] = NULL;
  for (i = 0; i < 16; i++) value->downstream[i] = NULL;
  value->upstream_count = 0;
  value->downstream_count = 0;
  value->reduce = cm_reduce_first;
  value->tag[0] = 0;
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
cm_value_link(struct cm_value * value, struct cm_value * up, float offset) {
  cm_value_unlink_all_upstream(value);
  value->offset = offset;
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
  up->index_at_downstream[down_i] = up->index_at_downstream[
    up->downstream_count - 1];
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
      up->index_at_downstream[j] = up->index_at_downstream[
        up->downstream_count - 1];
      up->downstream_count--;
    }
  }
  value->upstream_count = 0;
}


void cm_value_unlink_all_downstream(struct cm_value * value) {
  while (value->downstream_count > 0)
    cm_value_unlink(value->downstream[0], value);
}

float cm_value_get(struct cm_value const * value) {
  return value->absolute;
}

void
cm_value_set_reduce(struct cm_value * value, struct cm_value_reduce reduce) {
  value->reduce = reduce;
  cm_value_update(value);
}

void cm_value_set_tag(struct cm_value * value, const char tag[7]) {
  int i = 0;
  for (i = 0; i < 7 && tag[i] != 0; i++) {
    value->tag[i] = tag[i] == 0 ? ' ' : tag[i];
  }
  for (; i < 7; i++) value->tag[i] = ' ';
  value->tag[7] = 0;
}

void cm_value_set(struct cm_value * value, float absolute) {
  cm_value_set_recursive(value, absolute, -1, 0);
}

void cm_value_update(struct cm_value * value) {
  float absolute = cm_value_calculate_absolute(value);
  cm_value_set(value, absolute);
}

void cm_value_set_recursive(struct cm_value * value, float absolute, int parent_index, uint32_t depth) {
  if (value->absolute == absolute) return;
  value->absolute = absolute;

#ifdef CREME_DEBUG_UPDATE_CYCLE
  cm_value_debug_print(value, depth);
#endif

  uint32_t parent_bit = 0;
  if (parent_index == -1) {
    value->update_seen = 0;
    parent_bit = 0;
  } else parent_bit = 1u << (uint32_t) parent_index;

  if (value->update_seen & parent_bit) {
    fprintf(stderr, "cyclic update.\n");
  }

  for (uint8_t i = 0; i < value->downstream_count; i++) {
    struct cm_value * downstream = value->downstream[i];
    if ((value->update_seen & parent_bit) == 0) downstream->update_seen = 0;
    int index_at_downstream = value->index_at_downstream[i];
    float downstream_absolute = cm_value_calculate_absolute(downstream);
    cm_value_set_recursive(
      value->downstream[i],
      downstream_absolute,
      index_at_downstream,
      depth + 1
    );
  }
}

void cm_value_debug_print(const struct cm_value * value, uint32_t depth) {
  printf("%*s %s", depth * 2, "", value->tag);
  if (value->upstream_count > 0) {
    printf("::%s(", value->reduce.tag);
    for (uint8_t i = 0; i < value->upstream_count; i++) {
      printf("%.2f", value->upstream[i]->absolute);
      if (i + 1 < value->upstream_count) printf(", ");
    }
    printf(")");
  }
  printf(" = ");
  if (fabsf(value->offset) > 0) {
    printf("%.2f + %.2f = ", value->absolute - value->offset, value->offset);
  }
  printf("%.2f\n", value->absolute);
}

float cm_value_calculate_absolute(struct cm_value * value) {
  if (value->upstream_count == 0) return value->absolute;
  float upstream_absolutes[CREME_MAX_VALUE_UPSTREAM];
  for (uint8_t i = 0; i < value->upstream_count; i++)
    upstream_absolutes[i] = value->upstream[i]->absolute;

  return value->reduce.reduce_fn
    (
      upstream_absolutes,
      value->upstream_count,
      value->reduce.reduce_data
    ) + value->offset;
}




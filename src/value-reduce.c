#include "value-reduce.h"
#include <stdlib.h>


extern float
cm_reduce_first_fn(float const values[], uint16_t values_count, void * data);


float
cm_reduce_average_fn(float const values[], uint16_t values_count, void * data);


float
cm_reduce_max_fn(float const values[], uint16_t values_count, void * data);


float
cm_reduce_min_fn(float const values[], uint16_t values_count, void * data);

struct cm_value_reduce const cm_reduce_first = {cm_reduce_first_fn, NULL};
struct cm_value_reduce const cm_reduce_average = {cm_reduce_average_fn, NULL};
struct cm_value_reduce const cm_reduce_max = {cm_reduce_max_fn, NULL};
struct cm_value_reduce const cm_reduce_min = {cm_reduce_min_fn, NULL};

float
cm_reduce_first_fn(const float * values, uint16_t values_count, void * data) {
  (void) data;
  if (values_count == 0) return 0;
  return values[0];
}

float
cm_reduce_average_fn(const float * values, uint16_t values_count, void * data) {
  (void) data;
  float acc = 0.0f;
  uint16_t i = 0;
  for (i = 0; i < values_count; i++) acc += values[i];
  return acc / values_count;
}

float cm_reduce_max_fn(const float * values, uint16_t values_count, void * data) {
  (void) data;
  int i = 0;
  float max = 0.0f;
  if (values_count == 0) return 0.0f;
  for (i = 0; i < values_count; i++)
    if (values[i] > max) max = values[i];
  return max;
}

float cm_reduce_min_fn(const float * values, uint16_t values_count, void * data) {
  (void) data;
  int i = 0;
  float min = 0.0f;
  if (values_count == 0) return 0.0f;
  for (i = 0; i < values_count; i++)
    if (values[i] < min) min = values[i];
  return min;
}


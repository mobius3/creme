#ifndef CREME_VALUE_REDUCE_H
#define CREME_VALUE_REDUCE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Specifies the type of a reduce function. These functions take an array
 * of float values corresponding to absolute values of a `cm_value` upstream
 * links and it returns a new float value that will be set in the `cm_value`.
 */
typedef float (* cm_reduce_fn)(
  float const values[],
  uint16_t values_count,
  void * reduce_data
);

struct cm_value_reduce
{
  cm_reduce_fn reduce_fn;
  void * reduce_data;
};

/**
 * Ignores all but the first value in the array and returns it.
 */
extern struct cm_value_reduce const cm_reduce_first;

/**
 * Calculates the average of all values passed in and returns it.
 */
extern struct cm_value_reduce const cm_reduce_average;

/**
 * Finds the maximum value in the value array and returns it.
 */
extern struct cm_value_reduce const cm_reduce_max;

/**
 * Finds the minimum value in the value array and returns it.
 */
extern struct cm_value_reduce const cm_reduce_min;

#ifdef __cplusplus
}
#endif

#endif /* CREME_VALUE_REDUCE_H */

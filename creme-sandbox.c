#include <stdio.h>

#include "value.h"

int main(int argc, char * argv[]) {
  struct cm_value values[12];
  cm_value_construct_max(&values[0]);
  cm_value_construct(&values[1]);
  cm_value_construct(&values[2]);
  cm_value_construct(&values[3]);

  cm_value_set(&values[1], 10);
  cm_value_set(&values[2], 20);
  cm_value_set(&values[3], 30);

  cm_value_link(&values[0], &values[1]);
  cm_value_link(&values[1], &values[2]);
  cm_value_link(&values[2], &values[3]);
  cm_value_link(&values[3], &values[0]);

  return 0;
}
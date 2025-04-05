#include "rand_result.h"

#include <stdlib.h>

void rand_result_clean(
  struct rand_result* rand_result
) {
  free(rand_result->data);
}


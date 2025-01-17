#include "result.h"

#include <stdlib.h>

void result_clean(struct result* result) {
  free(result->data);
}


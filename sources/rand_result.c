#include <rand_result.h>

#include <stdlib.h>

void rand_result_initialize(
  struct rand_result* rand_result,
  unsigned long int length
) {
  rand_result->length = length;

  rand_result->bytes = malloc(
    sizeof(unsigned char) *
    rand_result->length
  );
}

void rand_result_clean(
  struct rand_result* rand_result
) {
  free(
    rand_result->bytes
  );

  rand_result->bytes = (
    (void*)0
  );
}

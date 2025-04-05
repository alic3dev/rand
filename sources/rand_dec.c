#include "rand_dec.h"

#include <stdlib.h>

#include "rand_options.h"
#include "rand_result.h"
#include "rand_source.h"

void rand_dec_get(
  struct rand_result* rand_result,
  struct rand_options* rand_options
) {
  rand_result->length = rand_options->length;
  rand_result->data = malloc(
    sizeof(char) * rand_result->length
  );

  for (
    unsigned int i = 0;
    i < rand_result->length;
    i++
  ) {
    rand_result->data[i] = (
      rand_source_get_int(0, 10) + '0'
    );
  }
}


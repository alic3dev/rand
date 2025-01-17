#include "rand_dec.h"

#include <stdlib.h>

#include "rand_source.h"

#include "options.h"
#include "result.h"

void rand_dec_get(
  struct result* result,
  struct options* options
) {
  result->length = options->length;
  result->data = malloc(
    sizeof(char) * result->length
  );

  for (
    unsigned int i = 0;
    i < result->length;
    i++
  ) {
    result->data[i] = (
      rand_source_get_int(0, 10) + '0'
    );
  }
}


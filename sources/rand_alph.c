#include "rand_alph.h"

#include <stdlib.h>

#include "rand_options.h"
#include "rand_result.h"
#include "rand_source.h"

void rand_alph_get(
  struct rand_result* rand_result,
  struct rand_options* rand_options
) {
  rand_result->length = rand_options->length;
  rand_result->data = malloc(
    sizeof(char) * rand_result->length
  );

  char random_value;

  for (
    unsigned int i = 0;
    i < rand_result->length;
    i++
  ) {
    random_value = rand_source_get_int(0, 52);

    rand_result->data[i] = (
      random_value + (
        random_value > 25 ? 'A' - 26 : 'a'
      )
    );
  }
}


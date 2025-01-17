#include "rand_alph.h"

#include <stdlib.h>

#include "rand_source.h"

#include "options.h"
#include "result.h"

void rand_alph_get(
  struct result* result,
  struct options* options
) {
  result->length = options->length;
  result->data = malloc(
    sizeof(char) * result->length
  );

  char random_value;

  for (
    unsigned int i = 0;
    i < result->length;
    i++
  ) {
    random_value = rand_source_get_int(0, 52);

    result->data[i] = (
      random_value + (
        random_value > 25 ? 'A' - 26 : 'a'
      )
    );
  }
}


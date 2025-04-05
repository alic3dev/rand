#include "rand_hex.h"

#include <stdlib.h>

#include "rand_options.h"
#include "rand_result.h"
#include "rand_source.h"

void rand_hex_get(
  struct rand_result* rand_result,
  struct rand_options* rand_options
) {
  rand_result->length = rand_options->length;
  rand_result->data = malloc(
    sizeof(char) * rand_result->length
  );

  char random_value;

  for (
    unsigned int rand_result_data_index = 0;
    rand_result_data_index < rand_result->length;
    ++rand_result_data_index
  ) {
    random_value = rand_source_get_int(0, 16);

    rand_result->data[
      rand_result_data_index
    ] = (
      random_value + (
        random_value > 9 ? 'A' - 10 : '0'
      )
    );
  }
}


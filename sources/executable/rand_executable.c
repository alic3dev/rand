#include "rand_executable.h"

#include <stdio.h>
#include <stdlib.h>

#include "rand_functions.h"
#include "rand_options.h"
#include "rand_result.h"
#include "rand_source.h"

int rand_executable(int argc, char** argv) {
  struct rand_options* rand_options;
  rand_options = malloc(sizeof(struct rand_options));

  rand_options_parse(
    rand_options,
    argc,
    argv
  );

  if (
    rand_options->help != 0 ||
    rand_options->error != 0
  ) {
    int rand_options_error = rand_options->error;

    free(rand_options);

    return rand_options_error;
  }

  struct rand_source_options* rand_source_options;
  rand_source_options = malloc(
    sizeof(struct rand_source_options)
  );
  rand_source_options->secure = rand_options->secure;
  rand_source_initialize(rand_source_options);
  free(rand_source_options);

  struct rand_result* rand_result;
  rand_result = malloc(sizeof(struct rand_result));

  rand_get(
    rand_result,
    rand_options
  );

  for (
    unsigned int rand_result_data_index = 0;
    rand_result_data_index < rand_result->length;
    ++rand_result_data_index
  ) {
    printf(
      "%c",
      rand_result->data[
        rand_result_data_index
      ]
    );
  }

  printf("\n");

  free(rand_options);

  rand_result_clean(rand_result);
  free(rand_result);

  rand_source_clean();

  return 0;
}


#include <rand_executable.h>

#include <rand_functions.h>
#include <rand_options.h>
#include <rand_print_usage.h>
#include <rand_result.h>
#include <rand_source.h>

#include <stdio.h>
#include <stdlib.h>

int main(
  int length_parameters,
  char** parameters
) {
  struct rand_options rand_options;

  rand_options_parse(
    &rand_options,
    length_parameters,
    parameters
  );

  if (
    rand_options.error != 0
  ) {
    rand_print_usage(1);

    return rand_options.error;
  }

  if (
    rand_options.help != 0
  ) {
    rand_print_usage(0);

    return 0;
  }

  struct rand_source_options rand_source_options;
  rand_source_options.type_source = rand_options.type_source;

  struct rand_source rand_source;

  rand_source_initialize(
    &rand_source,
    &rand_source_options
  );

  struct rand_result rand_result;

  rand_result_initialize(
    &rand_result,
    rand_options.length
  );

  unsigned char status_rand_get = rand_get(
    &rand_source,
    &rand_result,
    &rand_options
  );

  if (
    status_rand_get != 0
  ) {
    fprintf(
      stderr,
      "error_unknown:generating_random_bytes\n"
    );

    rand_result_clean(
      &rand_result
    );

    return 1;
  }

  for (
    unsigned int rand_result_data_index = 0;
    rand_result_data_index < rand_result.length;
    ++rand_result_data_index
  ) {
    printf(
      "%c",
      rand_result.bytes[
        rand_result_data_index
      ]
    );
  }

  printf("\n");

  rand_result_clean(
    &rand_result
  );

  rand_source_clean(
    &rand_source
  );

  return 0;
}

#include "rand.h"

#include <stdio.h>
#include <stdlib.h>

#include "rand_source.h"
#include "rand_functions.h"

#include "options.h"
#include "result.h"

int main(int argc, char** argv) {
  struct options* options;
  options = malloc(sizeof(struct options));

  options_parse(
    options,
    argc,
    argv
  );

  if (
    options->help != 0 ||
    options->error != 0
  ) {
    int error = options->error;
    free(options);
    return error;
  }

  struct source_options* source_options;
  source_options = malloc(
    sizeof(struct source_options)
  );
  source_options->secure = options->secure;
  rand_source_initialize(source_options);
  free(source_options);

  struct result* result;
  result = malloc(sizeof(struct result));

  rand_get(result, options);

  for (
    unsigned int i = 0;
    i < result->length;
    i++
  ) {
    printf("%c", result->data[i]);
  }

  printf("\n");

  free(options);
  result_clean(result);
  free(result);

  rand_source_clean();

  return 0;
}


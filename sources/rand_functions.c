#include "rand_functions.h"

#include <stdio.h>

#include "rand_alph.h"
#include "rand_dec.h"
#include "rand_hex.h"
#include "rand_numalph.h"

#include "result.h"
#include "options.h"

void rand_get(
  struct result* result,
  struct options* options
) {
  void (*rand_function)(
    struct result*,
    struct options*
  );

  switch (options->mode) {
    case alph:
      rand_function = rand_alph_get;
      break;
    case dec:
      rand_function = rand_dec_get;
      break;
    case hex:
      rand_function = rand_hex_get;
      break;
    case numalph:
      rand_function = rand_numalph_get;
      break;
    default:
      fprintf(
        stderr,
        "Unknown mode: %i\n",
        options->mode
      );
      options->error = 1;
      return;
  }

  rand_function(result, options);
}


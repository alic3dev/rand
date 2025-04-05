#include "rand_functions.h"

#include <stdio.h>

#include "rand_alph.h"
#include "rand_dec.h"
#include "rand_hex.h"
#include "rand_numalph.h"
#include "rand_options.h"
#include "rand_result.h"

void rand_get(
  struct rand_result* rand_result,
  struct rand_options* rand_options
) {
  void (*rand_function)(
    struct rand_result*,
    struct rand_options*
  );

  switch (rand_options->mode) {
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
        rand_options->mode
      );
      rand_options->error = 1;
      return;
  }

  rand_function(
    rand_result,
    rand_options
  );
}


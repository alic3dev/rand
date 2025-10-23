#include <rand_functions.h>

#include <rand_alphabetical.h>
#include <rand_decimal.h>
#include <rand_hexadecimal.h>
#include <rand_numeric_alphabetical.h>
#include <rand_options.h>
#include <rand_result.h>

#include <stdio.h>

unsigned char rand_get(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  struct rand_options* rand_options
) {
  rand_get_function rand_get_function;

  switch (rand_options->mode) {
    case rand_mode_alphabetical:
      rand_get_function = rand_alphabetical_get;
      break;
    case rand_mode_decimal:
      rand_get_function = rand_decimal_get;
      break;
    case rand_mode_hexadecimal:
      rand_get_function = rand_hexadecimal_get;
      break;
    case rand_mode_numeric_alphabetical:
      rand_get_function = rand_numeric_alphabetical_get;
      break;
    default:
      fprintf(
        stderr,
        "mode:unknown->{%i}\n",
        rand_options->mode
      );

      rand_options->error = 1;

      return rand_options->error;
  }

  return rand_get_function(
    rand_source,
    rand_result
  );
}

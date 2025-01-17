#include "options.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_usage.h"

void options_parse(
  struct options* options,
  int argc,
  char** argv
) {
  options->length = 10;
  options->mode = hex;
  options->error = 0;
  options->help = 0;
  options->secure = 0;

  struct options_parsing_state state;
  state.mode_set = 0;

  for (int i = 1; i < argc; ++i) {
    if (
      strcmp(argv[i], "-h") == 0 ||
      strcmp(argv[i], "--help") == 0 ||
      strcmp(argv[i], "help") == 0
    ) {
      print_usage(0);
      options->help = 1;
      return;
    } else if (
      strcmp(argv[i], "sec") == 0 ||
      strcmp(argv[i], "-s") == 0 ||
      strcmp (argv[i], "--secure") == 0
    ) {
      if (options->secure != 0) {
        fprintf(
          stderr,
          "Tried to set secure twice\n"
        );
        options->error = 1;
      } else {
        options->secure = 1;
      }
    } else if (strcmp(argv[i], "dec") == 0) {
      options_mode_set(
        dec,
        options,
        &state
      );
    } else if (strcmp(argv[i], "hex") == 0) {
      options_mode_set(
        hex,
        options,
        &state
      );
    } else if (strcmp(argv[i], "alph") == 0) {
      options_mode_set(
        alph,
        options,
        &state
      );
    } else if (strcmp(argv[i], "numalph") == 0) {
      options_mode_set(
        numalph,
        options,
        &state
      );
    } else {
      size_t option_length = strlen(argv[i]);
      unsigned char is_number = 1;

      for (size_t c = 0; c < option_length; ++c) {
        if (
          argv[i][c] < '0' || argv[i][c] > '9'
        ) {
          is_number = 0;
          break;
        }
      }

      if (is_number == 1) {
        options->length = atoi(argv[i]);

        if (options->length <= 0) {
          fprintf(
            stderr,
            "Invalid length: %i\n",
            options->length
          );
          options->error = 1;
        }
      } else {
        fprintf(
          stderr,
          "Unknown option: %s\n",
          argv[i]
        );
        options->error = 1;
      }
    }

    if (options->error != 0) {
      printf("\n");
      print_usage(1);
      return;
    }
  }
}

void options_mode_set(
  enum rand_mode mode,
  struct options* options,
  struct options_parsing_state* state
) {
  if (state->mode_set != 0) {
    fprintf(
      stderr,
      "Tried setting two modes\n"
    );
    options->error = 1;
  } else {
    options->mode = mode;
    state->mode_set = 1;
  }
}


#include "rand_options.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_print_usage.h"

void rand_options_parse(
  struct rand_options* rand_options,
  int parameters_length,
  char** parameters
) {
  rand_options->length = 10;
  rand_options->mode = hex;
  rand_options->error = 0;
  rand_options->help = 0;
  rand_options->secure = 0;

  struct rand_options_parsing_state rand_options_parsing_state;
  rand_options_parsing_state.mode_set = 0;

  for (
    int parameter_index = 1; 
    parameter_index < parameters_length;
    ++parameter_index
  ) {
    if (
      strcmp(parameters[parameter_index], "-h") == 0 ||
      strcmp(parameters[parameter_index], "--help") == 0 ||
      strcmp(parameters[parameter_index], "help") == 0
    ) {
      rand_print_usage(0);
      rand_options->help = 1;
      return;
    } else if (
      strcmp(parameters[parameter_index], "sec") == 0 ||
      strcmp(parameters[parameter_index], "-s") == 0 ||
      strcmp(parameters[parameter_index], "--secure") == 0
    ) {
      if (rand_options->secure != 0) {
        fprintf(
          stderr,
          "Tried to set secure twice\n"
        );
        rand_options->error = 1;
      } else {
        rand_options->secure = 1;
      }
    } else if (strcmp(parameters[parameter_index], "dec") == 0) {
      rand_options_mode_set(
        dec,
        rand_options,
        &rand_options_parsing_state
      );
    } else if (strcmp(parameters[parameter_index], "hex") == 0) {
      rand_options_mode_set(
        hex,
        rand_options,
        &rand_options_parsing_state
      );
    } else if (strcmp(parameters[parameter_index], "alph") == 0) {
      rand_options_mode_set(
        alph,
        rand_options,
        &rand_options_parsing_state
      );
    } else if (strcmp(parameters[parameter_index], "numalph") == 0) {
      rand_options_mode_set(
        numalph,
        rand_options,
        &rand_options_parsing_state
      );
    } else {
      size_t option_length = strlen(parameters[parameter_index]);
      unsigned char is_number = 1;

      for (
        size_t parameter_character_index = 0;
        parameter_character_index < option_length;
        ++parameter_character_index
      ) {
        if (
          parameters[
            parameter_index
          ][
            parameter_character_index
          ] < '0' || 
          parameters[
            parameter_index
          ][
            parameter_character_index
          ] > '9'
        ) {
          is_number = 0;
          break;
        }
      }

      if (is_number == 1) {
        rand_options->length = atoi(parameters[parameter_index]);

        if (rand_options->length <= 0) {
          fprintf(
            stderr,
            "Invalid length: %i\n",
            rand_options->length
          );
          rand_options->error = 1;
        }
      } else {
        fprintf(
          stderr,
          "Unknown option: %s\n",
          parameters[parameter_index]
        );
        rand_options->error = 1;
      }
    }

    if (rand_options->error != 0) {
      printf("\n");
      rand_print_usage(1);
      return;
    }
  }
}

void rand_options_mode_set(
  enum rand_mode rand_mode,
  struct rand_options* rand_options,
  struct rand_options_parsing_state* rand_options_parsing_state
) {
  if (rand_options_parsing_state->mode_set != 0) {
    fprintf(
      stderr,
      "Tried setting two modes\n"
    );
    rand_options->error = 1;
  } else {
    rand_options->mode = rand_mode;
    rand_options_parsing_state->mode_set = 1;
  }
}


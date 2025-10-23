#include <rand_options.h>

#include <rand_mode.h>
#include <rand_source.h>

#include <clic3_char_arrays.h>

#include <stdio.h>

void rand_options_parse(
  struct rand_options* rand_options,
  int parameters_length,
  char** parameters
) {
  rand_options->length = 10;
  rand_options->mode = rand_mode_hexadecimal;
  rand_options->error = 0;
  rand_options->help = 0;
  rand_options->type_source = rand_source_type_default;

  struct rand_options_parsing_state rand_options_parsing_state;
  rand_options_parsing_state.mode_set = 0;

  for (
    int index_parameter = 1; 
    index_parameter < parameters_length;
    ++index_parameter
  ) {
    if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-h",
        "--help",
        "help"
      ) != -1
    ) {
      rand_options->help = 1;
      return;
    } else if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-s",
        "--secure",
        "secure"
      ) != -1
    ) {
      if (
        rand_options->type_source == rand_source_type_secure
      ) {
        fprintf(
          stderr,
          "tried_to_set_secure_more_than_once\n"
        );
        rand_options->error = 1;
      } else {
        rand_options->type_source = rand_source_type_secure;
      }
    } else if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-d",
        "--decimal",
        "decimal"
      ) != -1
    ) {
      rand_options_mode_set(
        rand_mode_decimal,
        rand_options,
        &rand_options_parsing_state
      );
    } else if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-x",
        "--hexadecimal",
        "hexadecimal"
      ) != -1
    ) {
      rand_options_mode_set(
        rand_mode_hexadecimal,
        rand_options,
        &rand_options_parsing_state
      );
    } else if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-a",
        "--alphabetical",
        "alphabetical"
      ) != -1
    ) {
      rand_options_mode_set(
        rand_mode_alphabetical,
        rand_options,
        &rand_options_parsing_state
      );
    } else if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-n",
        "--numeric_alphabetical",
        "numeric_alphabetical"
      ) != -1
    ) {
      rand_options_mode_set(
        rand_mode_numeric_alphabetical,
        rand_options,
        &rand_options_parsing_state
      );
    } else {
      size_t option_length = clic3_char_array_length(
        parameters[
          index_parameter
        ]
      );
      unsigned char is_number = 1;

      for (
        size_t parameter_character_index = 0;
        parameter_character_index < option_length;
        ++parameter_character_index
      ) {
        if (
          parameters[
            index_parameter
          ][
            parameter_character_index
          ] < '0' || 
          parameters[
            index_parameter
          ][
            parameter_character_index
          ] > '9'
        ) {
          is_number = 0;
          break;
        }
      }

      if (
        is_number == 1
      ) {
        unsigned char status_char_array_to_unsigned_long_int = clic3_char_array_to_unsigned_long_int(
          parameters[
            index_parameter
          ],
          &rand_options->length
        );

        if (
          status_char_array_to_unsigned_long_int != 0 ||
          rand_options->length <= 0
        ) {
          fprintf(
            stderr,
            "length:invalid->{%i}\n",
            rand_options->length
          );
          rand_options->error = 1;
        }
      } else {
        fprintf(
          stderr,
          "option:unknown->{%s}\n",
          parameters[index_parameter]
        );
        rand_options->error = 1;
      }
    }

    if (
      rand_options->error != 0
    ) {
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
      "tried_setting_two_modes\n"
    );
    rand_options->error = 1;

    return;
  }

  rand_options->mode = rand_mode;
  rand_options_parsing_state->mode_set = 1;
}

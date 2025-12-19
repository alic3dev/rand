#include <rand_parameters.h>

#include <rand_mode.h>
#include <rand_source.h>

#include <clic3_char_arrays.h>

#include <stdio.h>

void rand_parameters_initialize(
  struct rand_parameters* rand_parameters,
  unsigned long int length,
  enum rand_mode rand_mode,
  enum rand_source_type rand_source_type
) {
  rand_parameters->error = 0;
  rand_parameters->help = 0;
  rand_parameters->length = length;
  rand_parameters->mode = rand_mode;
  rand_parameters->type_source = rand_source_type;
}

void rand_parameters_initialize_default(
  struct rand_parameters* rand_parameters
) {
  rand_parameters_initialize(
    rand_parameters,
    10,
    rand_mode_hexadecimal,
    rand_source_type_default
  );
}

void rand_parameters_parse(
  struct rand_parameters* rand_parameters,
  int parameters_length,
  char** parameters
) {
  rand_parameters_initialize_default(
    rand_parameters
  );

  struct rand_parameters_parsing_state rand_parameters_parsing_state;
  rand_parameters_parsing_state.mode_set = 0;

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
      rand_parameters->help = 1;
      return;
    } else if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-v",
        "--divisive",
        "divisive"
      ) != -1
    ) {
      if (
        rand_parameters->type_source == rand_source_type_default
      ) {
        rand_parameters->type_source = rand_source_type_divisive;
      } else {
        fprintf(
          stderr,
          "tried_to_set_source_more_than_once\n"
        );

        rand_parameters->error = 1;
      }
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
        rand_parameters->type_source == rand_source_type_default
      ) {
        rand_parameters->type_source = rand_source_type_secure;
      } else {
        fprintf(
          stderr,
          "tried_to_set_source_more_than_once\n"
        );

        rand_parameters->error = 1;
      }
    }  else if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-c",
        "--divisive_secure",
        "divisive_secure"
      ) != -1
    ) {
      if (
        rand_parameters->type_source == rand_source_type_default
      ) {
        rand_parameters->type_source = rand_source_type_divisive_secure;
      } else {
        fprintf(
          stderr,
          "tried_to_set_source_more_than_once\n"
        );

        rand_parameters->error = 1;
      }
    } else if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-z",
        "--zac",
        "zac"
      ) != -1
    ) {
      if (
        rand_parameters->type_source == rand_source_type_default
      ) {
        rand_parameters->type_source = rand_source_type_zac;
      } else {
        fprintf(
          stderr,
          "tried_to_set_source_more_than_once\n"
        );

        rand_parameters->error = 1;
      }
    } else if (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        3,
        "-b",
        "--bytes",
        "bytes"
      ) != -1
    ) {
      rand_parameters_mode_set(
        rand_mode_bytes,
        rand_parameters,
        &rand_parameters_parsing_state
      );
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
      rand_parameters_mode_set(
        rand_mode_decimal,
        rand_parameters,
        &rand_parameters_parsing_state
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
      rand_parameters_mode_set(
        rand_mode_hexadecimal,
        rand_parameters,
        &rand_parameters_parsing_state
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
      rand_parameters_mode_set(
        rand_mode_alphabetical,
        rand_parameters,
        &rand_parameters_parsing_state
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
      rand_parameters_mode_set(
        rand_mode_numeric_alphabetical,
        rand_parameters,
        &rand_parameters_parsing_state
      );
    } else {
      unsigned int parameter_length = clic3_char_array_length(
        parameters[
          index_parameter
        ]
      );
      unsigned char is_number = 1;

      for (
        unsigned int parameter_character_index = 0;
        parameter_character_index < parameter_length;
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
          &rand_parameters->length
        );

        if (
          status_char_array_to_unsigned_long_int != 0 ||
          rand_parameters->length <= 0
        ) {
          fprintf(
            stderr,
            "length:invalid->{%lu}\n",
            rand_parameters->length
          );
          rand_parameters->error = 1;
        }
      } else {
        fprintf(
          stderr,
          "parameter:unknown->{%s}\n",
          parameters[index_parameter]
        );
        rand_parameters->error = 1;
      }
    }

    if (
      rand_parameters->error != 0
    ) {
      return;
    }
  }
}

void rand_parameters_mode_set(
  enum rand_mode rand_mode,
  struct rand_parameters* rand_parameters,
  struct rand_parameters_parsing_state* rand_parameters_parsing_state
) {
  if (
    rand_parameters_parsing_state->mode_set != 0
  ) {
    fprintf(
      stderr,
      "tried_setting_two_modes\n"
    );
    rand_parameters->error = 1;

    return;
  }

  rand_parameters->mode = rand_mode;
  rand_parameters_parsing_state->mode_set = 1;
}

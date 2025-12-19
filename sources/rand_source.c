#include <rand_source.h>

#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_source_divisive_data.h>
#include <rand_source_divisive_secure_data.h>
#include <rand_source_secure_data.h>
#include <rand_source_zac_data.h>

#include <stdlib.h>
#include <sys/time.h>
#include <timingsafe.h>

void rand_source_initialize(
  struct rand_source* rand_source,
  struct rand_source_parameters* rand_source_parameters
) {
  rand_source_seed_by_time(
    rand_source
  );

  rand_source->type_source = rand_source_parameters->type_source;
  rand_source->data = (void*)0;

  switch (rand_source->type_source) {
    case rand_source_type_divisive_secure:
      rand_source->rand = rand_source_divisive_secure;
      rand_source->data = malloc(
        sizeof(struct rand_source_divisive_secure_data)
      );

      struct rand_source_divisive_secure_data* rand_source_divisive_secure_data = (
        rand_source->data
      );

      rand_source_divisive_secure_data->timingsafe_token = (
        timingsafe_enable_if_supported()
      );

      rand_source_divisive_data_initialize(
        &rand_source_divisive_secure_data->rand_source_divisive_data
      );

      break;
    case rand_source_type_divisive:
      rand_source->rand = rand_source_divisive;
      rand_source->data = malloc(
        sizeof(struct rand_source_divisive_data)
      );

      rand_source_divisive_data_initialize(
        rand_source->data
      );
      
      break;
    case rand_source_type_secure:
      rand_source->rand = rand_source_rand_secure;
      rand_source->data = malloc(
        sizeof(struct rand_source_secure_data)
      );

      struct rand_source_secure_data* rand_source_secure_data = (
        rand_source->data
      );

      rand_source_secure_data->timingsafe_token = (
        timingsafe_enable_if_supported()
      );

      rand_source_secure_data->urandom = fopen(
        "/dev/urandom",
        "rb"
      );

      break;
    case rand_source_type_zac:
      rand_source->rand = rand_source_zac;
      rand_source->data = malloc(
        sizeof(struct rand_source_zac_data)
      );

      rand_source_zac_data_initialize(
        rand_source->data
      );
      break;
    case rand_source_type_default:
    default:
      rand_source->rand = rand_source_rand;
      rand_source->data = (void*)0;
      break;
  }
}

void rand_source_seed_by_time(
  struct rand_source* rand_source
) {
  struct timeval time;

  gettimeofday(
    &time,
    (void*)0
  );

  srand(
    time.tv_sec * 1000000 +
    time.tv_usec
  );
}

unsigned char rand_source_divisive_secure(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  struct rand_source_divisive_secure_data* rand_source_divisive_secure_data = (
    rand_source->data
  );

  struct rand_source_divisive_data* rand_source_divisive_data = (
    &rand_source_divisive_secure_data->rand_source_divisive_data
  );

  return rand_source_divisive_from_data(
    rand_source_divisive_data,
    rand_result,
    rand_source_get_bytes_transform_function
  );
}

unsigned char rand_source_divisive(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  struct rand_source_divisive_data* rand_source_divisive_data = (
    rand_source->data
  );

  return rand_source_divisive_from_data(
    rand_source_divisive_data,
    rand_result,
    rand_source_get_bytes_transform_function
  );
}

unsigned char rand_source_divisive_from_data(
  struct rand_source_divisive_data* rand_source_divisive_data,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  for (
    unsigned long int index_byte = 0;
    index_byte < rand_result->length;
    ++index_byte
  ) {
    do {
      rand_source_divisive_data->value = (
        rand_source_divisive_data->value / 2.0f
      );
    } while (
      rand_source_divisive_data->value > 1.0f
    );

    float value = (
      (rand_source_divisive_data->value - 0.5f) /
      0.5f
    );

    unsigned char index_generation_distribution = (
      value * 100.0f
    );

    rand_source_divisive_data->generation_distributions[
      index_generation_distribution
    ] = (
      (rand_source_divisive_data->generation_distributions[
        index_generation_distribution
      ] + 1) %
      (index_generation_distribution + 3)
    );

    if (
      (index_generation_distribution + 1) % (
        rand_source_divisive_data->generation_distributions[
          index_generation_distribution
        ]
      ) == 0
    ) {
      value = 1.0f - value;
    }

    rand_result->bytes[
      index_byte
    ] = rand_source_get_bytes_transform_function(
      value * 256
    );

    rand_source_divisive_data->value = (
      rand_source_divisive_data->value * rand_source_divisive_data->multiplier
    );
  }

  return 0;
}

unsigned char rand_source_rand(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  for (
    unsigned long int index_byte = 0;
    index_byte < rand_result->length;
    ++index_byte
  ) {
    rand_result->bytes[
      index_byte
    ] = rand_source_get_bytes_transform_function(
      rand() % 256
    );
  }

  return 0;
}

unsigned char rand_source_rand_secure(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  struct rand_source_secure_data* rand_source_secure_data = (
    rand_source->data
  );

  unsigned char length_preliminary_rand_calls = (
    rand() % 256
  );

  for (
    unsigned char index_rand_calls = 0;
    index_rand_calls < length_preliminary_rand_calls;
    ++index_rand_calls
  ) {
    rand();
  }

  for (
    unsigned long int index_byte = 0;
    index_byte < rand_result->length;
    ++index_byte
  ) {
    int random_value = rand();
    int add_rand_calls = rand() % 100;

    unsigned int rand_source_index = (
      add_rand_calls % 8 == 0
      ? 1
      : 0
    );

    for (
      int index_rand_calls = 0;
      index_rand_calls < add_rand_calls;
      ++index_rand_calls
    ) {
      rand_source_index = (
        rand_source_index == 0
        ? rand() % 8
        : fgetc(
          rand_source_secure_data->urandom
        ) % 8
      );

      if (
        rand_source_index == 0
      ) {
        random_value = (
          random_value + rand()
        ) % RAND_MAX;
      } else {
        unsigned int length_characters = fgetc(
          rand_source_secure_data->urandom
        );

        for (
          unsigned int index_character = 0;
          index_character <= length_characters;
          ++index_character
        ) {
          random_value = (
            random_value + (
              fgetc(
                rand_source_secure_data->urandom
              )
            ) % RAND_MAX
          );
        }
      }
    }

    rand_result->bytes[
      index_byte
    ] = rand_source_get_bytes_transform_function(
      random_value % 256
    );
  }

  return 0;
}

unsigned char rand_source_zac(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  struct rand_source_zac_data* rand_source_zac_data = (
    rand_source->data
  );

  for (
    unsigned long int index_byte = 0;
    index_byte < rand_result->length;
    ++index_byte
  ) {
    rand_result->bytes[
      index_byte
    ] = rand_source_get_bytes_transform_function(
      -rand_source_zac_data->value
    );

    switch (
      rand_source_zac_data->step
    ) {
      case 0: {
        rand_source_zac_data->value += 2;
        break;
      }
      case 1: {
        rand_source_zac_data->value -= 6;
        break;
      }
      case 2: {
        rand_source_zac_data->value += 1;
        break;
      }
      case 3: {
        rand_source_zac_data->value -= 3;
        break;
      }
    }

    rand_source_zac_data->step = (
      rand_source_zac_data->step +
      1
    ) % 4;
  }

  return 0;
}

unsigned char rand_source_get_bytes(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  return rand_source->rand(
    rand_source,
    rand_result,
    rand_source_get_bytes_transform_function
  );
}

void rand_source_clean(
  struct rand_source* rand_source
) {
  switch (
    rand_source->type_source
  ) {
    case rand_source_type_divisive: {
      free(
        rand_source->data
      );

      break;
    }
    case rand_source_type_divisive_secure: {
      struct rand_source_divisive_secure_data* rand_source_divisive_secure_data = (
        rand_source->data
      );

      timingsafe_restore_if_supported(
        rand_source_divisive_secure_data->timingsafe_token
      );

      free(
        rand_source->data
      );

      break;
    }
    case rand_source_type_secure: {
      struct rand_source_secure_data* rand_source_secure_data = (
        rand_source->data
      );

      timingsafe_restore_if_supported(
        rand_source_secure_data->timingsafe_token
      );

      fclose(
        rand_source_secure_data->urandom
      );

      free(
        rand_source->data
      );

      break;
    }
    default: {
      break;
    }
  }
}

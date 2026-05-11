#include <rand_source.h>

#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_seed.h>
#include <rand_source_divisive_data.h>

#include <clic3_memory.h>

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

  rand_source->type_source = (
    rand_source_parameters->type_source
  );

  rand_source->data = (
    0x00
  );

  switch (
    rand_source->type_source
  ) {
    case rand_source_type_divisive: {
      rand_source->rand = (
        rand_source_divisive
      );

      rand_source->data = (
        clic3_memory_allocate_raw(
          sizeof(
            struct rand_source_divisive_data
          )
        )
      );

      rand_source_divisive_data_initialize(
        rand_source->data
      );

      break;
    }
    case rand_source_type_default:
    default: {
      rand_source->rand = (
        rand_source_rand
      );

      rand_source->data = (
        0
      );

      break;
    }
  }
}

void rand_source_seed_by_time(
  struct rand_source* rand_source
) {
  struct timeval time;

  gettimeofday(
    &time,
    0
  );

  srand(
    time.tv_sec *
    1000000 +
    time.tv_usec
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
        (
          rand_source_divisive_data->value /
          2.0f
        ) + (
          rand_source_divisive_data->value / (
            (
              (
                index_byte %
                100
              ) +
              1
            ) *
            100.0f
          )
        )
      );
    } while (
      rand_source_divisive_data->value > 1.0f
    );

    float value = (
      (
        rand_source_divisive_data->value -
        0.5f
      ) /
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
      value *
      256
    );

    rand_source_divisive_data->value = (
      rand_source_divisive_data->value *
      rand_source_divisive_data->multiplier
    );
  }

  return 0;
}

unsigned char rand_source_rand(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  rand_seed_generate(
    rand_result->bytes,
    rand_result->length
  );

  for (
    unsigned long int index_byte = (
      0x00
    );
    (
      index_byte <
      rand_result->length
    );
    ++index_byte
  ) {
    rand_result->bytes[
      index_byte
    ] = (
      rand_source_get_bytes_transform_function(
        rand_result->bytes[
          index_byte
        ]
      )
    );
  }

  return (
    0x00
  );
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
      rand_source_divisive_data_clean(
        rand_source->data
      );

      clic3_memory_free_raw(
        rand_source->data
      );

      break;
    }
    default: {
      break;
    }
  }
}

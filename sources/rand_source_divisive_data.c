#include <rand_source_divisive_data.h>

#include <rand_seed.h>

#include <clic3_memory.h>

#include <stdio.h>

void rand_source_divisive_data_initialize(
  struct rand_source_divisive_data* rand_source_divisive_data
) {
  rand_source_divisive_data_initialize_with_seed_length(
    rand_source_divisive_data,
    rand_source_divisive_bytes_seed_default
  );
}

void rand_source_divisive_data_initialize_with_seed_length(
  struct rand_source_divisive_data* rand_source_divisive_data,
  unsigned short int length_seed
) {
  rand_source_divisive_data->length_seed = (
    length_seed
  );

  rand_source_divisive_data->seed = (
    clic3_memory_allocate_raw(
      rand_source_divisive_data->length_seed
    )
  );

  rand_source_divisive_data_seed_generate(
    rand_source_divisive_data->seed,
    rand_source_divisive_data->length_seed
  );

  rand_source_divisive_data_initialize_preseeded(
    rand_source_divisive_data
  );
}

void rand_source_divisive_data_seed_generate(
  unsigned char* seed,
  unsigned short int length_seed
) {
  rand_seed_generate(
    seed,
    length_seed
  );
}

void rand_source_divisive_data_reseed(
  struct rand_source_divisive_data* rand_source_divisive_data
) {
  rand_source_divisive_data_seed_generate(
    rand_source_divisive_data->seed,
    rand_source_divisive_data->length_seed
  );

  rand_source_divisive_data_initialize_multiplier_value(
    rand_source_divisive_data
  );
}

void rand_source_divisive_data_reseed_additive(
  struct rand_source_divisive_data* rand_source_divisive_data
) {
  rand_seed_generate(
    rand_source_divisive_data->seed,
    rand_source_divisive_data->length_seed
  );

  rand_source_divisive_data_initialize_multiplier_value(
    rand_source_divisive_data
  );
}

void rand_source_divisive_data_reseed_with_seed(
  struct rand_source_divisive_data* rand_source_divisive_data,
  unsigned char* seed,
  unsigned short int length_seed
) {
  if (
    rand_source_divisive_data->length_seed > length_seed
  ) {
    clic3_memory_reallocate_raw(
      &rand_source_divisive_data->seed,
      length_seed
    );
  } else if (
    rand_source_divisive_data->length_seed < length_seed
  ) {
    clic3_memory_reallocate_raw(
      &rand_source_divisive_data->seed,
      length_seed
    );

    for (
      unsigned short int index_byte_seed = rand_source_divisive_data->length_seed;
      index_byte_seed < length_seed;
      ++index_byte_seed
    ) {
      rand_source_divisive_data->seed[
        index_byte_seed
      ] = (
        0x00
      );
    }
  }

  rand_source_divisive_data->length_seed = (
    length_seed
  );

  for (
    unsigned short int index_byte_seed = 0;
    index_byte_seed < rand_source_divisive_data->length_seed;
    ++index_byte_seed
  ) {
    rand_source_divisive_data->seed[
      index_byte_seed
    ] = (
      seed[
        index_byte_seed
      ]
    );
  }

  rand_source_divisive_data_initialize_multiplier_value(
    rand_source_divisive_data
  );
}

void rand_source_divisive_data_reseed_with_seed_additive(
  struct rand_source_divisive_data* rand_source_divisive_data,
  unsigned char* seed,
  unsigned short int length_seed
) {
  if (
    rand_source_divisive_data->length_seed > length_seed
  ) {
    clic3_memory_reallocate_raw(
      &rand_source_divisive_data->seed,
      length_seed
    );
  } else if (
    rand_source_divisive_data->length_seed < length_seed
  ) {
    clic3_memory_reallocate_raw(
      &rand_source_divisive_data->seed,
      length_seed
    );

    for (
      unsigned short int index_byte_seed = rand_source_divisive_data->length_seed;
      index_byte_seed < length_seed;
      ++index_byte_seed
    ) {
      rand_source_divisive_data->seed[
        index_byte_seed
      ] = (
        0x00
      );
    }
  }

  rand_source_divisive_data->length_seed = (
    length_seed
  );

  for (
    unsigned short int index_byte_seed = 0;
    index_byte_seed < rand_source_divisive_data->length_seed;
    ++index_byte_seed
  ) {
    rand_source_divisive_data->seed[
      index_byte_seed
    ] = (
      rand_source_divisive_data->seed[
        index_byte_seed
      ] +
      seed[
        index_byte_seed
      ]
    );
  }

  rand_source_divisive_data_initialize_multiplier_value(
    rand_source_divisive_data
  );
}

void rand_source_divisive_data_initialize_seeded(
  struct rand_source_divisive_data* rand_source_divisive_data,
  unsigned char* rand_source_divisive_data_seed,
  unsigned short int rand_source_divisive_data_length_seed
) {
  rand_source_divisive_data->length_seed = (
    rand_source_divisive_data_length_seed
  );

  rand_source_divisive_data->seed = (
    clic3_memory_allocate_raw(
      rand_source_divisive_data->length_seed
    )
  );

  for (
    unsigned short int index_byte_seed = 0;
    index_byte_seed < rand_source_divisive_data->length_seed;
    ++index_byte_seed
  ) {
    rand_source_divisive_data->seed[
      index_byte_seed
    ] = (
      rand_source_divisive_data_seed[
        index_byte_seed
      ]
    );
  }

  rand_source_divisive_data_initialize_preseeded(
    rand_source_divisive_data
  );
}

void rand_source_divisive_data_initialize_preseeded(
  struct rand_source_divisive_data* rand_source_divisive_data
) {
  rand_source_divisive_data->multiplier = (
    2.0f
  );

  rand_source_divisive_data->value = (
    2.0f
  );

  rand_source_divisive_data_initialize_multiplier_value(
    rand_source_divisive_data
  );
}

void rand_source_divisive_data_initialize_multiplier_value(
  struct rand_source_divisive_data* rand_source_divisive_data
) {
  for (
    unsigned short int index_byte_seed = 0;
    index_byte_seed < rand_source_divisive_data->length_seed;
    ++index_byte_seed
  ) {
    if (
      index_byte_seed % 2 == 0
    ) {
      if (
        index_byte_seed % 6 == 0
      ) {
        rand_source_divisive_data->multiplier = (
          rand_source_divisive_data->multiplier +
          (float) rand_source_divisive_data->seed[
            index_byte_seed
          ] /
          100000.0f
        );
      } else if (
        index_byte_seed % 4 == 0
      ) {
        rand_source_divisive_data->multiplier = (
          rand_source_divisive_data->multiplier +
          (float) rand_source_divisive_data->seed[
            index_byte_seed
          ]
        );
      } else {
        rand_source_divisive_data->multiplier = (
          rand_source_divisive_data->multiplier *
          (float) rand_source_divisive_data->seed[
            index_byte_seed
          ]
        );
      }

      if (
        rand_source_divisive_data->multiplier >
        0xfffd
      ) {
        rand_source_divisive_data->multiplier = (
          rand_source_divisive_data->multiplier -
          (unsigned int) (
            rand_source_divisive_data->multiplier /
            (float) 0xfffd
          ) * (
            (float) 0xfffd
          )
        );
      }
    } else {
      if (
        (
          index_byte_seed +
          1
        ) % 6 == 0
      ) {
        rand_source_divisive_data->value = (
          rand_source_divisive_data->value +
          (float) rand_source_divisive_data->seed[
            index_byte_seed
          ] /
          100000.0f
        );
      } else if (
        (
          index_byte_seed +
          1
        ) % 4 == 0
      ) {
        rand_source_divisive_data->value = (
          (
            rand_source_divisive_data->value +
            rand_source_divisive_data->seed[
              index_byte_seed
            ]
          )
        );
      } else {
        rand_source_divisive_data->value = (
          (
            rand_source_divisive_data->value *
            rand_source_divisive_data->seed[
              index_byte_seed
            ]
          )
        );
      }

      if (
        rand_source_divisive_data->value >
        0xfffd
      ) {
        rand_source_divisive_data->value = (
          rand_source_divisive_data->value -
          (unsigned int) (
            rand_source_divisive_data->value /
            (float) 0xfffd
          ) * (
            (float) 0xfffd
          )
        );
      }
    }
  }

  rand_source_divisive_data->multiplier = (
    rand_source_divisive_data->multiplier +
    2.0f
  );

  rand_source_divisive_data->value = (
    rand_source_divisive_data->value +
    2.0f
  );
}

void rand_source_divisive_data_clean(
  struct rand_source_divisive_data* rand_source_divisive_data
) {
  clic3_memory_free_raw(
    rand_source_divisive_data->seed
  );
}

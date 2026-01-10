#ifndef __rand_source_divisive_data_h
#define __rand_source_divisive_data_h

#define rand_source_divisive_length_generation_distributions 100

#define rand_source_divisive_bytes_seed_default 4096

struct rand_source_divisive_data {
  unsigned char generation_distributions[
    rand_source_divisive_length_generation_distributions
  ];
  float multiplier;

  unsigned char* seed;
  unsigned short int length_seed;

  float value;
};

void rand_source_divisive_data_initialize(
  struct rand_source_divisive_data*
);

void rand_source_divisive_data_initialize_with_seed_length(
  struct rand_source_divisive_data*,
  unsigned short int
);

void rand_source_divisive_data_seed_generate(
  unsigned char*,
  unsigned short int
);

void rand_source_divisive_data_reseed(
  struct rand_source_divisive_data*
);

void rand_source_divisive_data_reseed_additive(
  struct rand_source_divisive_data*
);

void rand_source_divisive_data_reseed_with_seed(
  struct rand_source_divisive_data*,
  unsigned char*,
  unsigned short int
);

void rand_source_divisive_data_reseed_with_seed_additive(
  struct rand_source_divisive_data*,
  unsigned char*,
  unsigned short int
);

void rand_source_divisive_data_initialize_seeded(
  struct rand_source_divisive_data*,
  unsigned char*,
  unsigned short int
);

void rand_source_divisive_data_initialize_preseeded(
  struct rand_source_divisive_data*
);

void rand_source_divisive_data_initialize_multiplier_value(
  struct rand_source_divisive_data*
);

void rand_source_divisive_data_clean(
  struct rand_source_divisive_data*
);

#endif

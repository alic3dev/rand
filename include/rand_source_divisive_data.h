#ifndef __rand_source_divisive_data_h
#define __rand_source_divisive_data_h

#define rand_source_divisive_length_generation_distributions 100

struct rand_source_divisive_data {
  unsigned char generation_distributions[
    rand_source_divisive_length_generation_distributions
  ];
  float multiplier;
  float seed;
  float value;
};

void rand_source_divisive_data_initialize(
  struct rand_source_divisive_data*
);

#endif

#ifndef __rand_source_h
#define __rand_source_h

#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_source_type.h>

#include <stdio.h>

#define rand_source_divisive_length_generation_distributions 100

struct rand_source;

typedef unsigned char (*rand_source_get_bytes_transform_function)(unsigned char);

typedef unsigned char (*rand_source_function)(
  struct rand_source*,
  struct rand_result*,
  rand_source_get_bytes_transform_function
);

struct rand_source_divisive_data {
  unsigned char generation_distributions[
    rand_source_divisive_length_generation_distributions
  ];
  float multiplier;
  float seed;
  float value;
};

struct rand_source {
  enum rand_source_type type_source;
  rand_source_function rand;
  void* data;
};

struct rand_source_parameters {
  enum rand_source_type type_source;
};

void rand_source_initialize(
  struct rand_source*,
  struct rand_source_parameters*
);

void rand_source_seed_by_time(
  struct rand_source*
);

unsigned char rand_source_divisive(
  struct rand_source*,
  struct rand_result*,
  rand_source_get_bytes_transform_function
);

unsigned char rand_source_rand(
  struct rand_source*,
  struct rand_result*,
  rand_source_get_bytes_transform_function
);

unsigned char rand_source_rand_secure(
  struct rand_source*,
  struct rand_result*,
  rand_source_get_bytes_transform_function
);

unsigned char rand_source_get_bytes(
  struct rand_source*,
  struct rand_result*,
  rand_source_get_bytes_transform_function
);

void rand_source_clean(
  struct rand_source*
);

#endif

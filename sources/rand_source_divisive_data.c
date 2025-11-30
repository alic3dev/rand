#include <rand_source_divisive_data.h>

#include <stdio.h>

void rand_source_divisive_data_initialize(
  struct rand_source_divisive_data* rand_source_divisive_data
) {
  void* urandom = fopen(
    "/dev/urandom",
    "rb"
  );

  rand_source_divisive_data->multiplier = (
    ((fgetc(urandom) + fgetc(urandom)) % 0xfffd) +
    ((float) (fgetc(urandom) + fgetc(urandom)) / 100000.0f)
  ) + 2.0f;

  rand_source_divisive_data->seed = (
    (fgetc(urandom) * fgetc(urandom)) % 0xfffd
  ) + 2.0f;

  rand_source_divisive_data->value = (
    rand_source_divisive_data->seed
  );

  fclose(urandom);
}

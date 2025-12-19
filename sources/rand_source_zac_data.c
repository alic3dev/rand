#include <rand_source_zac_data.h>

#include <stdio.h>

void rand_source_zac_data_initialize(
  struct rand_source_zac_data* rand_source_zac_data
) {
  void* urandom = fopen(
    "/dev/urandom",
    "rb"
  );

  rand_source_zac_data->step = 0;
  rand_source_zac_data->value = rand_source_zac_data->value = fgetc(
    urandom
  ) * fgetc(
    urandom
  );

  fclose(urandom);
}

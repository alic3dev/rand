#include <rand_source_zac_data.h>

#include <rand_seed.h>

void rand_source_zac_data_initialize(
  struct rand_source_zac_data* rand_source_zac_data
) {
  rand_source_zac_data->step = 0;

  unsigned char rand_seed_zac[
    0x02
  ];
  
  rand_seed_generate(
    rand_seed_zac,
    0x02
  );

  rand_source_zac_data->value = (
    (
      rand_seed_zac[
        0x00
      ] +
      0x01
    ) *
    (
      rand_seed_zac[
        0x01
      ] +
      0x01
    )
  );
}

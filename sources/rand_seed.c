#include <rand_seed.h>

void rand_seed_generate(
  unsigned char* rand_seed_buffer,
  unsigned char length_rand_seed_buffer
) {
  for (
    unsigned char index_rand_seed = (
      0x00
    );
    (
      index_rand_seed <
      length_rand_seed_buffer
    );
    ++index_rand_seed
  ) {
    rand_seed_buffer[
      index_rand_seed
    ] = (
      0x00
    );
  }
}

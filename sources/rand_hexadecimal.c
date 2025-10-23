#include <rand_hexadecimal.h>

#include <rand_options.h>
#include <rand_result.h>
#include <rand_source.h>

#include <stdlib.h>

unsigned char rand_hexadecimal_get(
  struct rand_source* rand_source,
  struct rand_result* rand_result
) {
  return rand_source_get_bytes(
    rand_source,
    rand_result,
    rand_hexadecimal_transform
  );
}

unsigned char rand_hexadecimal_transform(
  unsigned char byte
) {
  byte = (byte % 16);

  return (
    byte + (
      byte > 9
      ? 'a' - 10
      : '0'
    )
  );
}

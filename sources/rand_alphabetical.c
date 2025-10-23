#include <rand_alphabetical.h>

#include <rand_options.h>
#include <rand_result.h>
#include <rand_source.h>

#include <stdlib.h>

unsigned char rand_alphabetical_get(
  struct rand_source* rand_source,
  struct rand_result* rand_result
) {
  return rand_source_get_bytes(
    rand_source,
    rand_result,
    rand_alphabetical_transform
  );
}

unsigned char rand_alphabetical_transform(
  unsigned char byte
) {
  byte = (byte % 52);

  return (
    byte + (
      byte > 25
      ? 'A' - 26
      : 'a'
    )
  );
}

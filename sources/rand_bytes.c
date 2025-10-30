#include <rand_bytes.h>

#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_source.h>

unsigned char rand_bytes_get(
  struct rand_source* rand_source,
  struct rand_result* rand_result
) {
  return rand_source_get_bytes(
    rand_source,
    rand_result,
    rand_bytes_transform
  );
}

unsigned char rand_bytes_transform(
  unsigned char byte
) {
  return byte;
}

#include <rand_decimal.h>

#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_source.h>

unsigned char rand_decimal_get(
  struct rand_source* rand_source,
  struct rand_result* rand_result
) {
  return rand_source_get_bytes(
    rand_source,
    rand_result,
    rand_decimal_transform
  );
}

unsigned char rand_decimal_transform(
  unsigned char byte
) {
  return (byte % 10) + '0';
}

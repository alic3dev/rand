#ifndef __rand_decimal_h
#define __rand_decimal_h

#include <rand_options.h>
#include <rand_result.h>
#include <rand_source.h>

unsigned char rand_decimal_get(
  struct rand_source*,
  struct rand_result*
);

unsigned char rand_decimal_transform(
  unsigned char
);

#endif

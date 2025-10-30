#ifndef __rand_bytes_h
#define __rand_bytes_h

#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_source.h>

unsigned char rand_bytes_get(
  struct rand_source*,
  struct rand_result*
);

unsigned char rand_bytes_transform(
  unsigned char
);

#endif

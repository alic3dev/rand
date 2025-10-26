#ifndef __rand_alphabetical_h
#define __rand_alphabetical_h

#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_source.h>

unsigned char rand_alphabetical_get(
  struct rand_source*,
  struct rand_result*
);

unsigned char rand_alphabetical_transform(
  unsigned char
);

#endif

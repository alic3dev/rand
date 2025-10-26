#ifndef __rand_functions_h
#define __rand_functions_h

#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_source.h>

typedef unsigned char (*rand_get_function)(
  struct rand_source*,
  struct rand_result*
);

unsigned char rand_get(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  struct rand_parameters* rand_parameters
);

#endif

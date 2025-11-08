#ifndef __rand_initialize_h
#define __rand_initialize_h

#include <rand_mode.h>
#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_source.h>
#include <rand_source_type.h>

void rand_initialize(
  struct rand_parameters*,
  struct rand_result*,
  struct rand_source*,
  unsigned long int,
  enum rand_mode,
  enum rand_source_type
);

#endif

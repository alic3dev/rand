#ifndef __rand_parameters_h
#define __rand_parameters_h

#include <rand_mode.h>
#include <rand_source_type.h>

struct rand_parameters {
  enum rand_mode mode;
  enum rand_source_type type_source;
  unsigned long int length;
  unsigned char help;
  unsigned char error;
};

struct rand_parameters_parsing_state {
  unsigned char mode_set;
};

void rand_parameters_initialize(
  struct rand_parameters*,
  unsigned long int,
  enum rand_mode,
  enum rand_source_type
);

void rand_parameters_initialize_default(
  struct rand_parameters*
);

void rand_parameters_parse(
  struct rand_parameters*,
  int,
  char**
);

void rand_parameters_mode_set(
  enum rand_mode,
  struct rand_parameters*,
  struct rand_parameters_parsing_state*
);

#endif

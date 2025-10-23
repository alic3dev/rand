#ifndef __rand_options_h
#define __rand_options_h

#include <rand_mode.h>
#include <rand_source_type.h>

struct rand_options {
  enum rand_mode mode;
  enum rand_source_type type_source;
  unsigned long int length;
  unsigned char help;
  unsigned char error;
};

struct rand_options_parsing_state {
  unsigned char mode_set;
};

void rand_options_parse(
  struct rand_options*,
  int,
  char**
);

void rand_options_mode_set(
  enum rand_mode,
  struct rand_options*,
  struct rand_options_parsing_state*
);

#endif

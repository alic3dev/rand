#ifndef __RAND_OPTIONS_H
#define __RAND_OPTIONS_H

enum rand_mode {
  hex,
  dec,
  alph,
  numalph
};

struct rand_options {
  unsigned int length;
  enum rand_mode mode;
  unsigned char secure;
  unsigned char help;
  int error;
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


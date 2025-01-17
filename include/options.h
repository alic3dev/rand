#ifndef __OPTIONS_H
#define __OPTIONS_H

enum rand_mode {
  hex,
  dec,
  alph,
  numalph
};

struct options {
  unsigned int length;
  enum rand_mode mode;
  unsigned char secure;
  unsigned char help;
  int error;
};

struct options_parsing_state {
  unsigned char mode_set;
};

void options_parse(
  struct options*,
  int,
  char**
);

void options_mode_set(
  enum rand_mode,
  struct options*,
  struct options_parsing_state*
);

#endif


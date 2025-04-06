#ifndef __RAND_SOURCE_H
#define __RAND_SOURCE_H

#include <stdio.h>
#include <sys/time.h>

struct rand_source {
  unsigned char secure;
  struct timeval* time;
  unsigned int (*rand)();
  FILE* urandom;
};

extern struct rand_source* rand_source;

struct rand_source_options {
  unsigned char secure;
};

void rand_source_initialize(
  struct rand_source_options*
);

void __rand_source_seed_by_time();

unsigned int __rand_source_rand();
unsigned int __rand_source_rand_secure();

unsigned int rand_source_get_int(
  unsigned int,
  unsigned int
);

void rand_source_clean();

#endif


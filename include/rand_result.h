#ifndef __rand_result_h
#define __rand_result_h

struct rand_result {
  unsigned char* bytes;
  unsigned long int length;
};

void rand_result_initialize(
  struct rand_result*,
  unsigned long int
);

void rand_result_clean(
  struct rand_result*
);

#endif

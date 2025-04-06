#ifndef __RAND_RESULT_H
#define __RAND_RESULT_H

struct rand_result {
  char* data;
  unsigned int length;
};

void rand_result_clean(struct rand_result*);

#endif


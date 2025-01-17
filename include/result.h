#ifndef __RESULT_H
#define __RESULT_H

struct result {
  char* data;
  unsigned int length;
};

void result_clean(struct result*);

#endif


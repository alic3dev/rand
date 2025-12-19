#ifndef __rand_source_zac_data_h
#define __rand_source_zac_data_h

struct rand_source_zac_data {
  unsigned char step;
  signed long long int value;
};

void rand_source_zac_data_initialize(
  struct rand_source_zac_data*
);

#endif

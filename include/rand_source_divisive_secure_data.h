#ifndef __rand_source_divisive_secure_data_h
#define __rand_source_divisive_secure_data_h

#include <rand_source_divisive_data.h>

#include <timingsafe.h>

struct rand_source_divisive_secure_data {
  struct rand_source_divisive_data rand_source_divisive_data;

  timingsafe_token_t timingsafe_token;
};

#endif

#ifndef __rand_source_secure_data_h
#define __rand_source_secure_data_h

struct rand_source_secure_data {
  timingsafe_token_t timingsafe_token;

  void* urandom;
};

#endif

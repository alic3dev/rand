#include "rand_source.h"

#include <stdlib.h>
#include <sys/time.h>

struct rand_source* rand_source = NULL;

void rand_source_initialize(
  struct rand_source_options* rand_source_options
) {
  rand_source = malloc(sizeof(struct rand_source));

  rand_source->time = malloc(sizeof(struct timeval));
  __rand_source_seed_by_time();

  rand_source->secure = rand_source_options->secure;


  if (rand_source->secure == 0) {
    rand_source->rand = &__rand_source_rand;
    rand_source->urandom = NULL;
  } else {
    rand_source->rand = &__rand_source_rand_secure;
    rand_source->urandom = fopen("/dev/urandom", "r");
  }
}

void __rand_source_seed_by_time() {
  gettimeofday(rand_source->time, NULL);
  
  srand(
    rand_source->time->tv_sec * 1000000 +
    rand_source->time->tv_usec
  );
}

unsigned int __rand_source_rand() {
  return rand();
}

unsigned int __rand_source_rand_secure() {
  int junk_rand_calls = rand() % 100;
  for (int i = 0; i < junk_rand_calls; ++i) {
    rand();
  }

  int random_value = rand();
  int add_rand_calls = rand() % 100;
  unsigned int rand_source_index;

  for (int i = 0; i < add_rand_calls; ++i) {
    rand_source_index = (
      rand_source_index == 0
      ? rand() % 2 
      : fgetc(rand_source->urandom)
    );
    
    if (rand_source_index == 0) {
      random_value = (
        random_value + rand()
      ) % RAND_MAX;
    } else {
      unsigned int pull = fgetc(rand_source->urandom);

      for (unsigned int c = 0; c <= pull; c++) {
        random_value += (
          fgetc(rand_source->urandom)
        ) % RAND_MAX;
      }
    }
  }

  return random_value;
}

unsigned int rand_source_get_int(
  unsigned int min,
  unsigned int max
) {
  unsigned int offset = max - min;

  unsigned int random_value = rand_source->rand();

  return (
    random_value % offset + min
  );
}

void rand_source_clean() {
  free(rand_source->time);

  if (rand_source->urandom != NULL) {
    fclose(rand_source->urandom);
  }

  free(rand_source);
}


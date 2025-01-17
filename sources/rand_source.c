#include "rand_source.h"

#include <stdlib.h>
#include <sys/time.h>

struct source* source = NULL;

void rand_source_initialize(
  struct source_options* source_options
) {
  source = malloc(sizeof(struct source));

  source->time = malloc(sizeof(struct timeval));
  __rand_source_seed_by_time();

  source->secure = source_options->secure;


  if (source->secure == 0) {
    source->rand = &__rand_source_rand;
    source->urandom = NULL;
  } else {
    source->rand = &__rand_source_rand_secure;
    source->urandom = fopen("/dev/urandom", "r");
  }
}

void __rand_source_seed_by_time() {
  gettimeofday(source->time, NULL);
  
  srand(
    source->time->tv_sec * 1000000 +
    source->time->tv_usec
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
  unsigned int source_index;

  for (int i = 0; i < add_rand_calls; ++i) {
    source_index = (
      source_index == 0
      ? rand() % 2 
      : fgetc(source->urandom)
    );
    
    if (source_index == 0) {
      random_value = (
        random_value + rand()
      ) % RAND_MAX;
    } else {
      unsigned int pull = fgetc(source->urandom);

      for (unsigned int c = 0; c <= pull; c++) {
        random_value += (
          fgetc(source->urandom)
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

  unsigned int random_value = source->rand();

  return (
    random_value % offset + min
  );
}

void rand_source_clean() {
  free(source->time);

  if (source->urandom != NULL) {
    fclose(source->urandom);
  }

  free(source);
}


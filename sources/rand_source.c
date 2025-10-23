#include <rand_source.h>

#include <rand_options.h>
#include <rand_result.h>

#include <stdlib.h>
#include <sys/time.h>

void rand_source_initialize(
  struct rand_source* rand_source,
  struct rand_source_options* rand_source_options
) {
  rand_source_seed_by_time(
    rand_source
  );

  rand_source->type_source = rand_source_options->type_source;

  switch (rand_source->type_source) {
    case rand_source_type_pseudo:
      rand_source->rand = rand_source_rand;
      rand_source->urandom = (void*)0;
      break;
    case rand_source_type_secure:
      rand_source->rand = rand_source_rand_secure;
      rand_source->urandom = fopen(
        "/dev/urandom",
        "rb"
      );
      break;
    case rand_source_type_default:
    default:
      rand_source->rand = rand_source_rand;
      rand_source->urandom = (void*)0;
      break;
  }
}

void rand_source_seed_by_time(
  struct rand_source* rand_source
) {
  gettimeofday(
    &rand_source->time,
    (void*)0
  );
  
  srand(
    rand_source->time.tv_sec * 1000000 +
    rand_source->time.tv_usec
  );
}

unsigned char rand_source_rand(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  for (
    unsigned long int index_byte = 0;
    index_byte < rand_result->length;
    ++index_byte
  ) {
    rand_result->bytes[
      index_byte
    ] = rand_source_get_bytes_transform_function(
      rand() % 256
    );
  }

  return 0;
}

unsigned char rand_source_rand_secure(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  unsigned char length_preliminary_rand_calls = (
    rand() % 256
  );

  for (
    unsigned char index_rand_calls = 0;
    index_rand_calls < length_preliminary_rand_calls;
    ++index_rand_calls
  ) {
    rand();
  }

  for (
    unsigned long int index_byte = 0;
    index_byte < rand_result->length;
    ++index_byte
  ) {
    int random_value = rand();
    int add_rand_calls = rand() % 100;

    unsigned int rand_source_index = (
      add_rand_calls % 8 == 0
      ? 1
      : 0
    );

    for (
      int index_rand_calls = 0;
      index_rand_calls < add_rand_calls;
      ++index_rand_calls
    ) {
      rand_source_index = (
        rand_source_index == 0
        ? rand() % 8
        : fgetc(rand_source->urandom) % 8
      );
      
      if (
        rand_source_index == 0
      ) {
        random_value = (
          random_value + rand()
        ) % RAND_MAX;
      } else {
        unsigned int length_characters = fgetc(
          rand_source->urandom
        );

        for (
          unsigned int index_character = 0;
          index_character <= length_characters;
          ++index_character
        ) {
          random_value = (
            random_value + (
              fgetc(
                rand_source->urandom
              )
            ) % RAND_MAX
          );
        }
      }
    }

    rand_result->bytes[
      index_byte
    ] = rand_source_get_bytes_transform_function(
      random_value % 256
    );
  }

  return 0;
}

unsigned char rand_source_get_bytes(
  struct rand_source* rand_source,
  struct rand_result* rand_result,
  rand_source_get_bytes_transform_function rand_source_get_bytes_transform_function
) {
  return rand_source->rand(
    rand_source,
    rand_result,
    rand_source_get_bytes_transform_function
  );
}

void rand_source_clean(
  struct rand_source* rand_source
) {
  if (
    rand_source->urandom != (void*)0
  ) {
    fclose(rand_source->urandom);
  }
}

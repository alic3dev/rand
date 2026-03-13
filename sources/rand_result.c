#include <rand_result.h>

#include <clic3_memory.h>

void rand_result_initialize(
  struct rand_result* rand_result,
  unsigned long int length
) {
  rand_result->length = (
    length
  );

  rand_result->bytes = (
    clic3_memory_allocate_raw(
      rand_result->length
    )
  );
}

void rand_result_clean(
  struct rand_result* rand_result
) {
  clic3_memory_free_raw(
    rand_result->bytes
  );

  rand_result->bytes = (
    0
  );
}

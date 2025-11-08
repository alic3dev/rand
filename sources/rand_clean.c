#include <rand_clean.h>

#include <rand_result.h>
#include <rand_source.h>

void rand_clean(
  struct rand_result* rand_result,
  struct rand_source* rand_source
) {
  rand_result_clean(
    rand_result
  );

  rand_source_clean(
    rand_source
  );
}

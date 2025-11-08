#include <rand_initialize.h>

#include <rand_mode.h>
#include <rand_parameters.h>
#include <rand_result.h>
#include <rand_source.h>
#include <rand_source_type.h>

void rand_initialize(
  struct rand_parameters* rand_parameters,
  struct rand_result* rand_result,
  struct rand_source* rand_source,
  unsigned long int length,
  enum rand_mode rand_mode,
  enum rand_source_type rand_source_type
) {
  rand_parameters_initialize(
    rand_parameters,
    length,
    rand_mode,
    rand_source_type
  );

  struct rand_source_parameters rand_source_parameters;
  rand_source_parameters.type_source = rand_parameters->type_source;

  rand_source_initialize(
    rand_source,
    &rand_source_parameters
  );

  rand_result_initialize(
    rand_result,
    rand_parameters->length
  );
}

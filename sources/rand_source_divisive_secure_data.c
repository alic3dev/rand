#include <rand_source_divisive_secure_data.h>

#include <rand_source_divisive_data.h>

void rand_source_divisive_secure_data_clean(
  struct rand_source_divisive_secure_data* rand_source_divisive_secure_data
) {
  timingsafe_restore_if_supported(
    rand_source_divisive_secure_data->timingsafe_token
  );

  rand_source_divisive_data_clean(
    &rand_source_divisive_secure_data->rand_source_divisive_data
  );
}

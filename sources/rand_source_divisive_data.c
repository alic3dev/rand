#include <rand_source_divisive_data.h>

#include <stdio.h>

void rand_source_divisive_data_initialize(
  struct rand_source_divisive_data* rand_source_divisive_data
) {
  void* urandom = fopen(
    "/dev/urandom",
    "rb"
  );

  unsigned char length_float = (
    sizeof(
      float
    )
  );

  unsigned char* bytes_seed = (
    (unsigned char*)
    &rand_source_divisive_data->seed
  );

  for (
    unsigned char index_seed = 0;
    index_seed < length_float;
    ++index_seed
  ) {
    bytes_seed[
      index_seed
    ] = (
      fgetc(
        urandom
      )
    );
  }

  if (
    length_float >= 4
  ) {
    rand_source_divisive_data->multiplier = (
      (float) (
        (
          bytes_seed[
            length_float -
            1
          ] +
          bytes_seed[
            length_float -
            3
          ]
        ) %
        0xfffd
      ) +
      (float) (
        bytes_seed[
          length_float -
          2
        ] +
        bytes_seed[
          length_float -
          4
        ]
      ) /
      100000.0f
    );

    rand_source_divisive_data->value = (
      (float) (
        (
          bytes_seed[
            0
          ] *
          bytes_seed[
            1
          ] +
          bytes_seed[
            2
          ] +
          bytes_seed[
            3
          ]
        ) %
        0xfffd
      ) +
      2.0f
    );
  } else {
    rand_source_divisive_data->multiplier = (
      (float) (
        (
          bytes_seed[
            1 %
            length_float
          ] +
          bytes_seed[
            3 %
            length_float
          ]
        ) %
        0xfffd
      ) +
      (float) (
        bytes_seed[
          2 %
          length_float
        ] +
        bytes_seed[
          4 %
          length_float
        ]
      ) /
      100000.0f
    );

    rand_source_divisive_data->value = (
      (float) (
        (
          bytes_seed[
            0
          ] *
          bytes_seed[
            1 %
            length_float
          ] +
          bytes_seed[
            2 %
            length_float
          ] +
          bytes_seed[
            3 %
            length_float
          ]
        ) %
        0xfffd
      ) +
      2.0f
    );
  }

  fclose(
    urandom
  );
}

#include <rand_seed.h>

#include <clic3_bytes.h>

#include <sys/sysctl.h>
#include <sys/time.h>

#include <stdio.h>

void rand_seed_generate(
  unsigned char* rand_seed_buffer,
  unsigned long long int length_rand_seed_buffer
) {
  struct timeval timeval;

  gettimeofday(
    &timeval,
    0
  );

  unsigned char bytes_time_val_sec[
    0x04
  ];

  unsigned char bytes_time_val_usec[
    0x03
  ];

  clic3_bytes_copy(
    bytes_time_val_sec,
    &timeval.tv_sec,
    0x04
  );

  clic3_bytes_copy(
    bytes_time_val_usec,
    &timeval.tv_usec,
    0x03
  );

  for (
    unsigned long long int index_rand_seed = (
      0x00
    );
    (
      index_rand_seed <
      length_rand_seed_buffer
    );
    ++index_rand_seed
  ) {
    rand_seed_buffer[
      index_rand_seed
    ] = (
      index_rand_seed *
      length_rand_seed_buffer
    );

    rand_seed_buffer[
      index_rand_seed
    ] = (
      (unsigned long long int)
      rand_seed_buffer[
        index_rand_seed
      ] +
      (
        length_rand_seed_buffer /
        index_rand_seed
      )
    );

    rand_seed_buffer[
      index_rand_seed
    ] = (
      (unsigned long long int)
      rand_seed_buffer[
        index_rand_seed
      ] +
      (
        (unsigned long long int)
        bytes_time_val_usec[
          index_rand_seed %
          0x03
        ] *
        (
          (
            index_rand_seed %
            0x03
          ) ==
          0x01
          ? 1.0f
          : (
            index_rand_seed %
            0x03
          ) ==
          0x02
          ? index_rand_seed
          : (
            length_rand_seed_buffer -
            index_rand_seed
          )
        )
      )
    );

    rand_seed_buffer[
      index_rand_seed
    ] = (
      (unsigned long long int)
      rand_seed_buffer[
        index_rand_seed
      ] +
      (
        (unsigned long long int)
        bytes_time_val_sec[
          0x00
        ] *
        (
          index_rand_seed %
          (
            bytes_time_val_usec[
              0x00
            ] *
            13
          )
        )
      )
    );
    
    rand_seed_buffer[
      index_rand_seed
    ] = (
      (unsigned long long int)
      rand_seed_buffer[
        index_rand_seed
      ] +
      (
        (unsigned long long int)
        bytes_time_val_sec[
          0x01
        ] *
        length_rand_seed_buffer
      )
    );

    rand_seed_buffer[
      index_rand_seed
    ] = (
      (unsigned long long int)
      rand_seed_buffer[
        index_rand_seed
      ] +
      (unsigned long long int)
      bytes_time_val_sec[
        0x02
      ]
    );

    rand_seed_buffer[
      index_rand_seed
    ] = (
      (unsigned long long int)
      rand_seed_buffer[
        index_rand_seed
      ] +
      (unsigned long long int)
      bytes_time_val_sec[
        0x03
      ]
    );

    if (
      (
        index_rand_seed <
        (
          length_rand_seed_buffer -
          0x01
        )
      ) &&
      (
        index_rand_seed %
        0x03 ==
        0x02
      )
    ) {
      gettimeofday(
        &timeval,
        0
      );

      clic3_bytes_copy(
        bytes_time_val_usec,
        &timeval.tv_usec,
        0x03
      );
    }
  }
}

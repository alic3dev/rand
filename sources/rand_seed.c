#include <rand_seed.h>

#include <clic3_bytes.h>

#include <sys/sysctl.h>
#include <sys/time.h>
#include <unistd.h>

void rand_seed_generate(
  unsigned char* rand_seed_buffer,
  unsigned long long int length_rand_seed_buffer
) {
  int identifier_process = (
    getpid()
  );
  struct timeval timeval;

  gettimeofday(
    &timeval,
    0x00
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
  
  unsigned char byte = (
    0x00
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
    byte = (
      byte +
      identifier_process +
      identifier_process *
      (
        identifier_process +
        index_rand_seed
      )
    );  
    rand_seed_buffer[
      index_rand_seed
    ] = (
      index_rand_seed *
      length_rand_seed_buffer +
      byte
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
    
    byte = (
      byte +
      rand_seed_buffer[
        byte %
        length_rand_seed_buffer
      ] +
      bytes_time_val_usec[
        byte %
        0x03
      ] *
      byte
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
          (
            byte +
            index_rand_seed
          ) %
          0x03
        ] *
        (
          (
            (
              index_rand_seed %
              0x03
            ) ==
            0x01
          )
          ? 0x01
          : (
            (
              (
                index_rand_seed %
                0x03
              ) ==
              0x02
            )
            ? index_rand_seed
            : (
              length_rand_seed_buffer -
              index_rand_seed
            )
          )
        )
      )
    );
    
    byte = (
      byte +
      byte *
      0x03 +
      index_rand_seed
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
          byte %
          0x04
        ] *
        (
          (
            index_rand_seed %
            (
              bytes_time_val_usec[
                0x00
              ] *
              0x0d
            )
          ) +
          0x01
        )
      )
    );
    
    byte = (
      byte +
      rand_seed_buffer[
        byte %
        length_rand_seed_buffer
      ] +
      byte /
      0x02 +
      byte *
      index_rand_seed
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
      ) +
      byte
    );
    
    byte = (
      byte *
      byte +
      bytes_time_val_usec[
        (
          index_rand_seed +
          byte
        ) %
        0x03
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
        0x02
      ] -
      byte
    );
    
    byte = (
      byte +
      byte *
      bytes_time_val_sec[
        byte %
        0x04
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
      ] +
      byte
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

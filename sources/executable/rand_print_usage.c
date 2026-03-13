#include <rand_print_usage.h>

#include <stdio.h>

void rand_print_usage(unsigned char to_std_err) {
  FILE* stream = (
    to_std_err == 0
    ? stdout
    : stderr
  );

  fprintf(
    stream,
    "usage: rand [?parameters] [?mode] [?#length]\n"
    "  modes:\n"
    "    -b, --bytes, bytes                                | bytes\n"
    "    -x, --hexadecimal, hexadecimal                    | hexadecimal\n"
    "    -d --decimal, decimal                             | decimal\n"
    "    -n, --numeric_alphabetical, numeric_alphabetical  | numeric & alphabetical\n"
    "    -a, --alphabetical, alphabetical                  | alphabetical\n"
    "  parameters:\n"
    "    -h, --help, help                                  | print help information\n"
    "    -v, --divisive, divisive                          | divisive random generation\n"
    "    -z, --zac                                         | zac random generation\n"
  );
}

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
    "usage: rand [?options] [?mode] [?#length]\n"
    "  modes:\n"
    "    -x, --hexadecimal, hexadecimal                    | hexadecimal\n"
    "    -d --decimal, decimal                             | decimal\n"
    "    -n, --numeric_alphabetical, numeric_alphabetical  | numeric & alphabetical\n"
    "    -a, --alphabetical, alphabetical                  | alphabetical\n"
    "  options:\n"
    "    -h, --help, help                                  | print help information\n"
    "    -s, --secure, secure                              | secure random generation\n"
  );
}

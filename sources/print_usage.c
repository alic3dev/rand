#include "print_usage.h"

#include <stdio.h>

void print_usage(unsigned char to_std_err) {
  FILE* stream = (
    to_std_err == 0 ? stdout : stderr
  );

  fprintf(
    stream,
    "USAGE: rand [options] [mode] [#length]\n\tModes:\n\t\thex\tHexadecimal\n\t\tdec\tDecimal\n\t\tnumalph\tNumeric + Alphabetical\n\t\talph\tAlphabetical\n\tOptions:\n\t\tsec, --secure\tSecure random generation\n"
  );
}


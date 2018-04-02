#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

void mv0(const char* original, const char* new) {
  rename(original, new);
}

int main(int argc, char const *argv[]) {
  if (argc != 3)
    return 1;
  mv0(argv[1], argv[2]);
  return 0;
}

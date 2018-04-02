#define _POSIX_C_SOURCE 200809L
#include <unistd.h>

void ln1(const char* original, const char* new) {
  link(original, new);
}

int main(int argc, char const *argv[]) {
  if (argc != 3)
    return 1;
  ln1(argv[1], argv[2]);
  return 0;
}

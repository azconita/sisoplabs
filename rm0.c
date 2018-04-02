#define _POSIX_C_SOURCE 200809L
#include <unistd.h>

void rm0(const char* filename) {
  unlink(filename);
}

int main(int argc, char const *argv[]) {
  rm0(argv[1]);
  return 0;
}

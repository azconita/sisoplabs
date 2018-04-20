#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

void rm1(const char* filename) {
  char buf[256];
  int r = unlink(filename);
  if (r == -1 && errno == EISDIR) {
    sprintf(buf, "rm: cannot remove '%s'", filename);
    perror(buf);
  }
}

int main(int argc, char const *argv[]) {
  rm1(argv[1]);
  return 0;
}

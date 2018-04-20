#define _POSIX_C_SOURCE 200809L
#include <unistd.h>

void ln0(const char* original, const char* new) {
  symlink(original, new);
}

int main(int argc, char const *argv[]) {
  if (argc != 3)
    return 1;
  ln0(argv[1], argv[2]);
  return 0;
}

//EEXIST: error si el archivo new ya existe

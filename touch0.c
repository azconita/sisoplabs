#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void touch0(const char* filename) {
  //open filename
  int fd = open(filename, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  //close filename
  close(fd);
}

int main(int argc, char const *argv[]) {
  if (argc == 2) {
    touch0(argv[1]);
    return 0;
  } else {
    return 1;
  }
}

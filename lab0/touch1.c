#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>

void touch1(const char* filename) {
  //open filename
  int fd = open(filename, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  //update times
  futimes(fd, NULL);
  //close filename
  close(fd);
}

int main(int argc, char const *argv[]) {
  if (argc == 2) {
    touch1(argv[1]);
    return 0;
  } else {
    return 1;
  }
}

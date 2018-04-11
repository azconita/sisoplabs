#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

void tee0(const char* filename) {
  char buf;
  int fd;
  //open filename
  if (access(filename, W_OK) == 0) {
    fd = open(filename, O_WRONLY);
  } else if (errno == ENOENT) {
    fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  } else {
    exit(1);
  }
  //read filename
  while (read(0, &buf, 1) > 0) {
    //write filename a stdout
    write(fd, &buf, 1);
    write(1, &buf, 1);
  }
  //close filename
  close(fd);
}

int main(int argc, char const *argv[]) {
  if (argc == 2) {
    tee0(argv[1]);
    return 0;
  } else {
    return 1;
  }
}

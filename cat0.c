#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void cat0(const char* filename) {
  char buf;
  //open filename
  int fd = open(filename, O_RDONLY);
  //read filename
  while (read(fd, &buf, 1) > 0) {
    //write filename a stdout
    write(1, &buf, 1);
  }
  //close filename
  close(fd);
}

int main(int argc, char const *argv[]) {
  if (argc == 2) {
    cat0(argv[1]);
    return 0;
  } else {
    return 1;
  }
}

#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void cp0(const char* original, const char* copy) {
  char buf;
  int fdcopy, fdorig;
  //open original
  fdorig = open(original, O_RDONLY);
  //create copy file
  fdcopy = open(copy, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  //read original
  while (read(fdorig, &buf, 1) > 0) {
    //write copy
    write(fdcopy, &buf, 1);
  }
  //close files
  close(fdorig);
  close(fdcopy);
}

int main(int argc, char const *argv[]) {
  if (argc == 3) {
    cp0(argv[1], argv[2]);
    return 0;
  } else {
    return 1;
  }
}

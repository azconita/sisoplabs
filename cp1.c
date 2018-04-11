#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void cp1(const char* original, const char* copy) {
  char *addr_orig, *addr_copy;
  int fdcopy, fdorig, length;
  struct stat statbuf;
  stat(original, &statbuf);
  length = statbuf.st_size;
  //open original
  fdorig = open(original, O_RDONLY);
  if (fdorig == -1) {
    printf("error opening file %s\n", original);
    exit(1);
  }
  //create copy file
  fdcopy = open(copy, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fdcopy == -1) {
    printf("error opening file %s\n", copy);
    close(fdorig);
    exit(1);
  }
  //set memory mapping spaces
  addr_orig = mmap(NULL, length, PROT_READ, MAP_SHARED, fdorig, 0);
  if (addr_orig == MAP_FAILED) {
    printf("error starting memory for file %s\n", original);
    close(fdorig);
    close(fdcopy);
    exit(1);
  }
  addr_copy = mmap(NULL, length, PROT_WRITE, MAP_SHARED, fdcopy, 0);
  if (addr_copy == MAP_FAILED) {
    printf("error starting memory for file %s\n", copy);
    close(fdorig);
    close(fdcopy);
    exit(1);
  }
  //memcpy(addr_copy, addr_orig, length);
  write(fdcopy, addr_orig, length);
  printf("done!\n");
  //free memory mapping spaces
  munmap(addr_orig, length);
  munmap(addr_copy, length);
  //close files
  close(fdorig);
  close(fdcopy);
}

int main(int argc, char const *argv[]) {
  if (argc == 3) {
    cp1(argv[1], argv[2]);
    return 0;
  } else {
    return 1;
  }
}

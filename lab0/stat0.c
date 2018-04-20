#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

char *typefile(mode_t m) {
  if (S_ISREG(m))
    return "regular file";
  if (S_ISDIR(m))
    return "directory";
  if (S_ISCHR(m))
    return "character device";
  if (S_ISBLK(m))
    return "block device";
  if (S_ISFIFO(m))
    return "FIFO (named pipe)";
  if (S_ISLNK(m))
    return "symbolic link";//  (Not in POSIX.1-1996.)
  if (S_ISSOCK(m))
    return "socket";//  (Not in POSIX.1-1996.)
  return "unknown";
}

void stat0(const char* filename) {
  struct stat statbuf;
  stat(filename, &statbuf);
  fprintf(stdout, "Size: %li\n", statbuf.st_size);
  fprintf(stdout, "File: %s\n", filename);
  fprintf(stdout, "Type: %s\n", typefile(statbuf.st_mode));
}

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    return 1;
  }
  stat0(argv[1]);
  return 0;
}

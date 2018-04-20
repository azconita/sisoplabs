#define _POSIX_C_SOURCE 200809L
#include <dirent.h>
#include <stdio.h>

void ls0() {
  struct dirent *d;
  DIR *p_dir = opendir(".");
  while ((d = readdir(p_dir)) != NULL)
    printf("%s\n", d->d_name);
  closedir(p_dir);
}

int main(int argc, char const *argv[]) {
  ls0();
  return 0;
}

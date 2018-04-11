#include <dirent.h>
#include <stdio.h>

void ls0(/* arguments */) {
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

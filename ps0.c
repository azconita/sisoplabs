#define _POSIX_C_SOURCE 200809L
#include <dirent.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void ps0() {
  char name[267], buf[1];
  struct dirent *d;
  DIR *p_dir = opendir("/proc");
  while ((d = readdir(p_dir)) != NULL) {
    if (isdigit((unsigned char) d->d_name[0])) {
      sprintf(name, "/proc/%s/comm", d->d_name);

      //open filename
      int fd = open(name, O_RDONLY);
      //read filename
      //printf("%s,", d->d_name);
      write(1,d->d_name, strlen(d->d_name));
      write(1,",",1);
      while (read(fd, &buf, 1) > 0) {
        //write filename a stdout
        write(1, &buf, 1);
      }
      //close filename
      close(fd);
    }
  }
  closedir(p_dir);
}

int main(int argc, char const *argv[]) {
  ps0();
  return 0;
}

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *buffer = NULL;
  size_t size = 0;

  if ((buffer = getcwd(buffer, size)) != NULL) {
    write(STDOUT_FILENO, buffer, strlen(buffer));
  } else {
    write(STDERR_FILENO, buffer, strlen(buffer));
  }

  free(buffer);
}

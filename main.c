#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  char array[256];

  ssize_t read_num = read(0, array, strlen(array) - 1);
  //  array[read_num] = '\0';

  if (read_num > 0) {
    printf("%s\n", array);
  }
}

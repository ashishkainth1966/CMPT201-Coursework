#include <stdio.h>
#include <unistd.h>

int main() {
  fork();

  for (int j = 0; j < 10; j++) {
    printf("Hello World!\n");
    sleep(1);
  }
  return 0;
}

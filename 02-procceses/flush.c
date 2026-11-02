#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *string = "Hello World!\n";
  for (int i = 0; i < strlen(string); i++) {
    printf("%c", string[i]);
    fflush(stdout);
    sleep(2);
  }
  printf("Done!\n");
}

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {

  while (1) {
    char input[256];
    char digits_input[5];
    int count = 0;

    printf("Enter command: ");

    fflush(stdout);

    ssize_t number = read(0, input, sizeof(input) - 1);

    if (number > 0) {
      input[number - 1] = '\0';
      printf("Input: %s\n", input);
    } else {
      printf("Read failed!");
    }

    for (int i = 0; i < strlen(input); i++) {
      if (isdigit(input[i])) {
        printf("%d %c\n", i, input[i]);
        digits_input[count] = input[i];
        count++;
      }
    }
    digits_input[count] = '\0';

    if (count != 0) {
      long num = atoi(digits_input);
      printf("Number: %i\n", (int)num);
    } else {
      printf("The string does not contain any numbers.\n");
    }
  }
  return 0;
}

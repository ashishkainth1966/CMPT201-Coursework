#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *line = NULL;
  size_t length = 0;

  printf("Please enter some text: ");

  if (getline(&line, &length, stdin) != -1) {
    printf("Tokens:\n");

    char *str = line;
    const char *delim = " ";
    char *saveptr = NULL;

    char *token = strtok_r(str, delim, &saveptr);

    while (token != NULL) {
      printf("%s\n", token);
      token = strtok_r(NULL, delim, &saveptr);
    }

  } else {
    perror("Getline failed!");
    exit(EXIT_FAILURE);
  }

  free(line);
}

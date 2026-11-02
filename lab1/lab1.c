// CMPT 201 - Lab 1
// Ashish Kumar - 301663404
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  // Initializing the getline input
  char *line = NULL;
  ssize_t length = 0;

  char *array[20];
  int count = 0;

  printf("Please enter some text: ");

  // Intializing a while loop to continue accepting user inputs
  while ((length = read(0, &length, stdin)) != -1) {
    if (strchr(line, '&') != NULL) {
      line[length - 1] = '\0';
    }

    printf("Tokens:\n");

    // Tokening the user entered string
    char *str = line;
    const char *delim = " ";
    char *saveptr = NULL;

    char *token = strtok_r(str, delim, &saveptr);

    while (token != NULL) {
      array[count] = token;
      count++;
      token = strtok_r(NULL, delim, &saveptr);
    }

    for (int i = 0; i < count; i++) {
      printf("%s\n", array[i]);
    }

    printf("Please enter some text: ");
  }

  // Printing error message to the terminal if getline failed or end of file is reached
  perror("Getline failed or end of file reached! \n");
  exit(EXIT_FAILURE);

  free(line);
}

// CMPT 201 - Lab 1
// Ashish Kumar - 301663404
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  // Initializing the getline input
  char *line = NULL;
  size_t length = 0;

  printf("Please enter some text: ");

  // Intializing a while loop to continue accepting user inputs
  while (getline(&line, &length, stdin) != -1) {
    printf("Tokens:\n");

    // Tokening the user entered string
    char *str = line;
    const char *delim = " ";
    char *saveptr = NULL;

    char *token = strtok_r(str, delim, &saveptr);

    while (token != NULL) {
      printf("%s\n", token);
      token = strtok_r(NULL, delim, &saveptr);
    }
    printf("Please enter some text:");
  }

  // Printing message to the terminal if getline failed or end of file is reached
  printf("Getline failed or end of file reached! \n");

  free(line);
}

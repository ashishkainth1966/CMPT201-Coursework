#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_LENGTH 5

char *input_array[ARRAY_LENGTH];
int array_element_number = 0;

void add_input(char **array, char *str);

int main() {
  char *input = NULL;
  char *newstr = NULL;
  size_t length = 0;
  int size = 0;

  while (1) {
    printf("Enter input: ");

    if ((length = getline(&input, &length, stdin)) != -1) {
      input[length - 1] = '\0';

      size = strlen(input);
      newstr = malloc(sizeof(char) * (size + 1));
      strcpy(newstr, input);
    } else {
      printf("Getline failed. Error occured while reading input.\n");
      exit(EXIT_FAILURE);
    }

    add_input(input_array, newstr);

    if ((strcmp(input, "print")) == 0) {
      for (int i = 0; i < ARRAY_LENGTH; i++) {
        if (input_array[i] != NULL) {
          printf("%s\n", input_array[i]);
        }
      }
    }
  }
  free(input);
  free(newstr);
  return 0;
}

void add_input(char **array, char *str) {
  if (array_element_number < ARRAY_LENGTH) {
    array[array_element_number] = str;
    array_element_number++;
  } else {
    for (int j = 1; j < array_element_number; j++) {
      array[j - 1] = array[j];
    }
    array_element_number--;
    array[array_element_number] = str;
    array_element_number++;
  }
}

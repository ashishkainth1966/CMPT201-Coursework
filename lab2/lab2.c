#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int flag = 1;

  while (flag) {
    char *input = NULL;
    size_t length = 0;

    printf("Enter programs to run.\n");
    printf("> ");

    if (getline(&input, &length, stdin) != -1) {
      length = strlen(input);
      input[length - 1] = '\0';

      pid_t pid = fork();

      if (pid != 0) {
        int wstatus = 0;
        if (waitpid(pid, &wstatus, 0) == -1) {
          printf("Waitpid failed!\n");
          exit(EXIT_FAILURE);
        }

        if (WIFEXITED(wstatus)) {
          printf("The child process exited with status: %d\n", WEXITSTATUS(wstatus));
        } else {
          printf("The child proces failed to exit normally.\n");
        }
      } else {
        if ((execlp(input, input, NULL)) == -1) {
          printf("Exec failure!\n");
          exit(EXIT_FAILURE);
        }
      }
    } else {
      printf("Getline failed. Error occured while reading input\n");
      exit(EXIT_FAILURE);
    }

    free(input);
  }
}

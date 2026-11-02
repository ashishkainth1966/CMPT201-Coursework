#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

int main() {
  int wstatus = 0;

  pid_t pid = fork();
  if (pid == 0) {
    printf("%d\n", getpid());

    if (execlp("sleep", "sleep", "20", NULL) == -1) {
      printf("excel");
      exit(EXIT_FAILURE);
    }
  } else {
    /*  if (waitpid(pid, &wstatus, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(wstatus)) {
        printf("Child exited: %d\n", WEXITSTATUS(wstatus));
      } else {
        printf("Childe did not exit normally.\n");
      }*/
  }
}

#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cnt = 0;

void *my_thread(void *args) {
  // printf("In thread %d: %i\n", gettid(), (int)args);
  int i = 0;
  while (i < 1000000) {
    cnt++;
    i++;
  }
  printf("Thread done!\n");
  return NULL;
}

int main() {
  pthread_t id1;
  if (pthread_create(&id1, NULL, my_thread, NULL) != 0) {
    perror("Unable to create a thread.\n");
    exit(EXIT_FAILURE);
  }

  pthread_t id2;
  if (pthread_create(&id2, NULL, my_thread, NULL) != 0) {
    perror("Unable to create a thread.\n");
    exit(EXIT_FAILURE);
  }

  if (pthread_join(id1, NULL) != 0) {
    perror("Unable to join.\n");
    exit(EXIT_FAILURE);
  }

  if (pthread_join(id2, NULL) != 0) {
    perror("Unable to join.\n");
    exit(EXIT_FAILURE);
  }

  printf("Threads returned: %d\n", cnt);

  printf("Done!\n");
}

#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

static void *func1(void *arg) {
  sleep(5);
  pthread_mutex_lock(&mutex1);
  printf("1 locked\n");
  pthread_mutex_lock(&mutex2);
  printf("2 locked\n");
  pthread_mutex_unlock(&mutex2);
  pthread_mutex_unlock(&mutex1);
  printf("2 and 1 unlocked\n");
  pthread_exit(0);
}
static void *func2(void *arg) {
  pthread_mutex_lock(&mutex2);
  printf("2 locked\n");
  pthread_mutex_lock(&mutex1);
  printf("1 locked\n");
  pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);
  printf("1 and 2 unlocked\n");
  pthread_exit(0);
}

int main() {
  pthread_t id1;
  if (pthread_create(&id1, NULL, func1, NULL) != 0) {
    perror("Unable to create a thread.\n");
    exit(EXIT_FAILURE);
  }

  pthread_t id2;
  if (pthread_create(&id2, NULL, func2, NULL) != 0) {
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

  printf("Done!\n");
}

#define _DEFAULT_SOURCE
#define _ISOC99_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 64

struct header {
  uint64_t size;
  struct header *next;
};

void increase_heap_size(void **ptr, int size) {
  if ((*ptr = sbrk(size)) == (void *)-1) {
    perror("sbrk failed!\n");
    exit(EXIT_FAILURE);
  }
}

void initialize_block(struct header *block, struct header *nextblock, uint64_t block_size) {
  block->size = block_size;
  block->next = nextblock;
}

void initialize_block_data(struct header *block, int data) {
  struct header *next_block = block;
  uint64_t memory_size = next_block->size - sizeof(struct header);
  memset(next_block + 1, data, memory_size);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUFF_SIZE];
  ssize_t len = snprintf(buf, BUFF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    perror("snprintf failed!\n");
    exit(EXIT_FAILURE);
  }
  write(STDOUT_FILENO, buf, len);
}

void print_block_data(struct header *block) {
  struct header *next_block = block;

  char *array = (char *)(next_block + 1);

  uint64_t memory_size = next_block->size - sizeof(struct header);

  for (int i = 0; i < memory_size; i++) {
    uint64_t data = (uint64_t)array[i];
    print_out("%lu\n", &data, sizeof(data));
  }
}

int main() {
  int size = 256;

  void *start_address = NULL;

  increase_heap_size(&start_address, size);

  struct header *first_memory_block = (struct header *)start_address;
  struct header *second_memory_block = (struct header *)(start_address + 128);

  initialize_block(first_memory_block, NULL, 128);
  initialize_block(second_memory_block, first_memory_block, 128);

  initialize_block_data(first_memory_block, 0);
  initialize_block_data(second_memory_block, 1);

  print_out("first block:       %p\n", &first_memory_block, sizeof(first_memory_block));
  print_out("second block:      %p\n", &second_memory_block, sizeof(second_memory_block));
  print_out("first block size:  %lu\n", &first_memory_block->size,
            sizeof(first_memory_block->size));
  print_out("first block next:  %p\n", &first_memory_block->next, sizeof(first_memory_block->next));
  print_out("second block size: %lu\n", &second_memory_block->size,
            sizeof(second_memory_block->size));
  print_out("second block next: %p\n", &second_memory_block->next,
            sizeof(second_memory_block->next));

  print_block_data(first_memory_block);
  print_block_data(second_memory_block);

  return 0;
}

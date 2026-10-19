#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit
  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size) {
      return current->id;
    }
    current = current->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t size_cmp = 0;
  // TODO: Implement best fit
  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size) {
      if (size_cmp == 0) {
        best_fit_id = current->id;
        size_cmp = current->size;
      } else {
        if (size_cmp > current->size) {
          best_fit_id = current->id;
          size_cmp = current->size;
        }
      }
    }
    current = current->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  uint64_t size_cmp = 0;
  // TODO: Implement worst fit
  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size) {
      if (size_cmp == 0) {
        worst_fit_id = current->id;
        size_cmp = current->size;
      } else {
        if (size_cmp < current->size) {
          worst_fit_id = current->id;
          size_cmp = current->size;
        }
      }
    }
    current = current->next;
  }
  return worst_fit_id;
}

void free_list(struct header **free_list_ptr) {
  struct header *block = *free_list_ptr;
  while (block != NULL) {
    struct header *block_next = block->next;
    free(block);
    block = block_next;
  }
  *free_list_ptr = NULL;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  free_list(&free_list_ptr);

  return 0;
}

/* Part 2: Coalescing Contiguous Free Blocks
 * Create a struct named header with two fields.
 * First field in the struct is uint64_t size and second field is a struct header *next
 * Create free blocks linked list's head using struct header and set it to null
 * If the linked list is empty, append the first free block to the head of the linked list
 * Point the head of the linked list to this block, set the head's next to NULL and exit
 * the alogrithm
 * Else
 * For the newly freed block, get it's starting address and ending address
 * Get starting address of the newly freed block by type casting struct header* to char*
 * Get ending address of the newly freed block by adding block total's size to it's starting address
 *
 * Set two bool variables. Adjacent_right_block_free and Adjacent_left_block_free
 * Set both bool variables to False
 *
 * Loop through the free blocks linked list
 * Check if starting address of the newly freed block matches the ending address of any linked list
 * blocks
 * If yes, store a pointer to this adjacent left free block
 * Set Adjacent_left_block free to true
 * Check if ending address of the newly freed block matches the starting address of any linked list
 * blocks
 * If yes, store a pointer to this adjacent right free block
 * Set Adjacent_right_block_free to true
 * Loop ends
 *
 * Case I: only adjacent left block in memory is free
 * Set adjacent left free block's size to sum of it's own size and the newly free block's size
 *
 * Case II: only adjacent right block in memory is free
 * Update the newly freed block's struct header pointer size with it's size equal to the sum of
 * size of newly freed block and the adjacent right free block's size
 * Point next of this coalesced free block to the head of the free blocks linked list
 * Update the head of the linked list to this new coalasced freed block
 * Loop through the linked list and stop at the block whose's next matches the adjacent right
 * block pointer stored
 * Set the next for this block to the next that the adjacent right free block currently points to
 *
 * CASE III: Both adjacent right and left block are free
 * Update the adjacent left free block's size equal to the sum of it's own size, newly freed
 * block's size and the adjacent right free block's size
 * If the adjacent right free block is not the head of the linked list
 * Loop through the linked list and stop at the block whose's next matches the adjacent
 * right block pointer stored
 * Set the next for this block to the next that the adjacent right free block currently points to
 * Else update the head of the linked list to the point to the next of the adjacent right free
 * block
 *
 * CASE IV: Both adjacent right and left block are not free
 * Point next of the newly freed block to the head of the free blocks linked list
 * Update the head of the linked list to this newly freed block
 *
 *
 *
 */

// How to remember the correct way to write
// a function pointer:
//
// 1. Write a normal function declaration
//    => int hello(int word)
//
// 2. Wrap the function name with pointer syntax
//    => int (*hello)(int word)
//
// 3. Change the name to the pointer name
//    => int (*my_callback)(int word)

// Same goes for functions that return pointers:
// char *coolness(char * word)
// char *(*coolness)(char * word)
// char *(*my_callback)(char *word)

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char * message)
{
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

// a typedef creates a fake type, in this case
// a function pointer
typedef int (*callback)(int a, int b);

int *bubble_sort(int *numbers, int count, callback cmp)
{
  int temp = 0;
  int *target = malloc(count * sizeof(int));

  if (!target) die("Memory error.");

  memcpy(target, numbers, count * sizeof(int));

  for (size_t i = 0; i < count; i++) {
    for (size_t j = 0; j < count - 1; j++) {
      if (cmp(target[j], target[j + 1]) > 0) {
        temp = target[j+1];
        target[j+1] = target[j];
        target[j] = temp;
      }
    }
  }

  // `target` will need to be freed by the caller
  // since this memory comes from the heap with
  // malloc.
  return target;
}

int sorted_order(int a, int b)
{
  return a - b;
}

int reverse_order(int a, int b)
{
  return b - a;
}

int strange_order(int a, int b)
{
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

void test_sorting(int *numbers, int count, callback cmp)
{
  int *sorted = bubble_sort(numbers, count, cmp);

  if (!sorted) die("Failed to sort!");

  for (size_t i = 0; i < count; i++) {
    printf("%d\n", sorted[i]);
  }
  printf("\n");

  free(sorted);

  // Show the raw assembler byte code for the
  // comparison function.
  unsigned char *data = (unsigned char *)cmp;

  for (size_t i = 0; i < 25; i++) {
    printf("%02x: ", data[i]);
  }
  
  printf("\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) die("USAGE: ex18 4 7 1 5 6");

  int count = argc - 1;
  char **inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));
  if (!numbers) die("Memory error.");

  for (size_t i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }

  test_sorting(numbers, count, sorted_order);
  test_sorting(numbers, count, reverse_order);
  test_sorting(numbers, count, strange_order);

  free(numbers);

  return 0;
}

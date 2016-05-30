#include <stdio.h>

int main(int argc, char *argv[])
{

  /*
    for(INITIALIZER; TEST; INCREMENTER) {
        CODE;
    }
  */

  for (size_t i = 0; i < argc; i++) {
    // NOTE
    // The format specifier for an unsigned long
    // integer, like that of type size_t, is `zu`.
    printf("Arg %zu: %s\n", i, argv[i]);
  }

  // Let's make an array of strings!
  char *states[] = {
    "State1", "State2", "State3",
    "State4", "State5",
  };

  printf("Size of states[CHAR]: %lu\n", sizeof(states));
  printf("Size of CHAR: %lu\n", sizeof(char));
  size_t num_states = 5;

  for (size_t i = 0; i < num_states; i++) {
    printf("state %zu: %s\n", i, states[i]);
  }

  return 0;
}

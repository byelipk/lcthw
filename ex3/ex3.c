#include <stdio.h>

int main(int argc, char const *argv[]) {
  int age = 12;
  int height = 70;

  printf("You are %d years old.\n", age);
  printf("She is %d inches tall.\n", height);

  /*
    For more information about escape sequences
    for the printf() function see:

      https://en.wikipedia.org/wiki/Escape_sequences_in_C

  */

  // Newline character numerical value (ASCII)
  printf("Newline character%cnumerical value.%c", 0x0a, 0x0a);

  // Newline character inside string literal
  printf("Newline character\nstring literal.\n");

  return 0;
}


// man 3 printf

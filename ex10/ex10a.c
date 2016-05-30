#include <stdio.h>

int main(int argc, char *argv[])
{
  // Two ways to make a string...
  char *str1  = "blah";
  char str2[] = { 'b', 'l', 'a', 'h', '\0' };

  // This is a combination of the two ways to make
  // a string shown above. Here each string is one
  // element and each character in the string is
  // another. So an array of strings is a
  // multi-dimensional array.
  char *array[] = {
    "Hello", "World", "How", "Are", "You"
  };

  printf("%s\n", str1);
  printf("%s\n", str2);

  for (size_t i = 0; i < 5; i++) {
    printf("%s\n", array[i]);
  }

  return 0;
}

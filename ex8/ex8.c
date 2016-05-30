#include <stdio.h>

int main(int argc, char *argv[])
{
  /*
    What happens when C sees an array
    declared in the following way:

    1. It first looks at the type.
    2. It seems square brakets ([]) without a specified length.
    3. It looks at the initializer to determine the length.
    4. It creates a block of memory that is large enough to hold all the elements of the array.
    5. It takes the name of the array and assigns it to the location in memory.
  */
  int areas[] = { 10, 12, 14, 19 };
  char name[] = "Zed";
  char full_name[] = {
    'Z','e','d',' ','S','h','a','w','\0'
  };


  // Integers and arrays
  printf("The size of an int: %lu\n",
    sizeof(int));

  printf("The size of areas (int[]): %lu\n",
    sizeof(areas));

  printf("The number of ints in areas (int[]): %lu\n",
    (sizeof(areas) / sizeof(int)));

  printf("The first area is %d and the second area is %d\n",
    areas[0], areas[1]);

  // Chars and arrays
  printf("The size of a char: %lu\n",
    sizeof(char));

  printf("The size of name (char[]): %lu\n",
    sizeof(name));

  printf("The number of chars in name: %lu\n",
    (sizeof(name) / sizeof(char)));

  printf("The size of full_name (char[]): %lu\n",
    sizeof(full_name));

  printf("The number of chars in full_name: %lu\n",
    (sizeof(full_name) / sizeof(char)));

  printf("name = \"%s\"; full_name = \"%s\"\n",
    name, full_name);

  return 0;
}

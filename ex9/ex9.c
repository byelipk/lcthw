#include <stdio.h>

int main(int argc, char *argv[])
{
  int  numbers[4] = { 1 };
  char name[4]    = { 'p' };

  printf("Numbers: %d %d %d %d\n",
    numbers[0],
    numbers[1],
    numbers[2],
    numbers[3]

    // NOTE
    // This will throw a compiler warning because
    // we're trying to access an index past the
    // end of the array.
    // , numbers[4]
  );

  // Printing the char array
  printf("Name: %c %c %c %c\n",
     name[0]
    ,name[1]
    ,name[2]
    ,name[3]
  );

  // Printing the base-10 representation of the char
  printf("Name: %d %d %d %d\n",
     name[0]
    ,name[1]
    ,name[2]
    ,name[3]
  );

  // Printing `name` as a string
  printf("%s\n", name);


  // Setup the numbers
  numbers[0] = 1;
  numbers[1] = 2;
  numbers[2] = 3;
  numbers[3] = 4;

  // Setup the name
  name[0] = 'P';
  name[1] = 'a';
  name[2] = 't';
  name[3] = '\0'; // Null terminator byte


  // Printing `numbers` again
  printf("Numbers: %d %d %d %d\n",
    numbers[0],
    numbers[1],
    numbers[2],
    numbers[3]
  );

  // Printing `name` again
  printf("[CHAR] Name: %c %c %c %c\n",
     name[0]
    ,name[1]
    ,name[2]
    ,name[3]
  );

  printf("[INT]  Name: %d %d %d %d\n",
     name[0]
    ,name[1]
    ,name[2]
    ,name[3]
  );

  printf("[STRING] Name: %s\n", name);


  // Anothr name
  char *another = "Zed";

  printf("[STRING] Another: %s\n", another);
  printf("[CHAR]   Another: %c %c %c %c\n",
     another[0]
    ,another[1]
    ,another[2]
    ,another[3]
  );

  return 0;
}

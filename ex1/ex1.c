#include <stdio.h>

int main(int argc, char *argv[]) {
  // The function puts() takes a pointer
  // to a char array saved in memory reserved
  // for constants.
  puts("Hello world.");

  char str1[13] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '.'};
  char str2[]  = "Hello world again.";
  const char str3[] = "Hello world again.";


  puts(str1);
  puts(str2);
  puts(str3);

  return 0;
}


// man 3 puts

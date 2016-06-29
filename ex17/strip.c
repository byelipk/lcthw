#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char const *argv[]) {
  printf("\n");

  char *string = "  Hello world  ";

  printf("BEFORE l-strip:\n");
  printf("%p | %lu bytes long\n",
    string, strlen(string));
  printf("-----\n");
  printf("%s\n", string);
  printf("-----\n");
  printf("\n");

  // Advance the pointer 2 bytes
  while (isspace(*string)) { string++; };

  printf("AFTER l-strip:\n");
  printf("%p | %lu bytes long\n",
    string, strlen(string));
  printf("-----\n");
  printf("%s\n", string);
  printf("-----\n");
  printf("\n");

  // How do we trim the right side?
  char *end;

  end = string + strlen(string) - 1;

  while (end > string && isspace(*end)) {
    end--;
  }

  // Increment the pointer. Now all the chars we care
  // about are to our left.
  end++;

  printf("%p\n", end);
  printf("%c\n", *end);
  printf("%c\n", end[0]);
  printf("%lu\n", strlen(end));
}

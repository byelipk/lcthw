#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);

void print_letters(char arg[])
{
  int length = strlen(arg);

  for (size_t i = 0; i < length; i++) {
    char ch = arg[i];
    if (can_print_it(ch)) {
      printf("'%c' == '%d' ", ch, ch);
    }
  }

  printf("\n");
}

int can_print_it(char ch)
{
  return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[])
{
  for (size_t i = 0; i < argc; i++) {
    print_letters(argv[i]);
  }
}

#include <stdio.h>
#include <ctype.h>

void log_this(char letter)
{
  printf("%d: %c\n", letter, toupper(letter));
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("ERROR: You must provide one argument. No more. No less.\n");

    // NOTE
    // This is how you abort a program:
    return 1;
  }

  for (size_t i = 0; argv[1][i] != '\0'; i++) {
    char letter = argv[1][i];

    switch (letter) {
      case 'a':
      case 'A':
      case 'e':
      case 'E':
      case 'i':
      case 'I':
      case 'o':
      case 'O':
      case 'u':
      case 'U':
        log_this(letter); break;

      case 'y':
      case 'Y':
        if (i > 2) {
          log_this(letter);
        }

        break;
    }
  }

  return 0;
}

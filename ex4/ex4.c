#include <stdio.h>

int main(int argc, char const *argv[]) {
  int age = 12;
  int height;

  printf("You are %d years old.\n", age);
  printf("She is %d inches tall.\n", height);

  unsigned char temp[] = {
    0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x0a
  };
  unsigned int temp_len = 12;

  for (size_t i = 0; i < temp_len; i++) {
    printf("%c", temp[i]);
  }
  printf("\n");

  return 0;
}

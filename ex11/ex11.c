#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;
  while (i < argc) {
    printf("arg %d: %s\n", i, argv[i]);
    i++;
  }

  char *states[] = {
    "Mass", "Oregon", "California",
    "Michigan", "Texas", "Florida"
  };

  int num_states = 6;
  i = 0;
  while (i < num_states) {
    printf("state %d: %s\n", i, states[i]);
    i++;
  }

  printf("Now let's count backwards...\n");
  i = 5;
  while (i > -1) {
    printf("backwards state %d: %s\n", i, states[i]);
    i--;
  }

  printf("Now let's copy ARGV into STATES...\n");
  i = 0;
  while (i < argc) {
    // NOTE
    // Don't add too many command line arguments
    // or the script will seg-fault.
    printf("Copying %s from ARGV into STATES[%d]\n", argv[i], i);
    states[i] = argv[i];
    printf("%s\n", states[i]);
    i++;
  }

  return 0;
}

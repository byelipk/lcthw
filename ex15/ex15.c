#include <stdio.h>

// NOTE
// A program to demonstrate the use of pointers
//
int main(int argc, char const *argv[]) {
  // Create two arrays we care about
  int ages[] = { 12,60,55,24,17,9,10 };
  char *names[] = {
    "Pat", "Paul", "Pete", "Pasey", "Posley",
    "Paris", "Paula"
  };

  // Safely get the size of ages
  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  // First way using indexing
  for (i = 0; i < count; i++) {
    printf("%s had %d years alive\n", names[i], ages[i]);
  }

  printf("---\n");

  // Set the pointers to the start of the arrays
  int *cur_age    = ages;
  char **cur_name = names;

  // Why is cur_name preceeded by two ampersands?
  // Well, `names` is an array of strings. A string
  // is an array of chars. So cur_name is an array
  // of arrays.
  //
  // Dereferencing names once provides us with a pointer
  // to the beginning of the array.
  printf("Start of `names` array: %p\n", *names);
  // Start of `names` array: 0x10bcf9efc
  //
  // Dereferencing `names` once more provides us
  // with the first char of the first item in
  // the names array.
  printf("%c\n", **names);
  printf("First char of first item in `names` array: %c\n", **names);

  printf("%p\n", cur_age);
  // NOTE
  // cur_age is a pointer. To get the value
  // stored in the memory address pointed
  // to by cur_age, we need to dereference
  // the pointer.
  printf("%d\n", *(cur_age + 0));
  printf("%d\n", *(cur_age + 1));

  // Second way using pointers
  for (i = 0; i < count; i++) {
    printf("The value of (whatever %p is pointed at  plus %d) is %s\n",
      cur_name, i, *(cur_name + i));

    printf("The value of (whatever %p is pointed at  plus %d) is %d\n",
      cur_age, i, *(cur_age + i));

    printf("%s is %d years old.\n",
      *(cur_name + i), *(cur_age + i));
  }

  printf("---\n");

  // Third way, pointers are just arrays
  for (i = 0; i < count; i++) {
    printf("%s had %d years alive (again)\n",
      cur_name[i], cur_age[i]);
  }
}

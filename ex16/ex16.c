#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Create a data structure with 4 elements
// to describe a Person.
struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

// Person_Create
// @return *struct Person
struct Person *Person_Create(
  char *name, int age, int height, int weight)
{
  int struct_size = sizeof(struct Person);

  printf("Size of (struct Person) is %d bytes\n", struct_size);

  // Ask the OS for a portion of raw memory the size of
  // the Person struct given all the elements inside it.
  struct Person *who = malloc(struct_size);

  // Check that malloc didn't return an invalid pointer.
  assert(who != NULL);

  // NOTE
  // We create a copy of name because we want to make
  // sure the struct owns its own copy.
  who->name   = strdup(name);
  who->age    = age;
  who->height = height;
  who->weight = weight;

  return who;
};

void Person_Destroy(struct Person *who)
{
  assert(who != NULL);

  // NOTE
  // The order which we deallocate memory is important.
  // If we don't do it in this order we'll get a memory leak.

  // 1. Free memory allocated by strdup.
  free(who->name);

  // 2. Free up the rest of the struct.
  free(who);
}

void Person_Print(struct Person *who)
{
  printf("%s stands %d units tall, is %d years old, and weighs %d units.\n",
    who->name,
    who->height,
    who->age,
    who->weight
  );
}

int main(int argc, char const *argv[]) {
  char *pat_name = "Pat";
  char *jay_name = "Jay";

  printf("Size of (*pat_name) is %lu bytes\n", sizeof(pat_name));
  printf("Size of (*jay_name) is %lu bytes\n", sizeof(jay_name));

  // make two person structs
  struct Person *pat = Person_Create(pat_name, 30, 72, 233);
  struct Person *jay = Person_Create(jay_name, 38, 62, 250);

  // mutate name variables to ensure both structs have
  // their own copies of name.
  pat_name = "Pat White";
  jay_name = "Jay White";
  assert(pat->name != pat_name);
  assert(jay->name != jay_name);

  Person_Print(pat);
  Person_Print(jay);

  // mutate Pat's attributes:
  pat->age += 10;
  pat->height -= 23;
  pat->weight -= 15;

  // mutate Jay's attributes:
  jay->age += 10;
  jay->height -= 23;
  jay->weight -= 100000000;

  Person_Print(pat);
  Person_Print(jay);

  Person_Destroy(pat);
  Person_Destroy(jay);

  // Person_Destroy(NULL);

  return 0;
}

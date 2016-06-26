#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Child {
  char name[MAX_DATA];
};

struct Parent {
  struct Child children[MAX_ROWS];
};

int main(int argc, char const *argv[]) {
  struct Parent *parent = malloc(sizeof(struct Parent));
  struct Child *child   = malloc(sizeof(struct Child));

  strncpy(child->name, "Pat White", MAX_DATA);

  parent->children[0] = *child;

  printf("%p -> %s\n",
    parent->children[0].name,
    parent->children[0].name);

  // Cleanup
  free(parent);
  free(child);
}

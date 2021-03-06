#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

void Object_destroy(void *self)
{
  assert(self != NULL);

  Object *obj = self;

  if (obj) {
    printf("[%s] ", __func__);
    if (obj->description) {
      printf("%s\n", obj->description);
      free(obj->description);
    }
    free(obj);
  }
}

void Object_describe(void *self)
{
  assert(self != NULL);
  Object *obj = self;
  printf("%s.\n", obj->description);
}

int Object_init(void *self)
{
  // do nothing really
  assert(self != NULL);
  return 1;
}

void *Object_move(void *self, Direction direction)
{
  assert(self != NULL);
  assert(direction >= 0 && direction <= 3);

  printf("You can't go in that direction!\n");

  return NULL;
}

int Object_attack(void *self, int damage)
{
  assert(self != NULL);
  printf("You can't attack that!\n");
  return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
  assert(description != NULL);

  printf("NEW() -> %s\n", description);

  // setup the default functions in case they aren't set
  if (!proto.init)     proto.init     = Object_init;
  if (!proto.describe) proto.describe = Object_describe;
  if (!proto.destroy)  proto.destroy  = Object_destroy;
  if (!proto.attack)   proto.attack   = Object_attack;
  if (!proto.move)     proto.move     = Object_move;

  // This seems weird, but we can make a struct of one
  // size, then point a different pointer at it to
  // "cast" it as another type.
  //
  // Let's break it down:
  //
  // => I call NEW(Room, "Hello.") which the CPP expands
  //    as a macro into Object_new(sizeof(Room), RoomProto, "Hello.").
  //
  // => This runs, and inside Object_new I allocate a
  //    piece of memory that's Room in size, but point
  //    a Object *el pointer at it.
  //
  // => Since C puts the Room.proto field first, that
  //    means the el pointer is really only pointing at
  //    enough of the block of memory to see a full
  //    Object struct. It has no idea that it's even
  //    called proto.
  //
  // => It then uses this Object *el pointer to set the
  //    contents of the piece of memory correctly with
  //    *el = proto;. Remember that you can copy structs,
  //    and that *el means "the value of whatever el
  //    points at", so this means "assign the proto
  //    struct to whatever el points at".
  //
  // => Now that this mystery struct is filled in with
  //    the right data from proto, the function can then
  //    call init or destroy on the Object, but the cool
  //    part is whoever called this function can change
  //    these out for whatever ones they want.
  Object *el = calloc(1, size);
  *el = proto;

  assert(el != NULL);

  // copy the description over
  el->description = strdup(description);

  // initialize it with whatever init we were given
  if (!el->init(el)) {
    // looks like it didn't initialize properly
    el->destroy(el);
    return NULL;
  } else {
    // all done, we made an object of any type
    return el;
  }
}

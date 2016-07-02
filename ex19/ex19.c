#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h"
#include <assert.h>

// MONSTER
int Monster_attack(void *self, int damage)
{
  assert(self != NULL);
  Monster *monster = self;

  printf("You attack %s!\n", monster->_(description));

  monster->hit_points -= damage;

  if (monster->hit_points > 0) {
    printf("It is still alive!\n");
    return 0;
  } else {
    printf("It is dead!\n");
    return 1;
  }
}

int Monster_init(void *self)
{
  assert(self != NULL);
  Monster *monster = self;
  monster->hit_points = 10;
  return 1;
}

Object MonsterProto = {
  .init = Monster_init,
  .attack = Monster_attack
};

// ROOM
void *Room_move(void *self, Direction direction)
{
  assert(self != NULL);
  assert(direction >= 0 && direction <= 3);

  Room *room = self;
  Room *next = NULL;

  if (direction == NORTH && room->north) {
    printf("You go north...\n");
    next = room->north;

  } else if (direction == SOUTH && room->south) {
    printf("You go south...\n");
    next = room->south;

  } else if (direction == EAST && room->east) {
    printf("You go east...\n");
    next = room->east;

  } else if (direction == WEST && room->west) {
    printf("You go west...\n");
    next = room->west;

  } else  {
    printf("You can't go in that direction.\n");
  }

  if (next) {
    next->_(describe(next));
  }

  return next;
}

int Room_attack(void *self, int damage)
{
  assert(self != NULL);
  Room *room = self;

  Monster *monster = room->bad_guy;

  if (monster) {
    monster->_(attack(monster, damage));
    return 1;
  } else {
    printf("You flail in the air at nothing. Idiot!");
    return 0;
  }
}

void Room_destroy(void *self)
{
  assert(self != NULL);
  Room *room = self;

  Object_destroy(room);
}

Object RoomProto = {
  .move    = Room_move,
  .attack  = Room_attack,
  .destroy = Room_destroy
};

// MAP
void *Map_move(void *self, Direction direction)
{
  assert(self != NULL);
  assert(direction >= 0 && direction <= 3);

  Map *map = self;

  assert(map->location != NULL);
  Room *location = map->location;

  Room *next = NULL;

  next = location->_(move(location, direction));

  if (next) {
    map->location = next;
  }

  return next;
}

int Map_attack(void *self, int damage)
{
  assert(self != NULL);

  Map *map = self;
  Room *location = map->location;

  return location->_(attack(location, damage));
}

int Map_init(void *self)
{
  assert(self != NULL);

  Map *map = self;

  // make some rooms for a small map
  Room *hall    = NEW(Room, "The great Hall");
  assert(hall    != NULL);

  Room *throne  = NEW(Room, "The throne room");
  assert(throne  != NULL);

  Room *arena   = NEW(Room, "The arena, with the minotaur");
  assert(arena   != NULL);

  Room *kitchen = NEW(Room, "Kitchen, you have the knife now");
  assert(kitchen != NULL);


  // put the bad guy in the arena
  arena->bad_guy = NEW(Monster, "The evil minotaur");

  // setup the map rooms
  hall->north = throne;

  throne->west = arena;
  throne->east = kitchen;
  throne->south = hall;

  arena->east = throne;
  kitchen->west = throne;

  // start the map and the character off in the hall
  map->start    = hall;
  map->location = hall;

  return 1;
}

Object MapProto = {
  .init    = Map_init,
  .attack  = Map_attack,
  .move    = Map_move
};

int process_input(Map *game)
{
  assert(game != NULL);

  printf("\n> ");

  char ch = getchar();
  getchar(); // eat ENTER

  assert(&ch != NULL);

  int damage = rand() % 4;

  switch(ch) {
    case 'q':
      printf("Giving up? You suck.\n");
      return 0;
      break;

    case 'n':
      game->_(move)(game, NORTH);
      break;

    case 's':
      game->_(move)(game, SOUTH);
      break;

    case 'e':
      game->_(move)(game, EAST);
      break;

    case 'w':
      game->_(move)(game, WEST);
      break;

    case 'a':
      game->_(attack)(game, damage);
      break;

    case 'l':
      printf("You can go:\n");
      if(game->location->north) printf("NORTH\n");
      if(game->location->south) printf("SOUTH\n");
      if(game->location->east) printf("EAST\n");
      if(game->location->west) printf("WEST\n");
      break;

    default:
        printf("What?: %d\n", ch);
  }

  return 1;
}

int main(int argc, char *argv[]) {
  // simple way to setup the randomness
  srand(time(NULL));

  // make our map to work with
  Map *game = NEW(Map, "The Hall of the Minotaur.");

  printf("You enter the ");
  game->location->_(describe)(game->location);

  while(process_input(game)) {
    // do nothing
  }

  return 0;
}

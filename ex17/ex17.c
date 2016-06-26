#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void Address_print(struct Address *addr)
{
  printf("%d %s %s\n",
    addr->id, addr->name, addr->email);
}

void Database_close(struct Connection *conn)
{
  if (conn) {
    if (conn->file) fclose(conn->file);
    if (conn->db)   free(conn->db);
    free(conn);
  }
}

void die(struct Connection *conn, char *message)
{
  Database_close(conn);

  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }
  exit(0);
}

void Database_load(struct Connection *conn)
{
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1) die(conn, "Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode)
{
  // STEP 1: Allocate memory from the heap to store the connection struct.
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) die(conn, "Memory error! [CONN]");

  // STEP 2: Allocate memory from the heap for the database struct.
  conn->db = malloc(sizeof(struct Database));
  if (!conn->db) die(conn, "Memory error! [DB]");

  // STEP 3: Either create a new file or open an existing file for reading.
  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn->file) die(conn, "Failed to open the file.");

  return conn;
}

void Database_write(struct Connection *conn)
{
  // NOTE
  // VOID
  // rewind(FILE *stream);
  //
  // The rewind() function sets the file position
  // indicator for the stream pointed to by `stream`
  // to the beginning of the file.
  rewind(conn->file);

  // NOTE
  // size_t
  // fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);
  //
  // The function fwrite() writes `nitems` objects, each
  // `size` bytes long, to the stream pointed to by `stream`,
  // obtaining them from the location given by `ptr`.
  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1) die(conn, "Failed to write database!");

  rc = fflush(conn->file);
  if (rc == -1) die(conn, "Cannot flush database!");
}

void Database_create(struct Connection *conn)
{
  // NOTE
  // When we create a new database we're going
  // ahead and creating MAX_ROWS of data.
  for (size_t i = 0; i < MAX_ROWS; i++) {
    struct Address addr = {.id = i, .set = 0};
    conn->db->rows[i] = addr;
  }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
  if (strlen(name) > MAX_DATA || strlen(email) > MAX_DATA) {
    die(conn, "Name or email is too long.");
  }

  // Get the location in memory of the address
  struct Address *addr = &conn->db->rows[id];
  if (addr->set) die(conn, "Already set. Delete it first.");

  addr->set = 1;

  // WARNING: bug, read the "How To Break It" and fix this.
  // SOLUTION: force last character to `\0`
  char *res = strncpy(addr->name, name, MAX_DATA);

  // demonstrate the strncpy bug
  if (!res) die(conn, "Name copy failed");

  res = strncpy(addr->email, email, MAX_DATA);
  if (!res) die(conn, "Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
  // Get the location in memory of the address
  struct Address *addr = &conn->db->rows[id];

  if (addr->set) {
    Address_print(addr);
  } else {
    die(conn, "Address ID is not set");
  }
}

void Database_delete(struct Connection *conn, int id)
{
  // STEP 1: Create a struct prototype, initializing
  // the `id` and `set` fields.
  struct Address addr = {.id = id, .set = 0};

  // STEP 2: Copy the struct prototype into the rows
  // array by assigning it the element with `id`.
  conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
  struct Database *db = conn->db;

  for (size_t i = 0; i < MAX_ROWS; i++) {
    // Get the location in memory of the address
    struct Address *cur = &db->rows[i];

    if (cur->set) {
      Address_print(cur);
    }
  }
}


int main(int argc, char *argv[]) {

  char *filename = argv[1];
  char action = argv[2][0];
  int id = 0;

  struct Connection *conn = Database_open(filename, action);

  if (argc < 3) die(conn, "USAGE: ex17 <dbfile> <action> [action params]");
  if (argc > 3) id = atoi(argv[3]);
  if (id >= MAX_ROWS) die(conn, "There's not that many records!");

  switch (action) {
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;

    case 'g':
      if (argc != 4) die(conn, "Need an id to get");

      Database_get(conn, id);
      break;

    case 's':
      if (argc != 6) die(conn, "Need id, name, email to set");

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

    case 'd':
      if (argc != 4) die(conn, "Need id to delete");

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'l':
      Database_list(conn);
      break;

    default:
      die(conn, "Invalid action, only: c=create, g=get, s=set, d=del, l=list");
  }

  Database_close(conn);

  return 0;
}


// $ ./ex17 db.dat c
// $ ./ex17 db.dat s 1 zed zed@zedshaw.com
// $ ./ex17 db.dat s 2 frank frank@zedshaw.com
// $ ./ex17 db.dat s 3 joe joe@zedshaw.com
// $ ./ex17 db.dat s 4 zed zed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.comzed@zedshaw.com
// $ ./ex17 db.dat g 1

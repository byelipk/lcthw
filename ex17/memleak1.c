#include <stdio.h>
#include <stdlib.h>

void leak() {
  char *memory = malloc(1024);
  printf("%p\n", memory);
}

int main(int argc, char const *argv[]) {
  // NOTE
  // If you get a block of memory from malloc, and
  // have that pointer on the stack, then when the
  // function exits, the pointer will get popped off
  // and lost.
  leak();
}

// valgrind ./memleak1
//
// ==2317== HEAP SUMMARY:
// ==2317==     in use at exit: 30,441 bytes in 375 blocks
// ==2317==   total heap usage: 451 allocs, 76 frees, 36,385 bytes allocated
// ==2317==
// ==2317== LEAK SUMMARY:
// ==2317==    definitely lost: 1,024 bytes in 1 blocks
// ==2317==    indirectly lost: 0 bytes in 0 blocks
// ==2317==      possibly lost: 0 bytes in 0 blocks
// ==2317==    still reachable: 4,096 bytes in 1 blocks
// ==2317==         suppressed: 25,321 bytes in 373 blocks
// ==2317== Rerun with --leak-check=full to see details of leaked memory
// ==2317==
// ==2317== For counts of detected and suppressed errors, rerun with: -v
// ==2317== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 1 from 1)

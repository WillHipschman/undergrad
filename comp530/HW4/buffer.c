/*
 * Author: William Hipschman
 * PID: 714228116
 * This file contains methods for BoundedBuffers.  Withdraw and deposit both modify the buffer passed to them.
 */


//System defined inclusions
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

//User defined inclusions
#include "st.h"
#include "semaphore.h"
#include "buffer.h"

/*
 * The deposit function inserts a character into the BoundedBuffer pointed to by b.  If the buffer is already full then the method blocks
 * and waits for elements to be consumed from the buffer.
 * Invariant: At all times 0 <= buffer.count < SIZE (SIZE is defined in buffer.h)
 */
void deposit(BoundedBuffer *b, char c){
  
  down(b->deposit);
  assert((b->count) < SIZE);
  
  b->array[b->nextIn] = c;
  b->nextIn = (b->nextIn + 1) % SIZE;
  b->count = b->count + 1;


  //printf("Deposit-Count: %d, nextIn: %d, Char: %c\n", b->count, b->nextIn, b->array[b->nextIn - 1]);
  assert(b->count > 0);
  up(b->withdraw);//tell withdraw there is another character to consume
}
/*
 * The withdraw function removes a character from the BoundedBuffer pointed to by b.  If the buffer is empty then the method blocks
 * and waits for elements to be added to the buffer.
 * Invariant: At all times 0<= buffer.count < SIZE (SIZE is defined in buffer.h)
 */
char Remove(BoundedBuffer *b){  
  
  down(b->withdraw);
  assert((b->count) > 0);
  
  char c = b->array[b->nextOut];
  b->nextOut = (b->nextOut + 1) % SIZE;
  b->count = b->count - 1;


  //  printf("Withdraw-Count: %d, nextOut: %d, Char: %c\n", b->count, b->nextOut, c);
  assert(b->count < SIZE);
  up(b->deposit);//tell deposit there is room to produce another character
  
  return c;
}


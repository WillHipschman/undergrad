/*
 * Author: William Hipschman
 * PID: 714228116
 * This program reads input from standard input and copies 80 characters
 * at a time to standard output replacing every carriage return with a space
 * and every adjacent pair of asterisks with a carat.  If no input is entered
 * no output is return.  If the number of characters mod 80 is not 0 then the
 * trailing characters will not be printed.
 *
 * The program does this with multiple threads using the ST library.  It processes
 * input in pipeline stages.  The description of each pipeline stage is before its method. 
 */

//system libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>

//usetr libraries
#include "st.h"
#include "semaphore.h"
#include "buffer.h"

//definitions
#define ERR_RETURN -1
#define SPACE ' '
#define NEWLINE '\n'
#define ASTERISK '*'
#define CARAT '^'
#define NUM_ARGS 1
#define TRUE 1
#define FALSE 0
#define LINE_SIZE 80

//structure to hold two buffers to pass to ST functions
typedef struct{

  BoundedBuffer *in;
  BoundedBuffer *out;
}Buffers;

//method declarations
void *pipeline_stage1(void *s);
void *pipeline_stage2(void *s);
void *pipeline_stage3(void *s);
void *pipeline_stage4(void *s);
void initialize_buffer(BoundedBuffer *b, semaphore *deposit, semaphore *withdraw);
void print_array(char *array);

//global variables
char array[LINE_SIZE]; //the characters to be printed on a line in the last pipeline stage

/*
 * The main method performs the following functions:
 *    1. Checks that the number of parameters is correct
 *    2. Allocates space for buffers
 *    3. Initializes ST thread library
 *    4. Initializes buffer values
 *    5. Creates threads for each pipeline stage and passes corresponding buffer
 *    6. Exits
 *
 * The pipeline stages are as follows:
 *    1. Input production (reads data from stdin)
 *    2. Input consumption and newline replacement production
 *    3. Newline replacement consumption and output production (replaces asterisk producing buffer data that should be written)
 *    4. Output consumption (writes data)
 */
int main(int argc, char *argv[])
{
  
  //check that parameter count is correct
  if(argc != NUM_ARGS){
    printf("ERROR: Incorrect number of arguments %d.  This program takes %d arguments", argc, NUM_ARGS);
    exit(ERR_RETURN);
  }
  
  //initialize ST library
  if (st_init() < 0) {
    perror("st_init");
    exit(ERR_RETURN);
  }
  
  /* create buffers */
  BoundedBuffer buffer12;
  semaphore deposit12;
  semaphore withdraw12;
  initialize_buffer(&buffer12, &deposit12, &withdraw12);

  BoundedBuffer buffer23;
  semaphore deposit23;
  semaphore withdraw23;
  initialize_buffer(&buffer23, &deposit23, &withdraw23);

  Buffers stage2buffers;
  (&stage2buffers)->in = &buffer12;
  (&stage2buffers)->out = &buffer23;

  BoundedBuffer buffer34;
  semaphore deposit34;
  semaphore withdraw34;
  initialize_buffer(&buffer34, &deposit34, &withdraw34);

  Buffers stage3buffers;
  (&stage3buffers)->in = &buffer23;
  (&stage3buffers)->out = &buffer34;

  
  /* start it first so it will block first 
   * The first parameter is the initial function executed in 
   * the thread.  The second is the only allowed parameter to
   * the initial function and must be a pointer to any type.
   */

  if (st_thread_create(pipeline_stage1, &buffer12, 0, 0) == NULL) {
    perror("st_thread_create");
    exit(1);
  } 
  if (st_thread_create(pipeline_stage2, &stage2buffers, 0, 0) == NULL) {
    perror("st_thread_create");
    exit(1);
  }
  if (st_thread_create(pipeline_stage3, &stage3buffers, 0, 0) == NULL) {
    perror("st_thread_create");
    exit(1);
  }
  if (st_thread_create(pipeline_stage4, &buffer34, 0, 0) == NULL) {
    perror("st_thread_create");
    exit(1);
  }

  /* causes the main thread to exit with others still running */
  fflush(stdout);
  st_thread_exit(NULL);
}


/* The initial function executed in a thread must have 
 * a function declaration like the following -- note
 * the use of void * (pointer to any type).
 */

/*
 *This method takes a pointer to a buffer and deposits characters from stdin into the buffer
 */
void *pipeline_stage1(void *s)
{
  BoundedBuffer *b = s;  /* b has the proper type instead of void */
  
  char c;
  while((c = getc(stdin)) != EOF)
    deposit(b, c);

  deposit(b, EOF);

  fflush(stdout);
  st_thread_exit(NULL);
}

/*
 * This method takes a pointer to a structure containing two buffers.  It reads characters from the first buffer
 * and deposits them in the second buffer.  If the character is a newline it deposits a space instead of a newline.
 */
void *pipeline_stage2(void *s)
{
  Buffers *b = s;  /* b has the proper type instead of void */

  char c;
  while((c = Remove(b->in)) != EOF){
    if(c == NEWLINE)
      deposit(b->out, SPACE);
    else
      deposit(b->out, c);
  }
  deposit(b->out, EOF);

  fflush(stdout);
  st_thread_exit(NULL);
}

/*
 * This method takes a pointer to a structure containing two buffers.  It reads characters from the first buffer
 * and deposits them in the second buffer.  If two asterisks are encountered in a row it deposits one carat instead
 * of the two asterisks.
 */
void *pipeline_stage3(void *s)
{
  Buffers *b = s;  /* b has the proper type instead of void */
  
  char c;
  int  flag = FALSE;
  while((c = Remove(b->in)) != EOF){
    if(flag == TRUE)
      if(c == ASTERISK){
	deposit(b->out, CARAT);
	flag = FALSE;
      }
      else{
	deposit(b->out, ASTERISK);
	deposit(b->out, c);
	flag = FALSE;
      }
    else if(c == ASTERISK){
      flag = TRUE;
      continue;
    }
    else
      deposit(b->out, c);
  }
  deposit(b->out, EOF);
  
  fflush(stdout);
  st_thread_exit(NULL);
}

/*
 * This method takes a pointer to a buffer.  It adds the characters to an array of LINE_SIZE and prints
 * this array when the number of elements is equal to LINE_SIZE.
 */
void *pipeline_stage4(void *s)
{
  BoundedBuffer *b = s;  /* b has the proper type instead of void */
  
  char c;
  int count = 0;
  while((c = Remove(b)) != EOF){
    array[count] = c;
    if(count == LINE_SIZE - 1){
      print_array(array);
      count = 0;
      continue;
    }
    count++;
  }
  
  fflush(stdout);
  st_thread_exit(NULL);
}

/*
 * This method initializes buffers.  It initializes semaphores to have size SIZE and 0, so that they will lock
 * when the buffer they are associated with is full or empty, respectively.
 */
void initialize_buffer(BoundedBuffer *b, semaphore *deposit, semaphore *withdraw){

  b->count = 0;
  b->nextIn = 0;
  b->nextOut = 0;
  createSem(deposit, SIZE);
  createSem(withdraw, 0);
  b->deposit = deposit;
  b->withdraw = withdraw;
}

void print_array(char *array){

  int count = 0;
  while(count < LINE_SIZE){
    fputc(*array, stdout);
    count++;
    array++;
  }
  fputc('\n', stdout);
}

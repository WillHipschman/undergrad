/* Author: Don Smith
 * This program runs as two ST threads in a single Linux process.
 * One of the threads is a "ping" (outputs a string) and the other
 * is a "pong" (outputs a string only after the ping thread has
 * output its string).  The ping thread executes a loop for a specified 
 * number of iterations.  At each iteration, the ping thread outputs its
 * "ping" message string to stdout, pauses (sleeps) for a random number
 * of seconds, and unblocks the pong thread from a semaphore (pong_turn)
 * that allows the pong thread to run.  The ping thread then blocks on a 
 * different semaphore (ping_turn) that will allow it to run only when 
 * the pong thread unblocks it.  When it is unblocked, the pong thread 
 * outputs its message string, pauses for a random number of seconds,
 * unblocks the ping thread, and then blocks again until the ping thread 
 * unblocks it.
 *
 * When the ping thread has completed its specified number of loop 
 * iterations, it sets a global boolean variable (quit) to true and unblocks 
 * the pong thread.  It then terminates.  The pong thread terminates when 
 * it is unblocked and finds the global variable set to true.
 * There are four positional parameters to this program in the following 
 * order:
 *  - the ping thread output string
 *  - the pong thread  output string
 *  - the number of loop iterations for ping thread
 *  - the maximum random sleep time (seconds)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>

#include "st.h"  /* required to compile with the threads library */
/* WARNING -- semaphore.h must be included AFTER st.h */
#include "semaphore.h"  /* required to compile with semaphores */

#define SEED_ONE 97  /* a prime number for seeding rand() */
#define SEED_TWO 79  /* another prime number */
#define NUM_ARGS 5  /* program name + 4 positional parameters */
#define ERR_RETURN -1
#define MAX_SLEEP 60  /* don't allow sleeping for more than a minute */

typedef struct
{
  semaphore ping_turn;
  semaphore pong_turn;
} shared_semaphores;

/* type definition for a structure to be used to initialize
 * each thread
 */

typedef struct
{
  const char *my_call;
  unsigned int my_seed;
  int count;
  int max_sleep;
} thread_init;

void *ping(void *s); /* function prototypes for functions executed as threads */
void *pong(void *s);

bool quit = false;   /* a global variable shared by thread functions */ 
shared_semaphores the_sems; /* semaphores shared by the threads */

int main(int argc, char *argv[])
{
  int loop_count;
  int sleep_secs;

  const int ping_arg = 1;
  const int pong_arg = 2;
  const int loop_arg = 3;
  const int sleep_arg = 4;

  const int ping_sem_init = 1;  /* don't block first time */
  const int pong_sem_init = 0;  /* do block first time */


  /* initializer structures for threads */
  thread_init ping_init;
  thread_init pong_init;

  /* validity check parameter count */
  if (argc != NUM_ARGS)
    {
      printf("Bad parameter count %d\n", argc);
      printf("Positional parameters: ping & pong strings, loop count, sleep limit\n");
      exit (ERR_RETURN);
    }

  /* the loop count is the third positional parameter */
  loop_count = atoi(argv[loop_arg]);  /* atoi converts string to integer */

  /* the sleep limit seconds is the fourth positional */
  sleep_secs = atoi(argv[sleep_arg]);  /* atoi converts string to integer */
  if (sleep_secs > MAX_SLEEP)
    {
      printf("Sleep of %d exceeds maximum %d\n", sleep_secs, MAX_SLEEP);
      exit (ERR_RETURN);
    }
 
  /* This call is required to initialize the thread library */
  if (st_init() < 0) {
    perror("st_init");
    exit(1);
  }

  /* initialize the shared semaphores */
  createSem(&the_sems.ping_turn, ping_sem_init); /* block-unblock ping */
  createSem(&the_sems.pong_turn, pong_sem_init);  /* block-unblock pong */

  /* Create a separate thread for each of ping and pong */

  /* create an initializer for ping thread */
  ping_init.my_call = argv[ping_arg];
  ping_init.my_seed = (unsigned int) getpid() + SEED_ONE;  /* unique random seed each run */
  ping_init.count = loop_count;
  ping_init.max_sleep = sleep_secs;

  /* The first parameter is the initial function executed in 
   * the thread.  The second is the only allowed parameter to
   * the initial function and must be a pointer to any type.
   */

  if (st_thread_create(ping, &ping_init, 0, 0) == NULL) 
     {
      perror("st_thread_create");
      exit(1);
     }

  /* create an initializer for pong thread */
  pong_init.my_call = argv[pong_arg];
  pong_init.my_seed = (unsigned int) getpid() + SEED_TWO;  /* unique random seed each run */
  pong_init.count = 0;  /* not used by pong */
  pong_init.max_sleep = sleep_secs;

  if (st_thread_create(pong, &pong_init, 0, 0) == NULL) 
     {
      perror("st_thread_create");
      exit(1);
     }

  /* causes the main thread to exit with others still running */
  printf("Main thread exiting\n");
  fflush(stdout);
  st_thread_exit(NULL);
}


/* The initial function executed in a thread must have 
 * a function declaration like the following -- note
 * the use of void * (pointer to any type).
 */

void *ping(void *s)
{
  thread_init *p = s;  /* p has the proper type instead of void */
  int i;
  int sleep_time;
  unsigned int rand_seed = p->my_seed;

  for (i = 0; i < p->count; i++)
     {
      down(&the_sems.ping_turn); /* block this thread */
      assert(the_sems.ping_turn.value == 0);
      sleep_time = 1 + (rand_r(&rand_seed) % p->max_sleep);
      printf("%s (Delay %d seconds before Pong thread)\n", p->my_call, sleep_time);
      st_sleep(sleep_time); 
      assert(the_sems.pong_turn.value == 0);
      up(&the_sems.pong_turn);  /* unblock pong thread */
     }
  quit = true;
  printf("Ping exiting\n");

  assert(the_sems.pong_turn.value == 0);
  up(&the_sems.pong_turn); /* unblock pong thread */
  st_thread_exit(NULL);
}

void *pong(void *s)
{
  thread_init *p = s;  /* p has the proper type instead of void */
  bool forever = true;
  int sleep_time;
  unsigned int rand_seed = p->my_seed;

  while (forever)
     {
      down(&the_sems.pong_turn);  /* block this thread */
      assert(the_sems.pong_turn.value == 0);
      if (quit)
         break;

      sleep_time = 1 + (rand_r(&rand_seed) % p->max_sleep);
      printf("%s (Delay %d seconds before Ping thread)\n", p->my_call, sleep_time);
      st_sleep(sleep_time); 
      assert(the_sems.ping_turn.value == 0);
      up(&the_sems.ping_turn);  /* unblock ping thread */
     }
  printf("Pong exiting\n");
  st_thread_exit(NULL);
}

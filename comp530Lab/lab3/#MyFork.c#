/* Author: Don Smith
 * This program runs as two Linux OS processes -- a parent process and
 * a child process.  Both processes execute a loop for a specified 
 * number of iterations.  At each iteration, the process pauses 
 * execution (OS system call to sleep) for a specified number of seconds 
 * and then outputs a string to stdout.  The child process terminates
 * when it has completed all its loop iterations.  The parent process
 * completes its loop iterations and then waits (OS system call to
 * wait) until it has confirmation that the child has terminated before
 * it also terminates.  There are four positional parameters to this
 * program in the following order:
 *  - the parent process output string
 *  - the child process output string
 *  - the number of loop iterations
 *  - the number of seconds to sleep between loop interations
 */

#define NUM_ARGS 5  /* program name + 4 positional parameters */
#define ERR_RETURN -1

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>

int main(int argc, char *argv[])
{
  pid_t cpid, term_pid; /* type for Linux process id */
  int chld_status; 
  int i;
  int loop_count;
  int sleep_secs;

  /* validity check parameter count */
  if (argc != NUM_ARGS)
    {
      printf("Bad parameter count %d\n", argc);
      printf("Positional parameters: parent & child strings, loop count, sleep seconds\n");
      exit (ERR_RETURN);
    }

  /* the loop count is the third positional parameter */
  loop_count = atoi(argv[3]);  /* atoi converts string to integer */

  /* the sleep seconds is the fourth positional */
  sleep_secs = atoi(argv[4]);  /* atoi converts string to integer */
 
  /* create child process, report error if present and exit */  
  cpid = fork(); 
  if (cpid == -1) 
     {
      perror("fork"); /* perror creates description of OS error codes */
      exit(ERR_RETURN); 
     }

  /* conditional execution of statements depending on whether the code is
   * if running as the parent or child process.
   */

  if (cpid == 0) 
     { 
      /* Loop iterations executed by the child process */
      for (i = 0; i < loop_count; i++)
	  {
	   sleep(sleep_secs);
	   printf("C: %s\n", argv[2]); /* positional parameter 2 is the child's string */
          }
      printf("Child process terminating.\n");
      exit (0);
     }  /* end of code that can be executed by the child process */
  else 
     {
      /* Loop iterations executed by the parent process */
      for (i = 0; i < loop_count; i++)
	  {
	   sleep(sleep_secs);
	   printf("P: %s\n", argv[1]); /* positional parameter 1 is the parent's string */
          }
       
      /* wait for the child to terminate and determine its exit status */
      /* this is necessary to prevent the accumulation of "Zombie" processes */

      term_pid = waitpid(cpid, &chld_status, 0);
      if (term_pid == -1) 
          perror("waitpid"); 
      else
	 {
          if (WIFEXITED(chld_status)) 
	     printf("PID %d exited, status = %d\n", cpid, WEXITSTATUS(chld_status));
          else
	     printf("PID %d did not exit normally\n", cpid);
         }

      printf("Parent process terminating.\n");
      exit(0);
     } /* end of code that can be executed by the parent process */
}

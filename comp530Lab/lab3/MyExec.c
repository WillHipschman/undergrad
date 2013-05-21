/* Author: Don Smith
 * Program to emulate the core operation in a shell program.
 * It uses the OS system call execvp to replace its process image
 * (executable and stack) with a new image (executable and stack).
 * The new code runs with the same process id and file descriptors
 * (e.g., stdin and stdout) as this original program.  The process
 * terminates when the new executable returns or exits.
 * This program has three positional parameters in the following
 * order:
 *  - The file name of the executable to be run (must be in the set
 *    of directories named in the PATH environment variable which
 *    is searched for the named file, or be an explicit full pathname).
 *  - Parameter string 1 to be passed to the new program as positional
 *    parameter 1
 *  - Parameter string 2 to be passed to the new program as positional
 *    parameter 2
 * NOTE: string 2 or both string 1 and string 2 may be absent. This 
 * program cannot be used to execute a new program that REQUIRES more 
 * than two parameters.
 */

#define MAX_ARGS 4  /* allows program name + 3 positional parameters */
#define MIN_ARGS 2  /* must have at least 1 positional parameter */
#define NUM_PARMS 4  /* allows program name + 2 parameters + NULL */
#define ERR_RETURN -1

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int i;
  int rc;
  char *parms_array[NUM_PARMS];  /* arrary of pointers to strings */

  /* validity check parameter count */
  if ((argc > MAX_ARGS) ||
      (argc < MIN_ARGS))
    {
      printf("Bad parameter count %d\n", argc);
      printf("Positional parameters: executable name, [parm 1 [parm 2]]\n");
      exit (ERR_RETURN);
    }

  /* The positional parameters passed to this program as pointers to 
   * strings can just be passed on to execvp which requires a
   * NULL-terminated array of pointers to strings.  By convention, the
   * first entry in the array is the file name to be executed, and the
   * next non-null pointers are for positional parameters to that program.
   */

  for (i = 0; i < (argc - 1); i++)
       parms_array[i] = argv[i+1];
  parms_array[i] = NULL;

  /* do the OS system call, if there is an error return, report it.  Otherwise
   * this call will not return and the new image will execute as this process ID.
   */

  rc = execvp(parms_array[0], parms_array);
  if (rc == -1) 
     {
      perror("execvp"); 
      exit(-1); 
     }
}

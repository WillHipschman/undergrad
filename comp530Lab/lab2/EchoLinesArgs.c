/* This program reads lines terminated by newlines from stdin 
 * and echos them to stdout preceded by a specified string.
 * There are three positional parameters to the program in
 * the following order:
 *  - a string value to precede the echo line,
 *  - a maximum size of the input line to echo (must be less
 *    than the size of the character array holding the output).
 *  - the maximum number of lines the program will accept before
 *    terminating.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define ECHO_SIZE 200  /* allocation size for character array */
#define NUM_ARGS 4     /* require program name + 3 positional */
#define ERR_RETURN -1  /* return -1 on any error condition */
#define OK_RETURN 0    /* return 0 if all OK */

int main(int argc, char* argv[])
{
  int max_line;
  int max_count;
  int line_count = 0;
  char echo_data[ECHO_SIZE];

  /* validity check parameter count */
  if (argc != NUM_ARGS)
    {
      fputs("Bad parameter count\n", stdout);
      return (ERR_RETURN);
    }

  /* the maximum input line is the second positional */
  max_line = atoi(argv[2]);  /* atoi converts string to integer */
  if (max_line > ECHO_SIZE)
    {
      fputs("Bad maximum input line size\n", stdout);
      return (ERR_RETURN);
    }

  /* the maximum number of lines is the third positional */
  max_count = atoi(argv[3]);  /* atoi converts string to integer */
   
  /* read lines up to maximum line size and count of lines.  Note
   * that fgets stops reading the buffered stdin on 3 conditions:
   * EOF or error, newline, and max line size -1.  A '\0' 
   * (string terminator) is always the last character stored.
   * NULL is returned if EOF or error.
   */

  while (fgets(echo_data, max_line, stdin) != NULL)
    {
     /* the preceding string is the first positional */
     fputs(argv[1], stdout);
     fputs(echo_data, stdout); /* no newline if stopped on size */
     if ((line_count += 1) == max_count)
        break;
    }
  return 0;
}

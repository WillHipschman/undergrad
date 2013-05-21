/* Author: Don Smith
 * A program that does nothing useful but provides some examples of using
 * strings in C and using (f)printf to format output.  The program requires
 * two positional parameters in the following sequence:
 *  - a string of characters
 *  - a string that is the character representation of a integer that can 
 *    be represented with a long.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define NUM_ARGS 3  /* program name + 2 positional parameters */
#define ERR_RETURN -1
#define NUMBER_BASE 1000
#define MAX_STRING 20

int main(int argc, char* argv[])
{
  int my_int1 = NUMBER_BASE;
  int my_int2 = NUMBER_BASE *10;
  int my_int3 = NUMBER_BASE / 2;
  int my_int4 = NUMBER_BASE * 2;

  char my_string[MAX_STRING + 1] = ""; /* array of characters as empty string */
  int parm_length;

  /* validity check parameter count */
  if (argc != NUM_ARGS)
    {
      printf("Bad parameter count %d\n", argc);
      printf("Positional parameters: arbitrary string, integer\n");
      exit (ERR_RETURN);
    }
  char *parm_string = argv[1];   /* copies pointer to parameter string */
  long parm_long = atol(argv[2]); /* converts string to long */

  /* format directive contains only output characters */
  fprintf(stdout, "Hello World!\n");

  /* format directive with output characters and string variable */
  fprintf(stdout, "String was: %s\n", parm_string);

  /* format directive with output characters, integer, and string variables */
  fprintf(stdout, "String and integer are: %s, %ld\n", parm_string, parm_long);

  /* format directive with integers (including integer expression) */
  fprintf(stdout, "%d %d %d\n", my_int1, (my_int2/10 + my_int3), my_int4);

  /* output the length of the parameter string */
  parm_length = strlen(parm_string);
  printf("The parameter string is %d bytes\n", parm_length);

  /* test whether parameter string is too long */
  if (parm_length > MAX_STRING)
     printf("This exceeds the maximum length of %d\n", MAX_STRING);

  /* if the string parameter has a special value, use it */
  if (strcmp(parm_string, "5.4.3.2.1.0") == 0)
     strcpy(my_string, parm_string);
  else
     strcpy(my_string, "9.8.7.6.5.4.3.2.1.0");

  printf("counting string is %s\n", my_string);

  /* create a new string by concatenation */
  strcat(my_string, " Blast Off!\n");
  printf("Count down begins -- %s", my_string);

  return 0;
}

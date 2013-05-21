/* Author: Don Smith 
 * This program reads lines terminated by newline from stdin and echos
 * the line to stdout preceded by the "greeting" string.  If the line
 * is longer than a maximum, it is split (possibly more than once) and
 * the individual pieces echoed on different lines.  The program 
 * terminates on EOF.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define MAX_LINE 10  /* sets limit on input line */
#define NEWLINE '\n'
#define GREETING_STRING "Hello "

int main(int argc, char* argv[])
{
  int i;
  int count = 0; /* count of characters and array index */
  int c;
  int echo_data[MAX_LINE];  /* to hold input until echoed */
  char greeting[] = GREETING_STRING; 

  /* process characters from stdin until EOF reached */
  while ((c = getc(stdin)) != EOF)
    {
      echo_data[count] = c;
      count += 1;

      /* check for absence of line ending conditions */
      if ((c != NEWLINE) &&
          (count < MAX_LINE))
continue;  /* get next character from stdin */
      else
{
 /* line ends, echo with greeting to stdout */
         fputs(greeting, stdout);
         for (i = 0; i < count; i++)
             fputc(echo_data[i], stdout);
         
         /* if at size limit and no newline at end */
         if ((count == MAX_LINE) &&
             (c != NEWLINE))
	      fputc(NEWLINE, stdout);
         count = 0; /* reset counter and index */
        }
    } /* end while */
  if (count > 0)
     {
      /* handle case where more characters preceeded EOF without newline*/
      fputs(greeting, stdout);
      for (i = 0; i < count; i++)
          fputc(echo_data[i], stdout);
      fputc(NEWLINE, stdout);
     }
} /* end main */


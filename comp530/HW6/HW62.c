
/*
 * Author: William Hipschman
 * PID: 714228116
 * This program reads characters from stdin and writes them to stdout.
 * It replaces NEWLINES with SPACES
 */

//system libraries
#include <stdio.h>

#define SPACE ' '
#define NEWLINE '\n'


int main(int argc, char *argv[]){

  char c;
  char space = SPACE;

  while((c = getc(stdin)) != EOF){
    if(c == NEWLINE)
      fputc(SPACE, stdout);
    else
      fputc(c, stdout);
  }//end while
}

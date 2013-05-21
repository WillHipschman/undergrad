/*
 * Author: William Hipschman
 * PID: 714228116
 * This program reads characters from stdin and writes them to stdout.
 * It replaces NEWLINES with SPACES
 * If two asterisks are encountered in a row it deposits one carat instead
 * of the two asterisks.
 */

//system libraries
#include <stdio.h>

#define CARAT '^'
#define ASTERISK '*'
#define FALSE 0
#define TRUE 1


int main(int argc, char *argv[])
{
  char c;
  int flag = FALSE;
  while((c = getc(stdin)) != EOF){
    if(flag == TRUE)
      if(c == ASTERISK){
        fputc(CARAT, stdout);
        flag = FALSE;
      }
      else{
        fputc(ASTERISK, stdout);
        fputc(c, stdout);
        flag = FALSE;
      }
    else if(c == ASTERISK){
      flag = TRUE;
      continue;
    }
    else
      fputc(c, stdout);
  }
}//end pipeline_stage3

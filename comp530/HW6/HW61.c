
/*
 * Author: William Hipschman
 * PID: 714228116
 * This program reads characters from stdin and writes them to stdout
 */

//system libraries
#include <stdio.h>


int main(int argc, char *argv[]){
  
  char c;
  while((c = getc(stdin)) != EOF)
    fputc(c, stdout);
}
  


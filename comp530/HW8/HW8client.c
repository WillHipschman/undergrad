/* Author: William Hipschman
 * PID: 714228116
 *
 * A client program that uses the service of a remote shell.
 *
 * This program reads input strings from stdin and sends them to
 * a server which executes commands and
 * returns the command output string back to the client.  The client
 * then puts the string to stdout.
 *
 * The client has two positional parameters: (1) the DNS host name
 * where the server program is running, and (2) the port number of
 * the server's "welcoming" socket.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "Socket.h"
#include "ToUpper.h" /* definitions common to client and server */

#define ERROR -1
#define STRING_END '\0'
#define NORMAL 0
#define NUM_ARGS 3
#define PROMPT ">>"
#define NEWLINE '\n'

void check_return_value(int rc, void *connect_socket);

int main(int argc, char* argv[]){

  int i, c, character, rc;
  int count = 0;

  char line_data[MAX_LINE];

  /* variable to hold socket descriptor */
  Socket connect_socket;

  if (argc < NUM_ARGS){

    printf("No host and port\n");
    return (ERROR);
  }

  /* connect to the server at the specified host and port;
   * blocks the process until the connection is accepted
   * by the server; creates a new data transfer socket.
   */
  connect_socket = Socket_new(argv[1], atoi(argv[2]));
  if (connect_socket < NORMAL){

    printf("Failed to connect to server\n");
    return (ERROR);
  }
  
  fputs(PROMPT, stdout);
  while((c = getc(stdin)) != EOF){
    if(c != NEWLINE){
      
      rc = Socket_putc(c, connect_socket);
    }
    else{
      rc = Socket_putc(NEWLINE, connect_socket);
      
      while((character = Socket_getc(connect_socket)) != STRING_END)
	fputc(character, stdout); 
      fputc(NEWLINE, stdout);
      fputs(PROMPT, stdout);
    }
  }
  rc = Socket_putc(EOF, connect_socket);
}


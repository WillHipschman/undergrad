/* Author: William Hipschman
 * PID: 714228116
 * This program takes a port number as its argument.  It creates
 * a welcoming socket on that port and waits for a client program 
 * to establish a connection.  Once a connection is established
 * it listens for lines of input.  For each of these lines a 
 * process is forked then the line is executed.  The output
 * from the command is redirected to a temp file which is then read
 * and sent back to the client program.  Any errors are sent to the
 * the client program.  The server program terminates when it reads an
 * EOF from the client.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Socket.h"
#include "ToUpper.h" /* definitions shared by client and server */

#define NUM_ARGS 2
#define ERROR -1
#define NORMAL 0
#define STRING_END '\0'
#define NUM_PARMS 50 //this should be less
#define SEPARATOR " \t\r\n"
#define MAX_TMP 100
#define NEWLINE '\n'
#define NEW_LINE "\n"
#define ITOA_CONVENTION 10
#define EXECUTE_ERR "ERROR: The command did not execute."

/* variables to hold socket descriptors */
ServerSocket welcome_socket;
Socket connect_socket;

void shell_service(void);
void parse_input(char line_data[], void *p);
void execute(char *strings[], void *p);
void check_put(int rc, void *p);
void send(char line_data[], void *p);

int main(int argc, char* argv[]){

  bool forever = true;
  if (argc != NUM_ARGS){

    printf("Please enter the listening port number only.");
    return (ERROR);
  }

  /* create a "welcoming" socket at the specified port */
  welcome_socket = ServerSocket_new(atoi(argv[1]));
  if (welcome_socket < NORMAL){

    printf("Failed new server socket\n");
    return (ERROR);
  }
  connect_socket = ServerSocket_accept(welcome_socket);
  if (connect_socket < NORMAL){
    printf("Failed accept on server socket\n");
    exit (ERROR);
  }
  
  shell_service();
}

void  shell_service(void){
  
  int i = 0, c, character, rc, no_error;
  //MAX_LINE is the longest the stdin buffer can be, so we won't overflow it
  char line_data[MAX_LINE];
  pid_t cpid, term_pid; /* pid_t is typedef for Linux process ID */
  int chld_status;
  unsigned char new_line[MAX_LINE];
  unsigned char tmp_name[MAX_TMP];
  unsigned char id_str[MAX_TMP];
  char response[MAX_LINE];
  char temp[MAX_LINE];
  int id;

  /* variable names for file "handles" */
  FILE *tmpFP;
  FILE *fp;

  /* get the parent process ID and use it to create a file name for the
   * temporary file with the format "tmpxxxxx" where xxxxx is the ID
   */
  id = (int) getpid();
  sprintf(id_str, "%d", id);
  strcpy(tmp_name,"tmp");
  strcat(tmp_name, id_str);

  /* will not use the server socket */
  Socket_close(welcome_socket);
  
  while((c = Socket_getc(connect_socket)) != EOF){
    
    if(c != NEWLINE){
     
      line_data[i] = c;
      i ++;
    }
    else{
      
      line_data[i] = STRING_END;
      i++;

      //make sure the string is terminated
      if(i == MAX_LINE){
	line_data[MAX_LINE - 1] = STRING_END;
      }
      
      cpid = fork();  /* create child == service process */
      if (cpid == ERROR){
	
      	perror("fork");
	exit (ERROR);
      }
      if (cpid == NORMAL) {/* code for the service process */
	
	/* dynamically redirect stdout to the named temporary
	 * file open for writing
	 */
	fp = freopen(tmp_name, "w", stdout);
	
      	parse_input(line_data, &connect_socket);
      } /* end service process */
      else{
	
	i = 0;
	
	term_pid = waitpid(cpid, &chld_status, 0);
	if (term_pid == ERROR)
	  perror("waitpid");
	else{
	  
	  if (WIFEXITED(chld_status))
	    sprintf(response, "End of input: PID %d exited, status = %d\n", cpid, WEXITSTATUS(chld_status));
	  else
	    sprintf(response, "End of Input: PID %d did not exit normally\n", cpid);
	}
	
	if ((tmpFP = fopen (tmp_name, "r")) == NULL) {
	  
	  fprintf (stderr, "error opening tmp file\n");
	  exit (ERROR);
	}

	no_error = 0;
	while (!feof (tmpFP)) {
	  no_error = 1;
	  /* Get line from file */
	  if (fgets (new_line, sizeof(new_line), tmpFP) == NULL)
            break;
	  send(new_line, &connect_socket);
	}

	
	rc = Socket_putc(NEWLINE, connect_socket);
	check_put(rc, &connect_socket);

	if(no_error)
	  send(response, &connect_socket);
	
	rc = Socket_putc(STRING_END, connect_socket);
	check_put(rc, &connect_socket);

	/* delete the temporary file */
	remove(tmp_name);
	//      } 
      }
    }  
  }
}

void parse_input(char string[], void *p){
  
  char* strings[NUM_PARMS];
  char* token;
  char* temp;
  char temp_char;
  int i = 0;
  int j = 0;
  
  /* initialize arrays */
  for(j = 0; j < NUM_PARMS; j++)
    strings[j] = NULL;
  
  /*tokenize the string*/
  
  token = strtok(string, SEPARATOR);
  
  /*while there are tokens, or while we haven't reached the end of the string*/
  while(token != NULL){
    
    strings[i] = token;
    i ++;
    if ( i == NUM_PARMS){
      //we use NUM_PARMS -1 because the last position needs to be NULL
      printf("ERROR: Please enter less than %d arguments\n", NUM_PARMS - 1);
      //exit the child process
      exit(ERROR);
    }
    //get the next token
    token = strtok(NULL, SEPARATOR);
  }
  
  //branch to the method in charge of execution
  execute(strings, p);
}

void execute(char *strings[], void *p){

  Socket *s = p;
  int rc;

  rc = execvp(strings[0], strings);
  if ( rc == ERROR){

    send(EXECUTE_ERR, s);
    //catch and print errors, exit the child
    perror("execvp");
    exit(ERROR);
  }
}

void check_put(int rc, void *p){

  Socket *s = p;
  Socket connect_socket = *s;
  if (rc == EOF){
    
    printf("Socket_putc EOF or error\n");
    Socket_close(connect_socket);
    exit (ERROR);  /* assume socket problem is fatal*/
  }
}

void send(char line_data[], void *p){

  Socket *s = p;
  Socket connect_socket = *s;
  int i, rc;

  for(i = 0; i < strlen(line_data); i++){
    rc = Socket_putc(line_data[i], connect_socket);
    check_put(rc, &connect_socket);
  }  
}

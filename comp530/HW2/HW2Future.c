//Author: William Hipschman


/* This program emulates shell functionaility.  It forks a new process, parses from stdin to create args and runs them using execvp
 * It runs a command w/ at most NUM_PARMS parameters and commands of no more than LINE_MAX characters.  Error cases are handled by terminating
 * child processes, not the parent process.
/* Definitions */
#define NUM_ARGS 1
#define ERR_RETURN -1
#define NEWLINE '\n'
#define END '\0'
#define TAB '\t'
#define SPACE ' '
#define PROMPT '%'
#define EMPTY ""
#define RETURN '\r'
#define SEPARATOR " \t\r\n"
#define NUM_PARMS 50
//actual maximum line length is LINE_MAX -1 , including the newline, because of the fgets handles its length
#define LINE_MAX 200

/* Includes  */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* Declarations */
void parse_input(char string[]);
void execute(char *strings[]);

int main(int argc, char* argv[]){
  
  //handle error case where too many or too few arguments are entered
  if ( argc != NUM_ARGS){
    printf("ERROR: Program takes %d argument\n", NUM_ARGS);
    exit(ERR_RETURN);
  }
  
  pid_t cpid, term_pid; /* type for Linux process ids */
  int child_status;
  
  fputc(PROMPT, stdout);
  char line[LINE_MAX];
  int count = 0;
  char c;

  while ( fgets(line, LINE_MAX, stdin) != NULL){

    //handle error case where lines are too long
    if(strlen(line) == LINE_MAX - 1){
      //we use LINE_MAX - 2 because the newline counts as a character, and fgets gets the LINE-MAX - 1 next characters
      printf("ERROR: Enter lines no more than %d characters", LINE_MAX - 2);
      line[0] = END;//comment this out
      continue;
    }
    /* create child process, report error if present and exit */
    cpid = fork();
    if ( cpid == ERR_RETURN ){
      
      perror("fork"); //create a description of error codes
      exit(ERR_RETURN);
    }/* end if */
    
    /* conditional execution of parent and child code */
    if ( cpid == 0 ){
      
      parse_input(line);
      exit(0);
    } /* end code executable by child process */
    else {
      
      /* wait for the child to terminate and determine its exit status */
      /*prevents accumulation of "zombie" processes */
      term_pid = waitpid(cpid, &child_status, 0);
      if ( term_pid == ERR_RETURN )
	perror("waitpid");
      else
	if (!WIFEXITED(child_status))
	  printf("Exited Abnormally\n");
    
      //print out new prompt
      fputc('\n', stdout);
      fputc(PROMPT, stdout);
    
    }/* end code executable by parent*/
    //prevents the last iterations' values from being passed to the next iteration
    line[0] = END;
  }/*end while*/
  exit(0);
}/* end main */

void parse_input(char string[]){

  /*initialize variables*/
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
    //assign the strings to an array
    strings[i] = token;
    i ++;
    //handle error cases if they enter too many arguments
    if ( i == NUM_PARMS){
      //we use NUM_PARMS -1 because the last position needs to be NULL
      printf("ERROR: You entered too many arguments.  Please enter less than %d arguments\n", NUM_PARMS - 1);
      //exit the child process
      exit(ERR_RETURN);
    }
    //get the next token
    token = strtok(NULL, SEPARATOR);
  }
  
  //branch to the method in charge of execution
  execute(strings); 
}

void execute(char *strings[]){
    


  int rc;
  //  execute the instruction
  int j = 0;
  int k = 0;
  //  for(j = 0; j <= sizeof(strings); j++)
  //printf("%s\n", strings[j]);

  rc = execvp(strings[0], strings);
  if ( rc == -1){
    
    //catch and print errors, exit the child
    perror("execvp");
    exit(ERR_RETURN);
  }
}

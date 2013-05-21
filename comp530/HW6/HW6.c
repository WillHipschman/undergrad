/*
 * Author: William Hipschman
 * PID: 714228116
 * This program reads input from standard input and copies 80 characters
 * at a time to standard output replacing every carriage return with a space
 * and every adjacent pair of asterisks with a carat.  If no input is entered
 * no output is return.  If the number of characters mod 80 is not 0 then the
 * trailing characters will not be printed.
 *
 * The program does this with multiple processes and uses pipes for interprocess communication.  It processes
 * input in pipeline stages.  The description of each pipeline stage is before its method. 
 */

//system libraries
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <ctype.h>

//definitions
#define SUCC_RETURN 0
#define ERR_RETURN -1
#define SPACE ' '
#define NEWLINE '\n'
#define ASTERISK '*'
#define CARAT '^'
#define NUM_ARGS 1
#define TRUE 1
#define FALSE 0
#define LINE_SIZE 80
#define READ 0
#define WRITE 1


//method declarations
void pipeline_stage1(void);
void pipeline_stage2(void);
void pipeline_stage3(void);
void pipeline_stage4(void);
void print_array(char *array);

//pipexy indicates that the pipe connects child x with child y
int pipe12[2];    // pipe from child1 to child2
int pipe23[2];    // pipe from child2 to child3
int pipe34[2];    // pipe from child3 to child4


//global variables
char array[LINE_SIZE]; //the characters to be printed on a line in the last pipeline stage

/*
 * The main method performs the following functions:
 *    1. Checks that the number of arguments is correct
 *    2. Initializes all pipes
 *    3. Creates threads for each pipeline stage
 *    4. Closes all pipes because the parent thread uses none of them
 *    5. Makes sure all process terminate
 *    6. Exits
 *
 * The pipeline stages are as follows:
 *    1. Input production (reads data from stdin)
 *    2. Input consumption and newline replacement production
 *    3. Newline replacement consumption and output production (replaces asterisk producing buffer data that should be written)
 *    4. Output consumption (writes data)
 */
int main(int argc, char *argv[])
{
  
  pid_t child1_id, child2_id, child3_id, child4_id, term_pid;
  int child_status;

  //create the pipes that connect processes
  if (pipe(pipe12) == ERR_RETURN){
    perror("pipe 1 to 2:");
    exit(EXIT_FAILURE);
  }
 if (pipe(pipe23) == ERR_RETURN){
    perror("pipe 2 to 3:");
    exit(EXIT_FAILURE);
  }
 if (pipe(pipe34) == ERR_RETURN){
    perror("pipe 3 to 4:");
    exit(EXIT_FAILURE);
  }

  //check that parameter count is correct
  if(argc != NUM_ARGS){
    printf("ERROR: Incorrect number of arguments %d.  This program takes %d arguments", argc, NUM_ARGS);
    exit(ERR_RETURN);
  }
  
  // create the first child; it will read input from stdin and place it in the pipe from child 1 to child 2
  child1_id = fork();
  if (child1_id == ERR_RETURN){
    perror("fork for child 1 process:");
    exit(ERR_RETURN);
  }

  if (child1_id == SUCC_RETURN){
    // code executed by child 1
    pipeline_stage1();
  }
  else{
    // code executed by parent
    //create the second child; it will replace newlines with space
    child2_id = fork();
    if (child2_id == ERR_RETURN){
      perror("fork for child 2 process:");
      exit(ERR_RETURN);
    }
    
    if (child2_id == SUCC_RETURN){
      // code executed by child 2
      pipeline_stage2();
    }
    else{
      //code executed by parent
      //create the third child; it will replace pairs of consecutive asterisks with a carat
      child3_id = fork();
      if (child3_id == ERR_RETURN){
	perror("fork for child 3 process:");
	exit(ERR_RETURN);
      }
    
      if (child3_id == SUCC_RETURN){
	//code executed by child 3
	pipeline_stage3();
      }
      else{
	//code executed by parent
	//create the fourth child; it will print lines of output LINE_SIZE characters long
	child4_id = fork();
	if (child4_id == ERR_RETURN){
	  perror("fork for child 4 process:");
	  exit(ERR_RETURN);
	}
	
	if (child4_id == SUCC_RETURN){
	  //code executed by child 4
	  pipeline_stage4();
	}
	else{
	  
	  // wait for the child processes to terminate and determine exit status
	  // this is necessary to prevent the accumulation of "zombie" processes

	  //the parent process doesn't use any of the pipes
	  close(pipe12[READ]);
	  close(pipe12[WRITE]);
	  close(pipe23[READ]);
	  close(pipe23[WRITE]);
	  close(pipe34[READ]);
	  close(pipe34[WRITE]);
	  

	  //make sure all processes end correctly and rejoin the parent
	  term_pid = waitpid(child1_id, &child_status, 0);
	  if (term_pid == ERR_RETURN)
	    perror("waitpid");
	  else
	    if (!WIFEXITED(child_status))
	      printf("PID %d did not exit normally\n", child1_id);
	  
	  term_pid = waitpid(child2_id, &child_status, 0);
	  if (term_pid == ERR_RETURN)
	    perror("waitpid");
	  else
	    if (!WIFEXITED(child_status))
	      printf("PID %d did not exit normally\n", child2_id);
	  
	  
	  term_pid = waitpid(child3_id, &child_status, 0);
	  if (term_pid == ERR_RETURN)
	    perror("waitpid");
	  else
	    if (!WIFEXITED(child_status))
	      printf("PID %d did not exit normally\n", child3_id);
	 
	  term_pid = waitpid(child4_id, &child_status, 0);
	  if (term_pid == ERR_RETURN)
	    perror("waitpid");
	  else
	    if (!WIFEXITED(child_status))
	      printf("PID %d did not exit normally\n", child4_id);
	  
	  exit(SUCC_RETURN);
	}
      }
    }
  }
}

/*
 *This method (child2) deposits characters from stdin into a pipe from child 1 to child 2
 */
void pipeline_stage1(void)
{
  //close unused duplicates of pipe descriptors left after fork
  close(pipe12[READ]); // only write to the pipe between child 1 and 2
  close(pipe23[READ]); // do not use the pipe between child 2 and 3
  close(pipe23[WRITE]);
  close(pipe34[READ]); // do not use the pipe between child 3 and 4
  close(pipe34[WRITE]);

  char c;
  while((c = getc(stdin)) != EOF)
    // for pipe writes, a return of -1 indicates error, otherwise success
    if(write(pipe12[WRITE], &c, 1) == ERR_RETURN){
      perror("Child 1 pipe write: ");
      break;
    }

  close(pipe12[WRITE]); //close on write end gives EOF on read end
}

/*
 * This method (child 2) reads characters from the pipe between child 1 and child 2
 * and deposits them in pipe between child 2 and child 3.  If the character is a newline it deposits a space instead of a newline.
 */
void pipeline_stage2(void)
{
  //close unused duplicates of pipe descriptors left after fork
  close(pipe12[WRITE]);  //only read from the pipe between child 1 and 2
  close(pipe23[READ]);   //only write to the pipe between child 2 and 3
  close(pipe34[READ]);   //do not use the pipe between child 3 and 4
  close(pipe34[WRITE]);

  char child1_data;
  int rc;
  char space = SPACE;

  while((rc = read(pipe12[READ], &child1_data, 1)) > 0){
    // for pipe writes, a return of -1 indicates error, otherwise success
    if(child1_data == NEWLINE){
      if(write(pipe23[WRITE], &space, 1) == ERR_RETURN){
	perror("Child 2 pipe write: ");
	break;
      }
    }
    else
      if(write(pipe23[WRITE], &child1_data, 1) == ERR_RETURN){
	perror("Child 2 pipe write: ");
	break;
      }
  }//end while

  //determine if the while loop ended because of an error or an EOF
  if(rc == ERR_RETURN)
    perror("Child 2 pipe read:");

  close(pipe23[WRITE]); //close on write end gives EOF on read end
}

/*
 * This method (child 3)  reads characters from the pipe between child 2 and 3
 * and deposits them in the pipe between child 3 and 4.  If two asterisks are encountered in a row it deposits one carat instead
 * of the two asterisks.
 */
void pipeline_stage3(void)
{
  //close unused duplicates of pipe descriptors left after fork
  close(pipe12[WRITE]);  //do not use the pipe between child 1 and 2
  close(pipe12[READ]);   
  close(pipe23[WRITE]);  //only read from the pipe between child 2 and 3
  close(pipe34[READ]);  //only write to the pipe between child 3 and 4

  char child2_data;
  int rc;
  int  flag = FALSE;
  char carat = CARAT, asterisk = ASTERISK;

  //-1 indicates error, 0 indicates EOF, and >0 is the number of bytes read
  while((rc = read(pipe23[READ], &child2_data, 1)) > 0){
    // for pipe writes, a return of -1 indicates error, otherwise success
    if(flag == TRUE)
      if(child2_data == ASTERISK){
	if(write(pipe34[WRITE], &carat, 1) == ERR_RETURN){
	  perror("Child 3 pipe write ^: ");
	  break;
	}
	flag = FALSE;
      }
      else{
	if(write(pipe34[WRITE], &asterisk, 1) == ERR_RETURN){
	  perror("Child 3 pipe write *C: ");
	  break;
	}
	if(write(pipe34[WRITE], &child2_data, 1) == ERR_RETURN){
	  perror("Child 3 pipe write: *C");
	  break;
	}
	flag = FALSE;
      }
    else if(child2_data == ASTERISK){
      flag = TRUE;
      continue;
    }
    else
      if(write(pipe34[WRITE], &child2_data, 1) == ERR_RETURN){
	perror("Child 3 pipe write C: ");
	break;
      }
  }

  //determine if the while loop ended because of an error or an EOF
  if(rc == ERR_RETURN)
    perror("Child 3 pipe read:");
  
  //close on write end gives EOF on read end
  close(pipe34[WRITE]);  
}//end pipeline_stage3

/*
 * This method (child 4)  adds the characters from the pipe from child 3 to 4 to an array of LINE_SIZE and prints
 * this array when the number of elements is equal to LINE_SIZE.
 */
void pipeline_stage4(void){

  //close unused duplicates of pipe descriptors left after fork  
  close(pipe12[WRITE]); //do not read or write to the pipe between child 1 and 2
  close(pipe12[READ]);
  close(pipe23[READ]);  //do not read or write to the pipe between child 2 and 3
  close(pipe23[WRITE]);
  close(pipe34[WRITE]);  //only read from the pipe between child 3 and 4
  
  char child3_data;
  int rc;
  int count = 0;
  
  //-1 indicates error, 0 indicates EOF, and >0 is the number of bytes read
  while((rc = read(pipe34[READ], &child3_data, 1)) > 0 ){
    
    array[count] = child3_data;
    if(count == LINE_SIZE - 1){
      print_array(array);
      count = 0;
      continue;
    }
    count++;
  }//end while

  //determine if there was an error or EOF that close the while loop
  if(rc == ERR_RETURN)
    perror("Child 4 pipe read:"); 
  
}//end pipeline_stage4

void print_array(char *array){

  int count = 0;
  while(count < LINE_SIZE){
    fputc(*array, stdout);
    count++;
    array++;
  }//end while

  fputc('\n', stdout);
}//end print_array

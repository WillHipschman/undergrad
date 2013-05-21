#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void foo(void);

int main(int argc, char* argv[]){

  int stack1_ptr;
  int *ptr = malloc(1000 * sizeof(int));
  ptr = ptr + 1000 * sizeof(int);

  printf("main\n");
  
  __asm__ __volatile__("pushl %%ebp;"
		       "movl %%esp, %0;"
		       "movl %1, %%esp;"
		       "movl %%esp, %%ebp;"


		       "pushl %%ebp;"          //begin function call      
		       "subl $4, %%esp;"       //create room for function
 
		       "call foo;"             //call foo
		       
		       "leave;"                 //copies ebp into esp and pops old ebp into ebp

		       "movl %0, %%esp;"
		       "leave;"

		       //need to move back to original Stack
		       
		       :"=r"(stack1_ptr)
		       :"r"(ptr));
  
  /*asm( "pushl   %ebp;"
    "movl    %esp, %ebp;"
    "subl    $4, %esp;"
    
    "call    foo;"
    
    "addl    $4, %esp;"  //this should be resetting the stack pointer in a context switch
    "popl    %ebp;");
  */
  printf("main\n");
}

void foo(void){

  printf("foo\n");
}



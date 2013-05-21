

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void foo(void);

int main(int argc, char* argv[]){
  

  int x = 1, y = 2;

  printf("main x = %d, y = %d\n", x, y);
  
  asm( "pushl   %%ebp;"               //push the pointer to the base of the stack onto the stack
       "movl    %%esp, %%ebp;"        //set the base of the stack equal to the top of the stack           
       "movl    %2, %%ebx;"           //move x into a register
       "movl    %3, %%ecx;"           //move y into a register
       "pushl   %%ebx;"               //push x onto the stack    
       "pushl   %%ecx;"               //push y onto the stack
       "subl    $4, %%esp;"           //decrement the stack pointer for the next method

       "call    foo;"                 //call foo

                                      //foo returns
       
       "addl    $4, %%esp;"           //increment the stack pointer so it is at the value it was at before foo
       "popl    %%ecx;"               //pop y off the stack into a register
       "popl    %%ebx;"               //pop x off the stack into a register
       "popl    %%ebp;"               //pop the pointer to the base of the stack into the base register
       "movl    %%ebx, %0;"           //restore the value of x
       "movl    %%ecx, %1;"           //restore the value of y
       : "=r"(x), "=r"(y)             //read-only output variables
       : "r"(x), "r"(y)               //input variables
       : "%ebx", "%ecx");             //clobbered registers; these can't be used again

  printf("main x = %d, y = %d\n",x, y);

}

void foo(void){

  
  int x = 3, y = 4;
  printf("foo x = %d, y = %d\n", x, y);
  //  exit(1);
     
}



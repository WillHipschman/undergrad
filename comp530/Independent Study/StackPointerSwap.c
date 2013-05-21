

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int main(int argc, char* argv[]){

  int val, val2, val3 ;
  int *ptr =  malloc(1000);
  
  asm ("movl %%esp, %1;"
       "movl %3, %%esp;" 
       "movl %%esp, %0;"
       "movl %1, %%esp;"
       "movl %%esp, %2;"
       :"=r"(val), "=r"(val2), "=r"(val3)        /* output */
       :"r"(ptr)         /* input */
       );  


  printf("The stack pointer was: %d\n", val2);
  printf("Then it was set to   : %d\n", val);
  printf("Then it was reset to : %d\n", val3);
  
}


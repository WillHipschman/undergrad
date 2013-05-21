/*
 * Author: William Hipschman
 * PID: 714228116
 * This method takes characters from stdin and puts them in an array and prints
 * this array when the number of elements is equal to LINE_SIZE.
 */

//system libraries
#include <stdio.h>

#define LINE_SIZE 10

void print_array(char *array);

char array[LINE_SIZE];

int main(int argc, char *argv[]){
  
  int count = 0;
  char c;
  while((c = getc(stdin)) != EOF ){
    
    array[count] = c;
    if(count == LINE_SIZE - 1){
      print_array(array);
      count = 0;
      continue;
    }
    count++;
  }//end whi
}

void print_array(char *array){

  int count = 0;
  while(count < LINE_SIZE){
    fputc(*array, stdout);
    count++;
    array++;
  }//end while

  fputc('\n', stdout);
}//end print_array

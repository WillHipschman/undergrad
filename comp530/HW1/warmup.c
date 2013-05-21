/*
* Author: William Hipschman
* Date: 9/3/2010
* This program reads input from standard input and copies 80 characters
* at a time to standard output replacing every carriage return with a space
* and every adjacent pair of asterisks with a carat.  If no input is entered
* no output is return.  If the number of characters mod 80 is not 0 then the
* trailing characters will not be printed.
*/

/*Libraries*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h> 
#include <string.h>

/*Declarations*/
#define ARRAY_SIZE 80
#define NEWLINE '\n'
#define ASTERISK '*'
#define CARAT '^'
#define SPACE ' '

/*Function Definitions*/
int print(int count, char echo_data[]);

int main(int argc, char* argv[]){

  int i;
  int count = 0; /*Counts the number of characters in the echo_data array and is used to index that array*/
  int c;
  char echo_data[ARRAY_SIZE]; /*Holds the characters to be written to standard out*/
  char temp = 'a'; /*Used to keep track of previous characters in the next iteration of the while loop.  Initialized to 'a' so it doesn't cause null reference problems*/
  
  /*Run the loop until the end of the file is reached
  * If the last character was an asterisk test the
  * current character.  If it is an asterisk add a 
  * carat to the array, otherwise add the asterisk
  * and the new character.  If this character is
  * not an asterisk test if it is a carriage return.
  * if it is then add a space to the array, otherwise
  * add the character to the array.  When count reaches
  * 80 print the array and reset count to zero.
  */
  while ((c = getc(stdin)) != EOF){
    
    /*If the last character was an asterisk*/
    if (temp == ASTERISK){

      /*If this character is an asterisk*/
      if(c == ASTERISK){
	echo_data[count] = CARAT; /*Add a carat to the array*/
	if(print(count, echo_data)){ /*If the array is full, print it and reset the count*/
	    count = 0;
	    /*Set temp to any value != '*' so that it will not rerun the asterisk check.  Temp will be reassigned to a correct value before it is used again*/
	    temp = 'a';
	    continue; /*Continue to next iteration so we can handle the next 80 characters*/
	}/*end if*/
	count++;
	/*Set temp to any value != '*' so that it will not rerun the asterisk check.  Temp will be reassigned to a correct value before it is used again*/
	temp = 'a';
	continue;
      }/*end if*/
      /*If this point is reached than the continue statement above was not executed and so the second character was not an asterisk*/
      /*A lone asterisk was encountered*/
      /*add the asterisk to the array*/
      echo_data[count] = temp;
      /*Print the array if it is full*/
      if(print(count, echo_data))
	count = 0;
      else{
	/*Set temp to any value != '*' so that it will not rerun the asterisk check.  Temp will be reassigned to a correct value before it is used again*/
	temp = 'a';
	/*increment count so that the next character will go into the next slot of the array*/
	count++;
      }/*end else*/
    }/*end if*/

    /*Test the character for exchange conditions*/
    temp = c;
    if (temp == NEWLINE)
      temp = SPACE;
    /*Wait to increment size: continue to next iteration of the loop to check the next character*/
    if (temp == ASTERISK)
      continue;
    /*Add the character to the array*/
    echo_data[count] = temp;
    /*If the array is full print it, set the count to zero, and continue*/
    if (print(count, echo_data)){
	count = 0;
	continue;
	}/*end if*/
    count ++;
  }/*end while*/
}/*end main*/

/*
* Routine to print the array if it is full.  Returns one if the array was full, zero if empty.
*/
int print(int count, char echo_data[]){

  int i;
  if (count == ARRAY_SIZE - 1){ /* the 79th index is the 80th character */
      for (i = 0; i <= count; i++)
	fputc(echo_data[i], stdout);
      fputc('\n', stdout);
      return 1;
  }/*end if*/
  return 0;
}/*end print*/


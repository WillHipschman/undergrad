/* Author: Don Smith
 * This program does nothing useful.  It is intended to provide some
 * examples of using arrays (especially arrays of characters), pointers,
 * and arithmetic on pointers.  An important principle to keep in mind
 * is that in C arrays and pointers are closely related.  In fact, the
 * compiler implements references to array names by pointers and pointer
 * arithmetic.  The C programmer can also use pointers and pointer
 * arithmetic to process arrays by considering the following C rules. 
 *  - an array name is equivalent to a pointer 
 *  - array elements can be referenced with both index subscripts and
 *    pointer arithmetic
 *  - an array is passed implicitly to a function as a pointer
 * Some other things to remember when reading this program:
 *  - strings are arrays of characters terminated by a '\0' 
 *  - pointer variables contain the logical address of other variables
 *    or constants in memory.  Pointer variables are declared with the *
 *    prefix on a variable name (e.g., char *px declares px as a pointer)
 *    Note: the syntax char* px is equivalent and often used.
 *  - pointers can be used in pointer arithmetic expressions
 *  - pointer increment and decrement operations are scaled by the size of
 *    the data type the pointer references.  Pointers are typed, 
 *    i.e., constrained to address a particular data type 
 *    (int, char, float, etc.) and pointer arithmetic on these
 *    pointers have results that depend on the size of the data type
 *    (i.e., if px is a pointer to type char declared as char* px; 
 *    px++; increments px by one but if px is a pointer to type long, 
 *    declared as long* px; px++; increments px by four.)
 *  - the unary (prefix) operator & computes a pointer value (e.g., &x computes the
 *    pointer value that is the logical address of variable x) 
 *  - the unary (prefix) operator * refers to the DATA addressed
 *    by the pointer (this is called "de-referencing") (e.g., *px is a
 *    reference to the data value whose address is in the pointer variable px.
 *        {int foo; int* px; px = &foo; *px = 4;} 
 *    results in variable foo having value 4. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* The following functions to compute a string length all do 
 * the same processing with equivalent ways of referencing the data
 * using array indexing or pointer arithmetic. 
 * 
 * Note: placing the functions called from main() before it in the file
 * avoids the need to have function prototypes to declare the function
 * parameters and results.
 */

/* pass in a as an array name for an array of characters /*
/* use familiar arrary indexing on a character array name */
int str_len_a(char a[])
{
  int i = 0; /* i is both an index and element count */

  while (a[i] != '\0')
     i++;
  return(i);
}

/* pass in a as a pointer variable referencing an array of characters */  
int str_len_b(char *a)
{
  int i = 0; /* i is an element count */

  while (*a != '\0') /* dereference pointer a to get character value */
    {
     a++;  /* increment pointer to next character (+1) */
     i++;
    }
  return(i);
}

/* pass in a as an array name for an array of characters; 
 * in C, this is equivalent to passing a pointer to the array */  
int str_len_c(char a[])
{
  char* p = a; /* make a local copy in the pointer variable p */

  while (*p != '\0') /* dereference pointer a to get character value */
     p++;  /* increment pointer to next character (+1) */

  /* the number of characters in the array is the difference between
   * the last and first pointer values */
  return(p - a); 
}

/* The following functions to compute an array length for an array
 * of integers all do the same processing with differing ways of 
 * referencing the data using array indexing or pointer arithmetic.
 * To highlight the similarities to the string functions above, the 
 * value of 0 is used to mark the end of the array.
 */

/* pass in a as an array name for an array of characters /*
/* use familiar arrary indexing on an integer array name */
int array_len_a(int a[])
{
  int i = 0; /* i is both an index and element count */

  while (a[i] != 0)
     i++;
  return(i);
}
  
/* pass in a as a pointer variable referencing an array of integers */  
int array_len_b(int* a)
{
  int i = 0;  /* i is an element count */

  while (*a != 0) /* dereference pointer a to get integer value */
    {
     a++;  /* increment pointer to next integer (+4) */
     i++;
    }
  return(i);
}
  
/* pass in a as an array name for an array of integers; 
 * in C, this is equivalent to passing a pointer to the array */  
int array_len_c(int a[])
{
  int *p = a;  /* make a local copy in the pointer variable p */

  while (*p != 0)  /* dereference pointer a to get integer value */
     p++;   /* increment pointer to next integer (+4) */

  /* the number of elements in the array is the difference between
   * the last and first pointer values in terms of the data type size */
  return(p - a);
}

/* The main program illustrates use of pointer variables and 
 * differing ways of calling the functions passing an array.
 */

int main(int argc, char* argv[])
{
  /* In this array, the value zero is used as a termination marker */
  /* Note the use of an initializer to implicitly declare the array size */
  int Array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0};

  char Array2[] = "This represents a string with exactly 51 characters";

  int x;   /* an integer variable */
  int* ptr_x;  /* a pointer to variable of type integer */
  
  ptr_x = &x;  /* assign address of x to the pointer variable */

  /* Examples for character arrays (strings) 
   * Each of the above string functions is invoked using both an arrary
   * name and a pointer to pass the argument
   */ 

  fprintf(stdout, "\nExamples for character arrays (strings)\n");

  /* use a pointer dereference for assignment; pass array by name */
  *ptr_x = str_len_a(Array2);  /* assigns return value to x */ 
  fprintf(stdout,"Example 1, the string length is %d\n", x);

  /* use a pointer dereference in fprintf; pass array by computing its address */
  x = str_len_a(&Array2[0]);
  fprintf(stdout,"Example 2, the string length is %d\n", *ptr_x);

  /* pass array by name */
  x = str_len_b(Array2);  
  fprintf(stdout,"Example 3, the string length is %d\n", x);

  /* pass array by pointer */
  x = str_len_b(&Array2[0]);
  fprintf(stdout,"Example 4, the string length is %d\n", *ptr_x);

  /* pass array by name */
  x = str_len_c(Array2);  
  fprintf(stdout,"Example 5, the string length is %d\n", x);

  /* pass array by pointer */
  x = str_len_c(&Array2[0]);
  fprintf(stdout,"Example 6, the string length is %d\n", *ptr_x);

  /* end of examples for character arrarys */

  /* Examples for integer arrays 
   * Each of the above integer functions is invoked using both an arrary
   * name and a pointer to pass the argument
   */ 

  fprintf(stdout, "\nExamples for integer arrays\n");

  /* pass array by name */
  x = array_len_a(Array1);  
  fprintf(stdout,"Example 1, the array length is %d\n", *ptr_x);

  /* pass array by pointer */
  x = array_len_a(&Array1[0]);
  fprintf(stdout,"Example 2, the array length is %d\n", x);

  /* pass array by name */
  x = array_len_b(Array1);  
  fprintf(stdout,"Example 3, the array length is %d\n", *ptr_x);

  /* pass array by pointer */
  x = array_len_b(&Array1[0]);
  fprintf(stdout,"Example 4, the array length is %d\n", x);

  /* pass array by name */
  x = array_len_c(Array1);  
  fprintf(stdout,"Example 5, the array length is %d\n", *ptr_x);

  /* pass array by pointer */
  x = array_len_c(&Array1[0]);
  fprintf(stdout,"Example 6, the array length is %d\n", x);

  return 0;
}

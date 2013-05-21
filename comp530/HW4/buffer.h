/* 
 * Author: William Hipschman
 * PID: 714228116
 * This is the header file for the bounded buffer.
 * This bounded buffer supports two methods: withdraw and deposit.
 */


//size of the buffer
#define SIZE 10

//definition of a BoundedBuffer
typedef struct{

  char array[SIZE];
  int count;
  int nextIn;
  int nextOut;
  semaphore *deposit;
  semaphore *withdraw;

}BoundedBuffer;


/*
 * If b is not full then c is inserted at the end of the buffer.
 * If b is full then the thread running deposit blocks and waits for elements to be consumed.
 */
void deposit(BoundedBuffer *b, char c);

/*
 * If b is not empty then a character is returned from the beginning of the buffer.
 * If b is empty then the thread running withdraw blocks and waits for elements to be produced.
 */
char Remove(BoundedBuffer *b);

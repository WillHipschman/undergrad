#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int main(int argc, char* argv[])
{
  printf("Force Segmentation Fault\n");
  int *ptr;
  ptr = (int *)0;
  *ptr = 1;
}

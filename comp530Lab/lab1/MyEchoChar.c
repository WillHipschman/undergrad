#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int main(int argc, char* argv[]){

      int i;
      int count = 0;
      int c;
      int echo_data[200]; /* warning must be big enough */
      for (i = 0; i < 200; i++){
            c = fgetc(stdin);
            echo_data[i] = c;
            count++;
            if (c == '\n')
                  break;
      }
      fputs("Hello ", stdout);
      for (i = 0; i < count; i++)
            fputc(echo_data[i], stdout);
}

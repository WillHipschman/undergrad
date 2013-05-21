#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define MAX_LINE 10

int main(int argc, char* argv[]){

    int i;
    int count = 0;
    int c;
    int echo_data[MAX_LINE]; /* warning must be big enough */
    while ((c = getc(stdin)) != EOF){

        echo_data[0] = c;
        count = 1;
        if ( c != '\n'){
            
            for (i =1; i < MAX_LINE; i++){
    
                c = fgetc(stdin);
                echo_data[i] = c;
                count++;
                if (c == '\n')
                    break;
            }
        }
    fputs("Hello ", stdout);
    for (i = 0; i < count; i++)
        fputc(echo_data[i], stdout);
    }
}

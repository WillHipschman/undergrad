#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int main(int argc, char* argv[]){

    char echo_data[200]; /* warning must be big enough*/

    fgets(echo_data, sizeof(echo_data), stdin);
    fputs("Hello ", stdout);
    fputs(echo_data, stdout);
    return 0;

}

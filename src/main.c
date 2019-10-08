#include <stdio.h>
#include <stdlib.h>
#include "../headers/criptocao.h"


#define S 10000000 

int main (int argc, char** argv){

    char x = 'A';
    int i = x * 2 *S;
    printf("%c - %c\n", i, i /(2*S));
    return 0;
}

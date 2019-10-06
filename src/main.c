#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"

int main (int argc, char** argv){
    Block* b = blocks_createblock("hello world", 11);

    for(int i=0; i<SIZE; i++){
        for(int j=0;j<SIZE; j++)
            printf("%c ", b->state[i][j]);
        printf("\n");
    }
    return 0;
}
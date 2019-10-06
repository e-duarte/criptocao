#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"

// Tamanho dos blocos são 128 bits
#define SIZE 4

struct block {
    char state[SIZE][SIZE];
    int nbytes;
    struct block* prox;
};


void blocks_initialize(Blockchain* bc, char * src){
    
}
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

typedef struct block Block;

Blockchain* blockchain_create(){
    Blockchain* bc = (Blockchain*) malloc(sizeof(Blockchain));

    if(bc != NULL)
        *bc =  NULL;
    return NULL;
}
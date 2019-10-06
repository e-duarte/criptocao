#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"

// Tamanho dos blocos são 128 bits


void blocks_initialize(Blockchain* bc, char * src){
    
}

Blockchain* blocks_create(){
    Blockchain* bc = (Blockchain*) malloc(sizeof(Blockchain));

    if(bc != NULL)
        *bc =  NULL;
    return NULL;
}

Block* blocks_createblock(char* val, int nb){
    Block* b = (Block*) malloc(sizeof(Block));
    b->nbytes = 0;
    b->prox = NULL;
    char* m = *(b->state);
    for(int i=0; i<nb; i++){
        *m = *val++;
        m++;
    }

    if(nb < SIZE*SIZE){
        for(int i=0; i<SIZE*SIZE-nb; i++){
            *m = '$';
            m++;
        }
            
    }

    return b;
}
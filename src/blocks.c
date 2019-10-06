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


Blockchain* blocks_create(){
    Blockchain* bc = (Blockchain*) malloc(sizeof(Blockchain));

    if(bc != NULL)
        *bc =  NULL;
    return NULL;
}

void blocks_initialize(Blockchain* bc, char * src){
    FILE *plantext = fopen(src, "rb");
    if(plantext == NULL){
        printf("[ERRO] arquivo não encontrado");
        exit(EXIT_FAILURE);
    }

    char buffer[16];
    int nbytes;
    while(nbytes = fread(&buffer, sizeof(char), 16, plantext)){
        Block *block = blocks_createblock(buffer, nbytes);
        Block *aux = (*bc), *ant;
        while(aux != NULL){
            ant = aux;
            aux = aux->prox;
        }

        if(ant ==  NULL)
            *bc = block;
        else
            ant->prox = block;
    }

    fclose(plantext);
}


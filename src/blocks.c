#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"

// Tamanho dos blocos são 128 bits
struct node{
    struct state val;
    struct node* prox;
};

typedef struct node Block;

Blockchain* blocks_create(){
    Blockchain* bc = (Blockchain*) malloc(sizeof(Blockchain));

    if(bc != NULL)
        *bc = NULL;
    return bc;
}

Block* blocks_createblock(char* val, int nb){
    Block* b = (Block*) malloc(sizeof(Block));
    b->val.nbytes = nb;
    b->prox = NULL;
    char* m = *(b->val.state);
    for(int i=0; i<nb; i++){
        *m = *val++;
        m++;
    }
    /*Preenche a matriz de estado com $
     *caso a quantidade de bytes lidos
     * não seja igual ao tamanho do estado.
     */
    if(nb < SIZE*SIZE){
        for(int i=0; i<SIZE*SIZE-nb; i++){
            *m = '$';
            m++;
        }
    }

    return b;
}


void blocks_initialize(Blockchain* bc, char * src){
    if(bc == NULL){
        printf("[ERRO] NULLPOINTER\n");
        exit(EXIT_FAILURE);
    }

    FILE *plaintext = fopen(src, "rb");
    if(plaintext == NULL){
        printf("[ERRO] arquivo não encontrado\n");
        exit(EXIT_FAILURE);
    }

    char buffer[16];
    int nbytes;
    while(nbytes = fread(buffer, sizeof(char), 16, plaintext)){
        Block* block = blocks_createblock(buffer, nbytes);
        Block* aux = *bc, *ant = *bc;
        while(aux != NULL){
            ant = aux;
            aux = aux->prox;
        }
       //Insere no inicio 
        if(ant ==  NULL)
            *bc = block;
        else
            ant->prox = block;
        
    }
    fclose(plaintext);
}

State blocks_nextblock(Blockchain* bc){
    if(bc == NULL){
        printf("[ERRO] NULLPOINTER\n");
        exit(EXIT_FAILURE);
    }
    Block* b = *bc;
    State s = b->val;
    *bc = (*bc)->prox;
    free(b);
    return s;
}

void blocks_print(Blockchain* bc){
    char *val = *((*bc)->val.state);
    while(*bc != NULL){
        for(int i = 0; i < SIZE*SIZE; i++){
            printf("%c ", *val++);
        }
        printf("\n");
        (*bc) = (*bc)->prox;
        val = *((*bc)->val.state);
    }
}


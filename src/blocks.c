#include <stdio.h>
#include <stdlib.h>
#include "../headers/blocks.h"
#include "../headers/util.h"

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
    for(int i=0; i<nb; i++, m++, val++){
        *m = *val;
    }
    /*Preenche a matriz de estado com $
     *caso a quantidade de bytes lidos
     * não seja igual ao tamanho do estado.
     */
    if(nb < SIZE*SIZE){
        for(int i=0; i<SIZE*SIZE-nb; i++, m++){
            *m = '$';
        }
    }

    return b;
}



void blocks_initialize(Blockchain* bc, char * src){
    nullpointer(bc);

    FILE* plaintext = open_file(src, "r");

    char buffer[SIZE*SIZE];
    int nbytes;
    while(nbytes = fread(buffer, sizeof(char), SIZE*SIZE, plaintext)){
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

State* blocks_nextblock(Blockchain* bc){
    nullpointer(bc);
    if(*bc == NULL)
        return NULL;

    Block* b = *bc;
    State* s = (State *)malloc(sizeof(State));
    s->nbytes = b->val.nbytes;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            s->state[i][j] = b->val.state[i][j];
        }
    }
    *bc = b->prox;
    free(b);
    return s;
}

void blocks_print(Blockchain* bc){
    nullpointer(bc);
    nullpointer(*bc);

    Block* aux = *bc;
    while(aux != NULL){
       char* val = *(aux->val.state);
       for(int i = 0; i < SIZE*SIZE; i++)
           printf("%c ", *val++);
       printf("\n");
       aux = aux->prox;
    }
}

void blocks_destroy(Blockchain* bc){
    nullpointer(bc);

    Block* b;
    while(*bc != NULL){
        b = *bc;
        *bc = b->prox;
        free(b); 
    }
    free(bc);
}

/*
State* get(Blockchain* bc, int i){
    Block* aux = *bc;
    int r = 0;
    while(aux != NULL && r != i){
        aux = aux->prox;
        r++;
    }

    if(aux == NULL)
        return NULL;
    return &(aux->val);
}

*/
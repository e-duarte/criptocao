#include <stdio.h>
#include <stdlib.h>
#include "../headers/blocks.h"

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

void nullpointer(void* pointer){
    if(pointer == NULL){
        printf("[ERRO] NULLPOINTER\n");
        exit(EXIT_FAILURE);
    }
}

FILE* open_file(char* src){
    FILE* plaintext = fopen(src, "rb");
    if(plaintext == NULL){
        printf("[ERRO] arquivo não encontrado\n");
        exit(EXIT_FAILURE);
    }
    return plaintext;
}

void blocks_initialize(Blockchain* bc, char * src){
    nullpointer(bc);

    FILE* plaintext = open_file(src);

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

State blocks_nextblock(Blockchain* bc){
    nullpointer(bc);
    nullpointer(*bc);

    Block* b = *bc;
    State s;
    s.nbytes = b->val.nbytes;
    for(int i = 0; i < s.nbytes/4; i++){
        for(int j = 0; j < s.nbytes/4; j++){
            s.state[i][j] = b->val.state[i][j];
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


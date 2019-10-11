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
    Blockchain* bc;

    bc = (Blockchain*) malloc(sizeof(Blockchain));

    if(bc != NULL)
        *bc = NULL;
    return bc;
}

/**@vitor
 * Cria os node blocos.
 **/

Block* blocks_createblock(char* val, int nb){
    Block* b;
    unsigned char* m;
    int i;

    b = (Block*) malloc(sizeof(Block));
    b->val.nbytes = nb;
    b->prox = NULL;
    m = *(b->val.state);

    
    for(i=0; i<nb; i++, m++, val++)
        *m = *val;
    
    /**
     * Preenche a matriz de estado com $
     *caso a quantidade de bytes lidos
     * não seja igual ao tamanho do estado.
     **/
    
    if(nb < SIZE*SIZE){
        for(i=0; i<SIZE*SIZE-nb; i++, m++)
            *m = '$';
    }

    return b;
}



/**@ewerton**/

void blocks_initialize(Blockchain* bc, char * src){
    FILE* plaintext;
    char buffer[SIZE*SIZE];
    int nbytes;

    plaintext = open_file(src, "r");

    nullpointer(bc);
    
    while((nbytes = fread(buffer, sizeof(char), SIZE*SIZE, plaintext))){
        Block* block = blocks_createblock(buffer, nbytes);
        Block* aux = *bc, *ant = *bc;
        while(aux != NULL){
            ant = aux;
            aux = aux->prox;
        }
       /*Insere no inicio*/ 
        if(ant ==  NULL)
            *bc = block;
        else
            ant->prox = block;
        
    }

    fclose(plaintext);
}

State* blocks_nextblock(Blockchain* bc){
    Block* b = *bc;
    State* s = (State *)malloc(sizeof(State));
    int i, j;

    nullpointer(bc);
    if(*bc == NULL)
        return NULL;

    
    s->nbytes = b->val.nbytes;
    for(i= 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            s->state[i][j] = b->val.state[i][j];
        }
    }
    *bc = b->prox;
    free(b);
    return s;
}

void blocks_print(Blockchain* bc){
    Block* aux = *bc;
    int i;

    nullpointer(bc);
    nullpointer(*bc);
    
    while(aux != NULL){
       unsigned char* val = *(aux->val.state);
       for(i = 0; i < SIZE*SIZE; i++)
           printf("%c ", *val++);
       printf("\n");
       aux = aux->prox;
    }
}

void blocks_destroy(Blockchain* bc){
    Block* b;
    
    nullpointer(bc);
    
    while(*bc != NULL){
        b = *bc;
        *bc = b->prox;
        free(b); 
    }
    free(bc);
}


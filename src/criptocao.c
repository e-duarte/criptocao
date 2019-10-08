#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/criptocao.h"

#define LIMIT_I 32
#define LIMIT_S 256
#define SRC_KEY "privat_key.txt"
#define SRC_ENCRIPTY "encripty_file.txt"

int randomInteger (int low, int high){
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    int k = d * (high - low + 1);
    return low + k;
}

char* cripto_generatekey(){
    FILE* key = open_file(SRC_KEY, "w");

    srand(time(NULL));
    for(int i = 0; i < SIZE*SIZE; i++)
        fputc(randomInteger(LIMIT_I, LIMIT_S), key);
        
    fclose(key);
    return SRC_KEY;
}


void troca_linhas(char mat[SIZE][SIZE], int n, int m){
    for(int i = 0; i < 4; i++){
        int aux = mat[n][i];
        mat[n][i] = mat[m][i];
        mat[m][i] = aux;
    }
}


int eliminacao(char mat[SIZE][SIZE], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = i + 1; j < n; j++){
            int aux = j;
            while(mat[i][i] == 0){
                troca_linhas(mat, i,aux);
                aux++;
                if(aux < 4){
                    return 0;
                }
            }

            int m = (mat[j][i] / mat[i][i]);
            mat[j][i] = 0;
            for(int k = i+1; k < n; k++){
                mat[j][k] = mat[j][k] - m*mat[i][k];
            }
        }
    }
    return 1;
}

void copy_matriz(char* mat1, char* mat2){
   
    char *aux1 = mat1, *aux2 = mat2;
    for(int i = 0; i < SIZE*SIZE; i++){
        *aux2 = *aux1;
        aux1++;aux2++;
    }
}


int cripto_determinant(State state){
    char mat2[SIZE][SIZE];
    copy_matriz(*(state.state), *mat2); 
    int val = 1;
    if(eliminacao(mat2, SIZE)){
        for(int i = 0; i < SIZE; i++){
            val *= mat2[i][i];
        }
        return abs(val);
    }
    
    return 0;    
}

void cripto_shitleft(State* state, int det){
    for(int i = 0; i < state->nbytes; i++){
        for(int j = 0; j < state->nbytes; j++){
            state->state[i][j] = state->state[i][j] << det;
        }
    }
}

void cripto_shitright(State* state, int det){
    for(int i = 0; i < state->nbytes; i++){
        for(int j = 0; j < state->nbytes; j++){
            state->state[i][j] = state->state[i][j] >> det;
        }
    }
}

void xordaxuxa(State* s, State* k){
    char* a = *(s->state);
    char* b = *(k->state);
    for(int i=0; i <SIZE*SIZE; i++)
        *a = (*a)^(*b); a++;b++;
}

void add_encryptfile(FILE * f, State* s){
    char* cval = *s->state;
    for(int i = 0; i < s->nbytes; i++){
        printf("%c\n", *cval);
        int ival = *cval++;
        printf("%d\n", ival);
        fputc(ival, f);
    }
}

void cripto_encrypt(char* src){
    Blockchain* msg = blocks_create();
    Blockchain* key = blocks_create();
    blocks_initialize(msg, src);
    blocks_initialize(key, cripto_generatekey());
    State* k = blocks_nextblock(key);
    int det = cripto_determinant(*k) % 256;
    State* s;
    FILE* f = open_file(SRC_ENCRIPTY, "a"); 
    while(s = blocks_nextblock(msg)){
        cripto_shitleft(s, det);
        //xordaxuxa(s, k);
        add_encryptfile(f,s);
    }
    
}

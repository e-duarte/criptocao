#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/criptocao.h"


#define BIT_ML 64
#define BIT_MR 1
#define LIMIT_I 0
#define LIMIT_S 127
#define SRC_KEY "privat_key.txt"
#define SRC_ENCRIPTY "encripty_file.txt"
#define SRC_DECIPHERED "deciphered_file.txt"

int randomInteger (int low, int high){
    double d;
    int k;

    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    
    return low + k;
}

char* cripto_generatekey(){
    FILE* key = open_file(SRC_KEY, "w");
    int i;

    srand(time(NULL));
    for(i = 0; i < SIZE*SIZE; i++)
        fputc(randomInteger(LIMIT_I, LIMIT_S), key);
        
    fclose(key);
    return SRC_KEY;
}


void troca_linhas(unsigned char mat[SIZE][SIZE], int n, int m){
    int i;
    for(i=0; i<4; i++){
        char aux = mat[n][i];
        mat[n][i] = mat[m][i];
        mat[m][i] = aux;
    }
}


int eliminacao(unsigned char mat[SIZE][SIZE], int n){
    int i, j, k, m;
    for(i=0; i<n-1; i++){
        for(j=i+1; j<n; j++){
            int aux = j;
            while(mat[i][i] == 0){
                troca_linhas(mat, i,aux);
                aux++;
                if(aux < SIZE)
                    return 0;
            }
            m = (mat[j][i] / mat[i][i]);
            mat[j][i] = 0;
            for(k=i+1; k<n; k++){
                mat[j][k] = mat[j][k] - m*mat[i][k];
            }
        }
    }
    return 1;
}

void copy_matriz(unsigned char* mat1,unsigned char* mat2){
    int i;
    for(i=0; i <SIZE*SIZE; i++, mat1++, mat2++)
        *mat2 = *mat1;
}


int cripto_determinant(State* state){
    unsigned char mat2[SIZE][SIZE];
    int i, val;
    
    copy_matriz(*(state->state), *mat2); 
    val = 1;
    if(eliminacao(mat2, SIZE)){
        for(i=0; i < SIZE; i++)
            val *= mat2[i][i];
        return abs(val);
    }
    
    return 0;    
}

void cripto_shiftleft(State* state, int det){
    int i, j;
    unsigned char* aux = *(state->state);
    for(i=0; i<SIZE*SIZE; i++, aux++){
        unsigned char byte = *aux;
        for(j=0;j<det; j++){
            if(byte & BIT_ML){
                byte <<= 1;
                byte &= 127;
                byte |= 1;
            }else{
                byte <<= 1;
            }
        }
        *aux = byte;
    }
}

void cripto_shiftright(State* state, int det){
    unsigned char* aux = *(state->state);
    int i, j;

    for(i=0; i<SIZE*SIZE; i++, aux++){
        unsigned char byte = *aux;
        for(j=0; j<det; j++){
            if(byte & BIT_MR){
                byte >>= 1;
                byte |= 64;
            }else byte >>= 1;
        }
        *aux = byte;
    }
}

void xordaxuxa(State* s, State* k){
    unsigned char* a = *(s->state);
    unsigned char* b = *(k->state);
    int i;

    for(i=0; i<SIZE*SIZE; i++, a++, b++)
        *a = (*a) ^ (*b);
}

void add_encryptfile(FILE * f, State* s){
    unsigned char* val = *s->state;
    int i;

    for(i=0; i<s->nbytes; i++)
        fprintf(f, "%c", *val++);
}

void add_decipher(FILE * f, State* s){
    unsigned char* val = *s->state;
    int i;

    for(i=0; i<s->nbytes; i++)
        fprintf(f, "%c", *val++);
}


int normaliza(int det){
    int inter = det % LIMIT_S; /* [0-256] */
    float cast = (float) inter; /* casting para float */
    int n = (int)(cast/LIMIT_S*6); /* normaliza entre 0 e 10 */
    return n;
}

void cripto_encrypt(char* src){
    int det;
    State* s;
    State* k;
    FILE* f;

    Blockchain* msg = blocks_create();
    Blockchain* key = blocks_create();
    blocks_initialize(msg, src);
    blocks_initialize(key, cripto_generatekey());
    
    k = blocks_nextblock(key);
    det =  normaliza(cripto_determinant(k));

    f = open_file(SRC_ENCRIPTY, "w"); 
    while((s = blocks_nextblock(msg))){
        cripto_shiftleft(s, det);
        xordaxuxa(s, k);
        add_encryptfile(f,s);
    }
    
    fclose(f);
}

void cripto_decipher(char* src, char* src_key){
    int det;
    State* s;
    State* k;
    FILE* f;

    Blockchain* msg = blocks_create();
    Blockchain* key = blocks_create();

    blocks_initialize(msg, src);
    blocks_initialize(key, src_key);

    k = blocks_nextblock(key);
    det =  normaliza(cripto_determinant(k));
    f = open_file(SRC_DECIPHERED, "w"); 

    while((s = blocks_nextblock(msg))){
        xordaxuxa(s, k);
        cripto_shiftright(s, det);
        add_decipher(f,s);
    }
    fclose(f);
}
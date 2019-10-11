#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../headers/criptocao.h"
#include "../headers/util.h"

#define BIT_ML 64
#define BIT_MR 1
#define LIMIT_I 0
#define LIMIT_S 127

#define KEY "key.txt"
#define MSG_ENCRIPED "encripted.txt"
#define MSG_DECIPHERED "deciphered.txt"

char* cripto_generatekey(char* src){
    int i;
    char* src_file = str_replace(src, file_name(src), KEY);
    FILE* key = open_file(src_file, "w");
    
    srand(time(NULL));
    for(i=0; i<SIZE*SIZE; i++)
        fputc(randomInteger(LIMIT_I, LIMIT_S), key);
        
    fclose(key);
    return src_file;
}


void troca_linhas(unsigned char mat[SIZE][SIZE], int n, int m){
    int i;
    for(i=0; i<SIZE; i++){
        char aux = mat[n][i];
        mat[n][i] = mat[m][i];
        mat[m][i] = aux;
    }
}


int eliminate(unsigned char mat[SIZE][SIZE], int n){
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
    if(eliminate(mat2, SIZE)){
        for(i=0; i < SIZE; i++)
            val *= mat2[i][i];
        return abs(val);
    }
    
    return 0;    
}

void cripto_rotateshift(State* state, int det){
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

void cripto_rotateright(State* state, int det){
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

void xor(State* s, State* k){
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

void add_decipherfile(FILE * f, State* s){
    unsigned char* val = *s->state;
    int i;

    for(i=0; i<s->nbytes; i++)
        fprintf(f, "%c", *val++);
}

int normaliza(int det){
    int inter = det % LIMIT_S;
    float cast = (float) inter;
    int n = (int)(cast/LIMIT_S*6);
    return n;
}


void cripto_encrypt(char* src_msg){
    char* src_en;
    FILE* f;
    State* k;
    State* s;
    int det;

    Blockchain* msg = blocks_create();
    Blockchain* key = blocks_create();
    char* src_key = cripto_generatekey(src_msg);

    blocks_initialize(msg, src_msg);
    blocks_initialize(key, src_key);
    k = blocks_nextblock(key);
    det =  normaliza(cripto_determinant(k));
    src_en = str_replace(src_msg, file_name(src_msg), MSG_ENCRIPED);
    f = open_file(src_en, "w");

    while((s = blocks_nextblock(msg))){
        cripto_rotateshift(s, det);
        xor(s, k);
        add_encryptfile(f,s);
    }
    
    fclose(f);
}

void cripto_decipher(char* src, char* src_key){
    char* src_en;
    int det;
    State* s, *k;
    FILE* f;

    Blockchain* msg = blocks_create();
    Blockchain* key = blocks_create();

    blocks_initialize(msg, src);
    blocks_initialize(key, src_key);
    k = blocks_nextblock(key);
    det =  normaliza(cripto_determinant(k));
    src_en = str_replace(src, file_name(src), MSG_DECIPHERED);
    f = open_file(src_en, "w"); 

    while((s = blocks_nextblock(msg))){
        xor(s, k);
        cripto_rotateright(s, det);
        add_decipherfile(f,s);
    }
    
    fclose(f);
}
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
    char* src_file = str_replace(src, file_name(src), KEY);
    FILE* key = open_file(src_file, "w");

    srand(time(NULL));
    for(int i = 0; i < SIZE*SIZE; i++)
        fputc(randomInteger(LIMIT_I, LIMIT_S), key);
        
    fclose(key);
    return src_file;
}

void troca_linhas(char mat[SIZE][SIZE], int n, int m){
    for(int i = 0; i < 4; i++){
        char aux = mat[n][i];
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

int cripto_determinant(State* state){
    char mat2[SIZE][SIZE];
    copy_matriz(*(state->state), *mat2); 
    int val = 1;
    if(eliminacao(mat2, SIZE)){
        for(int i = 0; i < SIZE; i++){
            val *= mat2[i][i];
        }
        return abs(val);
    }
    
    return 0;    
}

void cripto_shiftleft(State* state, int det){
    char* aux = *(state->state);
    for(int i = 0; i < SIZE*SIZE; i++, aux++){
        char byte = *aux;
        for(int j = 0; j < det; j++){
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
    char* aux = *(state->state);
    for(int i = 0; i < SIZE*SIZE; i++, aux++){
        char byte = *aux;
        for(int j = 0; j < det; j++){
            if(byte & BIT_MR){
                byte >>= 1;
                byte |= 64;
            }else{
                byte >>= 1;
            }
        }
        *aux = byte;
    }
}

void xordaxuxa(State* s, State* k){
    char* a = *(s->state);
    char* b = *(k->state);
    for(int i=0; i <SIZE*SIZE; i++, a++, b++)
        *a = (*a) ^ (*b);
}

void add_encryptfile(FILE * f, State* s){
    char* val = *s->state;
    for(int i = 0; i < s->nbytes; i++){
        fprintf(f, "%c", *val++);
    }
}

void add_decipher(FILE * f, State* s){
    char* val = *s->state;
    for(int i = 0; i < s->nbytes; i++){
        fprintf(f, "%c", *val++);
    }
}

int normaliza(int det){
    int inter = det % LIMIT_S; // [0-256]
    float cast = (float) inter; // casting para float
    int n = (int)(cast/LIMIT_S*6); // normaliza entre 0 e 10
    return n;
}


void cripto_encrypt(char* src_msg){
    Blockchain* msg = blocks_create();
    Blockchain* key = blocks_create();
    char* src_key = cripto_generatekey(src_msg);
    char* src_en = NULL;
    FILE* f = NULL;
    State* k = NULL;
    State* s = NULL;
    int det = 0;
    

    blocks_initialize(msg, src_msg);
    blocks_initialize(key, src_key);
    k = blocks_nextblock(key);
    det =  normaliza(cripto_determinant(k));
    src_en = str_replace(src_msg, file_name(src_msg), MSG_ENCRIPED);
    f = open_file(src_en, "w");

    while(s = blocks_nextblock(msg)){
        cripto_shiftleft(s, det);
        xordaxuxa(s, k);
        add_encryptfile(f,s);
    }
    
    fclose(f);
}

void cripto_decipher(char* src, char* src_key){
    Blockchain* msg = blocks_create();
    Blockchain* key = blocks_create();
    char* src_en = NULL;
    FILE* f = NULL;
    State* k = NULL;
    State* s = NULL;
    int det = 0;

    blocks_initialize(msg, src);
    blocks_initialize(key, src_key);
    k = blocks_nextblock(key);
    det =  normaliza(cripto_determinant(k));
    src_en = str_replace(src, file_name(src), MSG_DECIPHERED);
    f = open_file(src_en, "w"); 

    while(s = blocks_nextblock(msg)){
        xordaxuxa(s, k);
        cripto_shiftright(s, det);
        add_decipher(f,s);
    }
    
    fclose(f);
    
}
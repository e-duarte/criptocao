#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/criptocao.h"

#define LIMIT_I 32
#define LIMIT_S 256
#define SRC_KEY "privat_key.txt"


int randomInteger (int low, int high){
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    int k = d * (high - low + 1);
    return low + k;
}

char* cripto_generatekey(){
    FILE* key = fopen(SRC_KEY, "w");

    if(key == NULL){
        printf("[ERRO] arquivo não encontrado\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for(int i = 0; i < SIZE*SIZE; i++)
        fputc(randomInteger(LIMIT_I, LIMIT_S), key);
        
    fclose(key);
    return SRC_KEY;
}


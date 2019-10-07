#include <stdio.h>
#include <stdlib.h>
#include "../headers/criptocao.h"

#define LIMIT_I 32
#define LIMIT_S 256
#define SRC_KEY "privat_key.txt"

void cripto_generatekey(){
    FILE* key = fopen(SRC_KEY, "w");

    if(key == NULL){
        printf("[ERRO] arquivo não encontrado\n");
        exit(EXIT_FAILURE);
    }
    char rand_key[SIZE*SIZE];

    srand(time(NULL));
    for(int i = 0; i < SIZE*SIZE; i++){
        rand_key[i] = (ran() % 257) + (244);
    }

    fprintf(key, "%s", rand_key);
    fclose(key);
}




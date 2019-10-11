#include <stdio.h>
#include <stdlib.h>
#include "../headers/criptocao.h"
#include "../headers/util.h"


int main (int argc, char** argv){
    if(argc > 1 ){
        cripto_encrypt(argv[1]);
        cripto_decipher("encripted.txt", "key.txt");
    }else
        printf("[ERRO]: Não é possível executar o algoritmo sem o arquivo!\n");

    return 0;
}

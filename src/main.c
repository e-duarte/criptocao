#include <stdio.h>
#include <stdlib.h>
#include "../headers/criptocao.h"

int main (int argc, char** argv){
    char * key = cripto_generatekey();
    Blockchain* bc_key = blocks_create();
    blocks_initialize(bc_key, key);
    blocks_print(bc_key);

    return 0;
}   
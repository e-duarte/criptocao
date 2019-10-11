#include <stdio.h>
#include <stdlib.h>
#include "../headers/criptocao.h"
#include "../headers/util.h"


int main (int argc, char** argv){
    cripto_encrypt(argv[1]);
    cripto_decipher("../encripted.txt", "../key.txt");

    //char* src = str_replace(argv[1], file_name(argv[1]), "t.txt");
    //printf("%s\n", src);
    return 0;
}

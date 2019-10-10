#include <stdio.h>
#include <stdlib.h>
#include "../headers/criptocao.h"


#define S 10000000 

int main (int argc, char** argv){
/*
    int k = 7;
    char msg = 'A';
    printf("Mensagem: %c\n", msg);
    int c = msg * 2 *S;
    //c = c ^ 7;
    printf("cifrado:%c\n", c);
    //int d = c ^ 7;
    c = c/(2*S);
    printf("decifrado:%c\n", c);
    return 0;
*/
    cripto_encrypt(argv[1]);
    cripto_decipher("encripty_file.txt", "privat_key.txt");
}

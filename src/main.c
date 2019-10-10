#include <stdio.h>
#include <stdlib.h>
#include "../headers/criptocao.h"
#include <locale.h>


#define S 10000000 

int main (int argc, char** argv){
    setlocale(LC_ALL, "Portuguese_Brasil");
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
    
    //Blockchain* msg = blocks_create();
    //blocks_initialize(msg, argv[1]);
    //teste(get(msg, 0));
    //cripto_shiftleft(get(msg, 0), 1);
    //printf("\n");
    //teste(get(msg, 0));
}

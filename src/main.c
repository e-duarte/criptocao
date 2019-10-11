#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/criptocao.h"


int main (int argc, char** argv){
    printf("%d\n", argc);
    if(argc > 1){
        if(!strcmp(argv[1],"-c")){
            if(argc == 3)
                cripto_encrypt(argv[2]);
            else{
                if(argc == 1)
                    printf("[ERRO]FALTA O CAMINHO DO ARQUIVO\n");
                else
                    printf("[ERRO]PARAMETROS INVALIDOS\n");
            }
                
        }else if(!strcmp(argv[1],"-d")){
            if(argc == 4)
                cripto_decipher(argv[2], argv[3]);
            else{
                if(argc == 2)
                    printf("[ERRO]FALTA O CAMINHO DO ARQUIVO\n");
                else
                    printf("[ERRO]PARAMETROS INVALIDOS\n");
            }
        }else
            printf("[ERRO]PARAMETRO INVALIDO\n");
    }else
        printf("[ERRO]NENHUM PARAMETRO INFORMADO\n");

    return 0;
}

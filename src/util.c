#include "../headers/util.h"

FILE* open_file(char* src, char* mode){
    FILE* file = fopen(src, mode);
    if(file == NULL){
        printf("[ERRO] arquivo não encontrado\n");
        exit(EXIT_FAILURE);
    }
    return file;
}


void nullpointer(void* pointer, char* function){
    if(pointer == NULL){
        printf("[ERRO] NULLPOINTER:function:%s\n", function);
        exit(EXIT_FAILURE);
    }
}

int randomInteger (int low, int high){
    double d;
    int k;
    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    return low + k;
}

char* str_replace(char* str, char* sub1, char* sub2){
    int len = strlen(str) + strlen(sub2) + 1;
    char* new = (char*) calloc(len, sizeof(char));
    char* aux1 =  new;
    char* aux2 =  NULL;
    int len_str;
    int i, j, k;

    aux2 = strstr(str, sub1);
    nullpointer(aux2, "str_replace([paramentros]) - bib util.c");
    len_str = strlen(str);
    
    for(i=0; i<len_str; i++){
        if(str == aux2){
            const int len_sub2 = strlen(sub2);
            const int len_sub1 = strlen(sub1);
            for(j=0; j<len_sub2; j++, aux1++, sub2++)
                *aux1 = *sub2;
            
            for(k=0; k<len_sub1; k++)
                str++;
        }else *aux1 = *str;aux1++;str++;
    }
    
    return new;
}

char* file_name(char* src_file){
    int len = strlen(src_file) + 1;
    char* aux1 = NULL;
    char* aux2 = NULL;
    char* new = (char*) calloc(len, sizeof(char));

    aux1 = new;
    aux2 = strrchr(src_file, 47);

    if(aux2 == NULL)
        aux2 = src_file;
    else
        aux2++;
    
    while((*aux1++ = *aux2++));

    return new;
}


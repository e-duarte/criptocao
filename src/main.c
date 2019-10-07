#include <stdio.h>
#include <stdlib.h>
#include "../headers/blocks.h"

int main (int argc, char** argv){
    Blockchain* b = blocks_create();
    blocks_initialize(b, argv[1]);
    blocks_print(b);
    blocks_free(b);
    return 0;
}
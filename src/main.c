#include <stdio.h>
#include <stdlib.h>
#include "../headers/blocks.h"

int main (int argc, char** argv){
    Blockchain* b = blocks_create();
    b = NULL;
    blocks_initialize(b, argv[1]);
    blocks_print(b);
    blocks_destroy(b);
    return 0;
}
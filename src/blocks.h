#define SIZE 4
struct block {
    char state[SIZE][SIZE];
    int nbytes;
    struct block* prox;
};


typedef struct block Block;
typedef Block* Blockchain;

Blockchain* blocks_create();
void blocks_initialize(Blockchain* bc, char * src);
Block* blocks_createblock(char* val, int nb);
void blocks_blockdestroy(Block* block);
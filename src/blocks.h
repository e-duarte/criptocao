typedef struct block *Block;
typedef Block* Blockchain;

Blockchain* blocks_create();
void blocks_initialize(Blockchain* bc, char * src);
Block* blocks_blockcreate(char* val);
void blocks_blockdestroy(Block* block);

typedef Block* Blockchain;

Blockchain* blockchain_create();
void blockchain_initialize(Blockchain* bc, char * src);
Block* block_create(char* val);
void blockchain_blockdestroy(Block* block);
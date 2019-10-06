#define SIZE 4

// Tamanho dos blocos são 128 bits
struct state {
    char state[SIZE][SIZE];
    int nbytes;
};

typedef struct node* Blockchain;

Blockchain* blocks_create();
void blocks_initialize(Blockchain* bc, char * src);
void blocks_print(Blockchain* bc);
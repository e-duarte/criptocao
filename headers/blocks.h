#define SIZE 4

struct state {
    char state[SIZE][SIZE];
    int nbytes;
};

typedef struct node* Blockchain;

Blockchain* blocks_create();
void blocks_initialize(Blockchain* bc, char * src);
void blocks_print(Blockchain* bc);
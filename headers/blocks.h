#define SIZE 4

/**@vitor
 * Tamanho dos blocos são 128 bits
 **/
struct state {
    unsigned char state[SIZE][SIZE];
    int nbytes;
};

typedef struct state State;
typedef struct node* Blockchain;

Blockchain* blocks_create();
void blocks_initialize(Blockchain* bc, char * src);
void blocks_print(Blockchain* bc);
State* blocks_nextblock(Blockchain * bc);
void blocks_destroy(Blockchain* bc);
FILE* open_file(char* src, char* mode);
State* get(Blockchain* bc, int i);
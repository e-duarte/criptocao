#include "../headers/blocks.h"

char* cripto_generatekey();
int cripto_determinant(State state);
void cripto_encrypt(char* src);
void cripto_decipher(char* src, char* src_key);
void cripto_shitleft(State* state, int det);
void cripto_shitright(State* state, int det);
void cripto_addfile(int det);
void nullpointer(void* pointer);

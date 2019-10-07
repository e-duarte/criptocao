#include "../headers/blocks.h"

char* cripto_generatekey();
void cripto_determinant(State state);
void cripto_encrypt(char* src);
void cripto_decipher(char* src, char* src_key);
void cripto_shitleft(int det);
void cripto_shitright(int det);
void cripto_addfile(int det);

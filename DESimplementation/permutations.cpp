#include "permutations.h"

char* permute(char *table, char *perm_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table[(int)perm_table[i]-1];
    }

    return result;
}

char* extractL(char * table) {
    char *result = new char[32];
    
    for (int i = 0; i < 32; i++) {
        result[i] = table[i];
    }
    
    return result;
}

char* extractR(char * table) {
    char *result = new char[32];
    
    for (int i = 32; i < 64; i++) {
        result[i - 32] = table[i];
    }
    
    return result;
}

char* expandR(char * table, char * expand_table) {
    char *result = new char[48];
    
    for(int i = 0; i < 48; i++) {
        result[i]=table[(int)expand_table[i]-1];
    }
    
    return result;
}

char* generateRandomKey(long tabsize) {
    char *result = new char[tabsize];
    
    for(int i = 0; i < tabsize; i++) {
        result[i] = rand() % 2;
    }
    
    return result;
}

char* computeKey(char * key, char * pc_left, char* pc_right, char* pc, int keyshift) {
    char *result = new char[48];
    char *concatLR = new char[56];
    char *left = new char[28];
    char *right = new char[28];
    char *shiftL = new char[28];
    char *shiftR = new char[28];
    
    for (int i = 0; i < 28; i++) {
        left[i] = key[(int)pc_left[i]];
        right[i] = key[(int)pc_right[i]];
    }
    
    for (int i = keyshift; i < (28 - keyshift); i++) {
        shiftL[i - keyshift] = left[i];
        shiftR[i - keyshift] = right[i];
    }
    
    for (int i = 0; i < keyshift; i++) {
        shiftL[28 - keyshift + i] = left[i];
        shiftR[28 - keyshift + i] = right[i];
    }
    
    for (int i = 0; i < 28; i++) {
        concatLR[i] = shiftL[i];
        concatLR[i + 28] = shiftR[i];
    }
    
    for (int i = 0; i < 48; i++) {
        result[i] = concatLR[(int)pc[i] - 1];
    }
    
    return result;
}

char* xorFunction(char *table, char *key, int tabsize) {
    char *result = new char[tabsize];
    
    for (int i = 0; i < tabsize; i++) {
        result[i] = table[i] != key[i];
    }
    
    return result;
}

char* substitutionBox(char * table, char sbox[2][64], char * permut) {
    char *substitue = new char[32];
    char *result = new char[32];
    char *to_binary = new char[4];
    int column, line, index;
    
    for (int i = 0; i < 8; i++) {
        column = table[0 + 6 * i] * 2 + table[5 + 6 * i];
        line = table[1 + 6 * i] * 8 + table[2 + 6 * i] * 4 + table[3 + 6 * i] * 2 + table[4 + 6 * i];
        index = line + column * 16;
        
        to_binary = convertToBinary((int)sbox[i][index]);
        
        substitue[i * 4] = to_binary[0];
        substitue[i * 4 + 1] = to_binary[1];
        substitue[i * 4 + 2] = to_binary[2];
        substitue[i * 4 + 3] = to_binary[3];
    }
    
    for (int i = 0; i < 32; i++) {
        result[i] = substitue[(int)permut[i]-1];
    }
    
    return result;
}

char* convertToBinary(int value) {
    char *result = new char[4];
    int i = 0 , j = 8;
    
    while (value > 0) {
        if (value >= j) {
            value -= j;
            result[i] = 1;
        } else {
            result[i] = 0;
        }
        i++;
        j /= 2;
    }
    
    return result;
}

char* reversePerm(char *L_table, char *R_table, char *perm_table) {
    char *result = new char[64];
    char *table = new char[64];
    
    for (int i = 0; i < 32; i++) {
        table[i] = L_table[i];
        table[i + 32] = R_table[i];
    }
    
    for(int i = 0; i < 64; i++) {
        result[i] = table[(int)perm_table[i] - 1];
    }
    
    return result;
}

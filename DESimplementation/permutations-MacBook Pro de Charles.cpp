#include "permutations.h"

// Make a permutation depeding on a table and the permutation table
char* permute(char *table, char *perm_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table[(int)perm_table[i]-1];
    }

    return result;
}

//Extract the first 32 bits of an array
char* extractL(char * table) {
    char *result = new char[32];
    
    for (int i = 0; i < 32; i++) {
        result[i] = table[i];
    }
    
    return result;
}

//Extract the last 32 bits of an array
char* extractR(char * table) {
    char *result = new char[32];
    
    for (int i = 32; i < 64; i++) {
        result[i - 32] = table[i];
    }
    
    return result;
}

//Use the expandable table to expand the right array
char* expandR(char * table, char * expand_table) {
    char *result = new char[48];
    
    for(int i = 0; i < 48; i++) {
        result[i]=table[(int)expand_table[i]-1];
    }
    
    return result;
}

//Generate a random key
char* generateRandomKey(long tabsize) {
    char *result = new char[tabsize];
    
    for(int i = 0; i < tabsize; i++) {
        result[i] = rand() % 2;
    }
    
    return result;
}

// Compute a subkey
char* computeKey(char * key, char * pc_left, char* pc_right, char* pc, int keyshift) {
    char *result = new char[48];
    char *concatLR = new char[56];
    char *left = new char[28];
    char *right = new char[28];
    char *shiftL = new char[28];
    char *shiftR = new char[28];
    
    for (int i = 0; i < 28; i++) {
        shiftL[i] = 9;
        shiftR[i] = 6;
    }
    
    for (int i = 0; i < 28; i++) {
        left[i] = key[(int)pc_left[i] - 1];
        right[i] = key[(int)pc_right[i] - 1];
    }
    
    for (int i = keyshift; i < 28; i++) {
        shiftL[i - keyshift] = left[i];
        shiftR[i - keyshift] = right[i];
    }
    
    for (int i = 0; i < keyshift; i++) {
        shiftL[28 - keyshift + i] = left[i];
        shiftR[28 - keyshift + i] = right[i];
    }
    
    for (int i = 0; i < 28; i++) {
        if (shiftL[i] > 1) {
             cout << endl << keyshift << endl << i << endl << (int)shiftL[i] << endl << (int)left[i+keyshift] <<endl<<endl;
        }
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

// Do a XOR between two table
char* xorFunction(char *table, char *key, int tabsize) {
    char *result = new char[tabsize];
    
    for (int i = 0; i < tabsize; i++) {
        result[i] = table[i] != key[i];
    }
    
    return result;
}

// Use the substitution box
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

//Convert an integer to a binary
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

// Do the last permutation (the reverse one)
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

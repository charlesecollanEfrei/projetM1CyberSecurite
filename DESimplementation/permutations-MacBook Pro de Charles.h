#ifndef PERMUTATIONS_H_INCLUDED
#define PERMUTATIONS_H_INCLUDED

#include <stdlib.h>

#include <iostream>
#include "bit_tables.h"
using namespace std;

char* permute(char *, char *, long);
char* extractL(char *);
char* extractR(char *);
char* expandR(char *, char *);
char* generateRandomKey(long);
char* computeKey(char *, char *, char*, char*, int);
char* xorFunction(char *, char *, int);
char* substitutionBox(char *, char [2][64], char *);
char* convertToBinary(int);
char* reversePerm(char *, char *, char *);

#endif // PERMUTATIONS_H_INCLUDED

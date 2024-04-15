#include "lists.h"
#ifndef QLIST
#define QLIST
static char FILES[][50] = {
    "./src/questions/skyrim.txt",          "./src/questions/geografia.txt",
    "./src/questions/geografia2.txt",      "./src/questions/Historia.txt",
    "./src/questions/historia_polski.txt", "./src/questions/wiedza_ogolna.txt"};
static const unsigned short AMMOUNT[] = {15, 55, 30, 53, 44, 45};
extern void genQuestions(LIST *, long *);
extern void genQuestion(LIST_ *, long *);
#endif

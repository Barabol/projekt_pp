#include "lists.h"
#ifndef QLIST
#define QLIST
static char FILES[][50] = {"./src/questions/skyrim.txt"};
static const unsigned short AMMOUNT[] = {15};
extern void genQuestions(LIST *, long *);
extern void genQuestion(LIST_ *, long *);
#endif

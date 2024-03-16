#include "lists.h"
#ifndef QLIST
#define QLIST
static char FILES[][50] = {"./src/questions/test.qu",
                           "./src/questions/test2.qu"};
static const unsigned short AMMOUNT[] = {5, 10};
extern void genQuestions(LIST *);
#endif

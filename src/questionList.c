#include "questionList.h"
#include "fileread.h"
#include <stdlib.h>
int is_used(long *toc, int val) {
  if ((*toc) & (1 << val))
    return 1;
  (*toc) = *toc + (1 << val);
  return 0;
}
void genQuestions(LIST *lista, long *toc) {
  int randomI, randomQ;
  int amm = sizeof(AMMOUNT) / sizeof(short);
  // long toc[amm];
  for (int x = 0; x < amm; x++)
    toc[x] = 0;
  for (int x = 0; x < 12; x++) {
    randomI = rand() % amm;
    randomQ = (rand() % AMMOUNT[randomI]) + 1;
    if (is_used(&toc[randomI], randomQ)) {
      x--;
      continue;
    }
    append(lista);
    readQuestion(&(FILES[randomI][0]), value(lista), randomQ);
  }
}
void genQuestion(LIST_ *lista, long *toc) {
  int randomI, randomQ;
  int amm = sizeof(AMMOUNT) / sizeof(short);
  // long toc[amm];
  for (int x = 0; x < 1; x++) {
    randomI = rand() % amm;
    randomQ = (rand() % AMMOUNT[randomI]) + 1;
    if (is_used(&toc[randomI], randomQ)) {
      x--;
      continue;
    }
    readQuestion(&(FILES[randomI][0]), lista, randomQ);
  }
}

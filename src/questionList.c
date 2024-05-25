#include "questionList.h"
#include "fileread.h"
#include <stdlib.h>

/*! \fn int is_used(long *toc, int val)
    \brief Funkcja sprawdzajaca czy 
    \param toc
    \param val
*/
int is_used(long *toc, int val) {
  if ((*toc) & (1 << val))
    return 1;
  (*toc) = *toc + (1 << val);
  return 0;
}

/*! \fn char czemu(char a)
    \brief Szymon nie jest z tego dumny.
    \param a Sprawdzana wartosc.
*/
char czemu(char a) {
  return (a == 1 || a == 2 || a == 3 || a == 4);
} // nie jestem z tego dumny
void genQuestions(LIST *lista, long *toc) {
  int randomI, randomQ;
  char bad = 0;
  int amm = sizeof(AMMOUNT) / sizeof(short);
  for (int x = 0; x < amm; x++)
    toc[x] = 0;
  for (int x = 0; x < 12; x++) {
    randomI = rand() % amm;
    randomQ = (rand() % AMMOUNT[randomI]) + 1;
    if (is_used(&toc[randomI], randomQ)) {
      x--;
      continue;
    }
    if (!bad)
      append(lista);
    readQuestion(&(FILES[randomI][0]), value(lista), randomQ);
    if (!czemu(value(lista)->trueQ) || value(lista)->q1[0] == 0 ||
        value(lista)->q2[0] == 0 || value(lista)->q3[0] == 0 ||
        value(lista)->q4[0] == 0 || value(lista)->question[0] == 0) {
      x--;
      bad = 1;
      continue;
    }
    if (bad)
      bad = 0;
  }
}
void genQuestion(LIST_ *lista, long *toc) {
  int randomI, randomQ;
  int amm = sizeof(AMMOUNT) / sizeof(short);
  for (int x = 0; x < 1; x++) {
    randomI = rand() % amm;
    randomQ = (rand() % AMMOUNT[randomI]) + 1;
    if (is_used(&toc[randomI], randomQ - 1)) {
      x--;
      continue;
    }
    readQuestion(&(FILES[randomI][0]), lista, randomQ);
    if (!czemu(lista->trueQ) || lista->q1[0] == 0 || lista->q2[0] == 0 ||
        lista->q3[0] == 0 || lista->q4[0] == 0 || lista->question[0] == 0) {
      x--;
      continue;
    }
  }
}

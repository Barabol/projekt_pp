#include "fileread.h"
#include "lists.h"
#include "questionList.h"
#include <stdio.h>
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
int main() {
  LIST *lista = new_list();
  append(lista);
  char bad = 0;
  const int amm = sizeof(AMMOUNT) / sizeof(short);
  for (int x = 0; x < amm; x++) {
  }
  for (int x = 0; x < amm; x++) {
    if (AMMOUNT[x] > 64) {
      printf("\x1b[1;31mPLIK: %s posiada ustawione więcej niż 64(max) "
             "pytania\x1b[0m\n",
             FILES[x]);
      break;
    }

    for (int y = 0; y < AMMOUNT[x]; y++) {
      printf("\x1b[1;31mPytanie: \x1b[1;34m%s\x1b[1;31m Index: \x1b[1;34m%d "
             "\x1b[1;31m Status: \x1b[0m",
             FILES[x], y);
      readQuestion(&(FILES[x][0]), value(lista), y + 1);

      printf("\x1b[1;3;32mOK\x1b[0m\n");
      printf("\x1b[1;3;33mQ: \x1b[1;3;100m%s\x1b[0m\n", value(lista)->question);
      printf("\x1b[1;3;33mA: \x1b[1;3;100m%s\x1b[0m\n", value(lista)->q1);
      printf("\x1b[1;3;33mB: \x1b[1;3;100m%s\x1b[0m\n", value(lista)->q2);
      printf("\x1b[1;3;33mC: \x1b[1;3;100m%s\x1b[0m\n", value(lista)->q3);
      printf("\x1b[1;3;33mD: \x1b[1;3;100m%s\x1b[0m\n", value(lista)->q4);
    }
  }
}

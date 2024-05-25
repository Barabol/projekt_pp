#include "ratunki.h"
#include "questionList.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * na pół                  -16 gut
 * zapytaj widownie        -32
 * telefon do przyjaciela  -64
 * zmiana pytania          -128 gut
 */
void ustaw(LIST_ *lista, int index) {
  switch (index) {
  case 0:
    lista->q1[0] = 0;
    return;
  case 1:
    lista->q2[0] = 0;
    return;
  case 2:
    lista->q3[0] = 0;
    return;
  case 3:
    lista->q4[0] = 0;
    return;
  }
}
void make_text(char *widownia_, char *text) {
  sprintf(text, "%d", (int)(*widownia_));
  for (int x = 0; x < 5; x++) {
    if (text[x] == 0) {
      text[x] = '%';
      text[x + 1] = 0;
      break;
    }
  }
}
short na_pol(char *av, LIST_ *lista) {
  if (~(*av) & 16)
    return 0;
  *av -= 16;
  int a = rand() & 3;
  int b = rand() & 3;
  while (a == lista->trueQ - 1)
    a = rand() & 3;
  while (b == lista->trueQ - 1 || b == a)
    b = rand() & 3;
  ustaw(lista, a);
  ustaw(lista, b);
  return 1;
}
short widownia(char *av, LIST_ *lista, char *widzowie) {
  if (~(*av) & 32)
    return 0;
  *av -= 32;
  char sum = 0;
  char holder;
  for (int x = 0; x < 4; x++) {
    widzowie[x] = rand() % 25;
    sum += widzowie[x];
  }
  widzowie[lista->trueQ - 1] += rand() % 22;
  if (sum >= 95) {
    holder = rand() % 5;
    if (widzowie[holder] - 15 < 0)
      widzowie[holder] = 0;
    else
      widzowie[holder] -= 15;
  }
  widzowie[4] = 100 - sum;
  return 1;
}
short tel_przyjaciela(char *av, LIST_ *lista, char *widzowie) {
  if (~(*av) & 64)
    return 0;
  *av -= 64;
  char sum = 0;
  char holder;
  for (int x = 0; x < 4; x++) {
    widzowie[x] = rand() % 25;
    sum += widzowie[x];
  }
  widzowie[lista->trueQ - 1] += rand() % 22;
  if (sum >= 95) {
    holder = rand() % 5;
    if (widzowie[holder] - 15 < 0)
      widzowie[holder] = 0;
    else
      widzowie[holder] -= 15;
  }
  widzowie[4] = 100 - sum;
  widzowie[lista->trueQ - 1] += widzowie[4];

  return 1;
}
short zamiana(char *av, LIST_ *lista, long *toc, unsigned long len) {
  if (~(*av) & 128)
    return 0;
  *av -= 128;
  genQuestion(lista, toc);
  return 1;
}

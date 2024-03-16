#include "fileread.h"
#include "lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
enum status_ { NONE = 0, QUESTION = 1, Q1 = 2, Q2 = 3, Q3 = 4, Q4 = 5 };
void strcopy(const char *a, char *b, const unsigned int padding) {
  int x = 0 + padding;
  for (; x < TABLE_LEN; x++) {
    if (a[x] == '_')
      b[x - padding] = ' ';
    else
      b[x - padding] = a[x];
  }
  b[x + 1 - padding] = 0;
}
void addQ(char index, char *text, const unsigned int is_true, LIST_ *lista) {
  switch (index) {
  case Q1:
    strcopy(text, &(lista->q1[0]), is_true);
    break;
  case Q2:
    strcopy(text, &(lista->q2[0]), is_true);
    break;
  case Q3:
    strcopy(text, &(lista->q3[0]), is_true);
    break;
  case Q4:
    strcopy(text, &(lista->q4[0]), is_true);
    break;
  }
  if (is_true)
    lista->trueQ = index - 1;
}
void randomize(LIST_ *lista) {
  char G[TABLE_LEN];
  char *a1, *a2, *a3;
  a3 = &(G[0]);
  int b;
  int a = rand() & 3;
label:
  b = rand() & 3;
  if (a == b)
    goto label;
  // printf("%d,%d\n", a, b);
  switch (a) {
  case 0:
    a2 = &(lista->q1[0]);
    break;
  case 1:
    a2 = &(lista->q2[0]);
    break;
  case 2:
    a2 = &(lista->q3[0]);
    break;
  case 3:
    a2 = &(lista->q4[0]);
    break;
  }
  switch (b) {
  case 0:
    a1 = &(lista->q1[0]);
    break;
  case 1:
    a1 = &(lista->q2[0]);
    break;
  case 2:
    a1 = &(lista->q3[0]);
    break;
  case 3:
    a1 = &(lista->q4[0]);
    break;
  }
  if (lista->trueQ == a + 1)
    lista->trueQ = b + 1;
  else if (lista->trueQ == b + 1)
    lista->trueQ = a + 1;
  strcpy(a3, a1);
  strcpy(a1, a2);
  strcpy(a2, a3);
}
int readQuestion(char *path, LIST_ *lista, const unsigned int level) {
  FILE *file = fopen(path, "r");
  if (file == NULL)
    return 1;
  char buffor[TABLE_LEN];
  char status = NONE;
  unsigned int index = 0;
  while (!feof(file)) {

    fscanf(file, "%s", buffor);
    if (buffor[0] == '-')
      index++;
    if (index != level)
      continue;
    switch (buffor[0]) {
    case '|':
      status++;
      addQ(status, &buffor[0], 1, lista);
      break;
    case '-':
      status = QUESTION;
      strcopy(&buffor[0], &(lista->question[0]), 1);
      break;
    default:
      status++;
      addQ(status, &buffor[0], 0, lista);
      break;
    }
    if (status == 5)
      break;
  }
  fclose(file);
  randomize(lista);
  return 0;
}

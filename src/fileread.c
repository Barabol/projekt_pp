#include "fileread.h"
#include <stdio.h>
enum status_ { NONE = 0, QUESTION = 1, Q1 = 2, Q2 = 3, Q3 = 4, Q4 = 5 };
void strcopy(const char *a, char *b, const unsigned int padding) {
  for (int x = 0 + padding; x < TABLE_LEN; x++) {
    if (a[x] == '_')
      b[x - padding] = ' ';
    else
      b[x - padding] = a[x];
  }
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
  return 0;
}

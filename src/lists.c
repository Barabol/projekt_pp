#include "lists.h"
#include <stdlib.h>
LIST *new_list() {
  LIST *root = (LIST *)malloc(sizeof(LIST));
  if (root == NULL)
    return NULL;
  root->pointing = NULL;
  return root;
}
int append(LIST *lista) {
  LIST_ *table = (LIST_ *)malloc(sizeof(LIST_));
  if (table == NULL)
    return 1;
  if (lista->pointing == NULL) {
    lista->pointing = table;
    table->next = table;
    return 0;
  }
  table->next = lista->pointing->next;
  lista->pointing->next = table;
  return 0;
}
void next(LIST *lista) {
  if (lista->pointing == NULL)
    return;
  lista->pointing = lista->pointing->next;
}
unsigned int len(LIST *lista) {
  if (lista->pointing == NULL)
    return 0;
  LIST_ *holder = lista->pointing;
  for (unsigned int x = 1;; x++) {
    next(lista);
    if (lista->pointing == holder)
      return x;
  }
}
unsigned int s_len(LIST *lista) {
  if (lista->pointing == NULL)
    return 0;
  if (lista->pointing == lista->pointing->next)
    return 1;
  if (lista->pointing == lista->pointing->next->next)
    return 2;
  return 3;
}
void pop(LIST *lista) {
  if (lista->pointing == NULL)
    return;
  LIST_ *holder = lista->pointing->next;
  switch (len(lista)) {
  case 1:
    free(lista->pointing);
    lista->pointing = NULL;
    return;
  case 2:
    free(holder);
    lista->pointing->next = lista->pointing;
    return;
  }
  LIST_ *holder2 = lista->pointing->next->next;
  free(holder);
  lista->pointing->next = holder2;
  return;
}
void clear(LIST *lista) {
  while (lista->pointing != NULL)
    pop(lista);
}
LIST_ *value(LIST *lista) {
  if (lista->pointing == NULL)
    return NULL;
  if (lista->pointing == lista->pointing->next)
    return lista->pointing;
  return lista->pointing->next;
}

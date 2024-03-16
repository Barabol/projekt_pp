#include "fileread.h"
#include "lists.h"
#include <stdio.h>
void print_list(LIST_ *a) {
  printf("Q: %s\n1: %s\n2: %s\n3: %s\n4: %s\nnumerek: %d\n", a->question, a->q1,
         a->q2, a->q3, a->q4, a->trueQ);
}
int main() {
  LIST *B = new_list();
  append(B);
  // B->pointing->question[0] = 'd';
  for (int x = 1; x < 6; x++) {
    readQuestion("./questions/test.qu", value(B), x);
    print_list(value(B));
  }
}

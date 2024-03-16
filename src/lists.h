#ifndef LISTS
#define LISTS
#define TABLE_LEN 40
typedef struct table_st {
  struct table_st *next;
  char question[TABLE_LEN];
  char q1[TABLE_LEN];
  char q2[TABLE_LEN];
  char q3[TABLE_LEN];
  char q4[TABLE_LEN];
  char trueQ;
} LIST_;
typedef struct table_root {
  struct table_st *pointing;
} LIST;

extern LIST *new_list();
extern int append(LIST *);
extern void next(LIST *);
extern unsigned int len(LIST *);
extern void clear(LIST *);
extern void pop(LIST *);
extern LIST_ *value(LIST *);

extern LIST root_table;

#endif

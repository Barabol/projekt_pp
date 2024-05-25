/*! \file questionList.h
    \brief Plik definiujacy sciezki do plikow z pytaniami oraz deklarujacy
   funkcje do generowania pytan.
*/

#include "lists.h"

/*! \def QLIST */
#ifndef QLIST
#define QLIST

/*! \var static char FILES
    \brief Zmienna przechowujaca sciezki do plikow z pytaniami.
*/
static char FILES[][50] = {
    "./src/questions/skyrim.txt",          "./src/questions/geografia.txt",
    "./src/questions/geografia2.txt",      "./src/questions/Historia.txt",
    "./src/questions/historia_polski.txt", "./src/questions/wiedza_ogolna.txt"};

/*! \var static const unsigned short AMMOUNT
    \brief Zmienna przechowujaca ilosc pytan w odpowiadajacym jej pliku.
    Wartosci odpowiadaja plikom w zmiennej FILES.
*/
static const unsigned short AMMOUNT[] = {15, 55, 30, 53, 44, 45};

/*! \fn extern void genQuestions(LIST *, long *)
    \brief Funkcja generojaca 12 pytan.
    \param LIST *
    \param long *
*/
extern void genQuestions(LIST *, long *);

/*! \fn extern void genQuestion(LIST *, long *)
    \brief Funkcja generojaca pojedyncze pytanie
    \param LIST *
    \param long *
*/
extern void genQuestion(LIST_ *, long *);
#endif

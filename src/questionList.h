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
    \brief Funkcja generojaca 12 pytan i nic nie zwraca.
    \param LIST * wskaznik na liste ktora ma zostac wypelniona.
    \param long * wskaznik na tabele uzytych pytan.
*/
extern void genQuestions(LIST *, long *);

/*! \fn extern void genQuestion(LIST *, long *)
    \brief Funkcja generojaca pojedyncze pytanie i nic nie zwraca.
    \param LIST_ * wskaznik na pytanie do zamiany lub uzupelnienia.
    \param long * wskaznik na tabele uzytych pytan.
*/
extern void genQuestion(LIST_ *, long *);
#endif

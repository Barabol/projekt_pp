/*! \file fileread.h */

#include "lists.h"

/*! \def LISTS
    \brief zapobieganie linkowania podwujnego biblioteki
*/
#ifndef READF
#define READF
/*! \fn extern int readQuestion(char *, LIST_ *, const unsigned int)
    \brief Funkcja odczytujaca pytanie i odpowiedzi z pliku zwraca int.
    \param char * sciezka do pliku z pytaniami.
    \param LIST_ * struktura, do ktorej maja zostac zaladowane dane.
    \param const unsigned int numer pytania
*/
extern int readQuestion(char *, LIST_ *, const unsigned int);
#endif

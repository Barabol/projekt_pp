/*! \file ratunki.h */

#include "lists.h"

/*! \def RATONKI */
#ifndef RATONKI
#define RATONKI

/*! \fn extern short na_pol(char *, LIST_ *)
    \brief Funkcja implementujaca kolo ratunkowe pol na pol
*/
extern short na_pol(char *, LIST_ *);

/*! \fn extern short tel_przyjaciela(char *, LIST_ *, char *)
    \brief Funkcja implementujaca kolo ratunkowe telefon do przyjaciela
*/
extern short tel_przyjaciela(char *, LIST_ *, char *);

/*! \fn extern short widownia(char *, LIST_ *, char *widzowie)
    \brief Funkcja implementujaca kolo ratunkowe pytanie do widowni
*/
extern short widownia(char *, LIST_ *, char *widzowie);

/*! \fn extern short zamiana(char *, LIST_ *, long *, unsigned long)
    \brief Funkcja implementujaca kolo ratunkowe zmiana pytania
*/
extern short zamiana(char *, LIST_ *, long *, unsigned long);

/*! \fn extern void make_text(char *, char *)
    \brief Funkcja zamienajaca liczbe na ciag znakow i dodajaca na koniec znak
   procent.
*/
extern void make_text(char *, char *);
#endif

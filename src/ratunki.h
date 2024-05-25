/*! \file ratunki.h */

#include "lists.h"

/*! \def RATONKI */
#ifndef RATONKI
#define RATONKI

/*! \fn extern short na_pol(char *, LIST_ *)
    \brief Funkcja implementujaca kolo ratunkowe pol na pol zwraca 1 lub 0 w
   zaleznosci czy gracz moze wykonac dzialanie.
   \param char * wskaznik na zmienna z kolami jakie zostaly graczowi.
   \param LIST_ * wskaznik na pytania ktore maja zostac podzielone.
*/
extern short na_pol(char *, LIST_ *);

/*! \fn extern short tel_przyjaciela(char *, LIST_ *, char *)
    \brief Funkcja implementujaca kolo ratunkowe telefon do przyjaciela zwraca 1
   lub 0 w zaleznosci czy gracz moze wykonac dzialanie.
   \param char * wskaznik na zmienna z kolami jakie zostaly graczowi.
   \param LIST_ * wskaznik na pytania ktore maja zostac wybrane przez
   przyjaciela.
   \param char * wskaznik na tabele zawierajaca procenty na dane pytanie.
*/
extern short tel_przyjaciela(char *, LIST_ *, char *);

/*! \fn extern short widownia(char *, LIST_ *, char *widzowie)
    \brief Funkcja implementujaca kolo ratunkowe pytanie do widowni zwraca 1 lub
   0 w zaleznosci czy gracz moze wykonac dzialanie.
   \param char * wskaznik na zmienna z kolami jakie zostaly graczowi.
   \param LIST_ * wskaznik na pytania ktore maja zostac wybrane przez widownie.
   \param char * wskaznik na tabele zawierajaca procenty na dane pytanie.
*/
extern short widownia(char *, LIST_ *, char *);

/*! \fn extern short zamiana(char *, LIST_ *, long *, unsigned long)
    \brief Funkcja implementujaca kolo ratunkowe zmiana pytania zwraca 1 lub
   0 w zaleznosci czy gracz moze wykonac dzialanie.
   \param char * wskaznik na zmienna z kolami jakie zostaly graczowi.
   \param LIST_ * wskaznik na pytania ktore maja zostac zamienione.
   \param long * wskaznik na tabele zawierajaca wykozystane pytania.
   \param unsigned long zmienna ktorej nie usunolem.
*/
extern short zamiana(char *, LIST_ *, long *, unsigned long);

/*! \fn extern void make_text(char *, char *)
    \brief Funkcja zamienajaca liczbe na ciag znakow i dodajaca na koniec znak
   procent nic nie zwraca.
   \param char * wskaznik na liczbe ktora ma byc zamieniona na ciag znakow.
   \param char * wskaznik na ciag znakow ktory ma zostac usupelniony.
   */
extern void make_text(char *, char *);
#endif

/*! \file lists.h
    \brief Plik definiujacy struktury i operacje na nich.
    W pliku mozemy znalezc definicje nowych typow danych
    bedacych strukturami oraz deklaracje funkcji, ktore
    implementuja operacje na danych strukturach.
*/

/*! \def LISTS
    \brief zapobieganie linkowania podwujnego biblioteki
*/
#ifndef LISTS
#define LISTS

/*! \def TABLE_LEN
    \brief Maksymalna dlugosc ciagu znakow zawierajacego pytanie/odpowiedz.
*/
#define TABLE_LEN 75

/*! \typedef LIST_
    \brief Definicja typu bedacego nowa struktura.
*/
/*! \def table_st
    \brief Struktura zawierajaca pytanie wraz z odpowiedziami.
    Struktura zawiera rowniez informacje, ktora odpowiedz jest prawdziwa
    oraz wskaznik na strukture stanowiaca kolejny zestaw wyzej wymienionych
   danych.
*/
typedef struct table_st {
  struct table_st *next;
  char question[TABLE_LEN];
  char q1[TABLE_LEN];
  char q2[TABLE_LEN];
  char q3[TABLE_LEN];
  char q4[TABLE_LEN];
  char trueQ;
} LIST_;

/*! \typedef LIST
    \brief Definicja typu bedacego cyklicznym wskaznikiem na liste.
*/
/*! \def table_st
    \brief Struktura wykorzystujaca poprzedzajaca strukture.
    Umozliwia ona powstanie ciagu struktur typu LIST_.
*/
typedef struct table_root {
  struct table_st *pointing;
} LIST;

/*! \fn extern LIST *new_list()
    \brief Funkcja bezparametrowa tworzaca nowa liste i ja zwraca.
*/
extern LIST *new_list();

/*! \fn extern int append(LIST *)
    \brief Funkcja dodajaca nowa instancje do ciagu struktur zwraca int.
    \param LIST * Wskaznik na ciag struktur, do ktorego chcemy dodac nowa
   strukture.
*/
extern int append(LIST *);

/*! \fn extern void next(LIST *);
    \brief Funkcja przechodzaca do nastepnego elementu ciagu struktur typu nic
   nie zwraca. LIST_.
   \param LIST * Wskaznik na ciag struktur, po ktorym chcemy
   sie poruszyc.
*/
extern void next(LIST *);

/*! \fn extern unsigned int len(LIST *)
    \brief Funkcja sprawdzajaca dlugosc listy i ja zwraca.
    \param LIST * Wskaznik na ciag struktur, ktorego dlugosc chcemy sprawdzic.
*/
extern unsigned int len(LIST *);

/*! \fn extern unsigned int s_len(LIST *)
    \brief Funkcja sprawdzajaca przedzial dlugosci listy i zwraca przedzial
   dlogosci listy.
   \param LIST * Wskaznik na ciag struktur, ktorego dlugosc
   chcemy sprawdzic.
*/
extern unsigned int s_len(LIST *);

/*! \fn extern void clear(LIST *)
    \brief Funkcja czyszczaca liste i nic nie zwraca.
    \param LIST * Wskaznik na ciag struktur, ktory chcemy wyczyscic.
*/
extern void clear(LIST *);

/*! \fn extern void pop(LIST *)
    \brief Funkcja usuwajaca element ciagu struktur typu LIST_ nic nie zwraca.
    \param LIST * Wskaznik na element ciagu struktur, ktory chcemy usunac.
*/
extern void pop(LIST *);

/*! \fn extern LIST_ *value(LIST *)
    \brief odczytywanie wartosci listy.
    \param LIST * Wskaznik na element ciagu struktur,
*/
extern LIST_ *value(LIST *);

/*! \var LIST root_table
    \brief Zezwolenie na wykorzystanie struktury bazowej listy.
*/
extern LIST root_table;

#endif

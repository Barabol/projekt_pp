/*! \file constants.h
    \brief Plik ze stalymi uzywanymi w programie.
*/

/*! \def CONSTANTS
    \brief zapobieganie linkowania podwujnego biblioteki
*/
#ifndef CONSTANTS

#define CONSTANTS
/*! \def WINDOW_W
    \brief Szerokosc okna aplikacji.
*/
#define WINDOW_W 1280

/*! \def WINDOW_H
    \brief Wysokosc okna aplikacji.
*/
#define WINDOW_H 720

/*! \def FONT_SIZE
    \brief Wielkosc czcionki aplikacji.
*/
#define FONT_SIZE 22

/*! \def FRAMES
    \brief Ilosc renderowanych klatek na sekunde.
*/
#define FRAMES 30

/*! \def DEBUG
    \brief
*/
#define DEBUG

/*! \var static const unsigned int ROUNDS
    \brief Kwota wygranej dla danej rundy.
*/
static const unsigned int ROUNDS[12] = {500,    1000,   2000,   5000,
                                        10000,  20000,  40000,  75000,
                                        125000, 250000, 500000, 1000000};

/*! \var static const unsigned int GWARANTOWANE
    \brief Kwota gwarantowanej wygranej dla danej rundy.
*/
static const unsigned int GWARANTOWANE[12] = {
    0, 1000, 1000, 1000, 1000, 1000, 40000, 40000, 40000, 40000, 40000, 40000};

/*! \var static const unsigned int BUTTONS
    \brief Dane na temat polozenia przyciskow z odpowiedziami.
*/
static const unsigned int BUTTONS[4][2] = {
    {20, 290}, {20, 508}, {660, 290}, {660, 508}};

/*! \var static const unsigned int BUTTONS_OFFSET
    \brief Ilość pixeli pomiędzy przyciskami
*/
static const unsigned int BUTTON_OFFSET[2] = {40, 80};

/*! \var static const unsigned int BUTTON_SIZE
    \brief Dane na temat wielkosci przyciskow z odpowiedziami.
*/
static const unsigned int BUTTON_SIZE[2] = {600, 200};

/*! \var static const unsigned int KOLA
    \brief Dane na temat polozenia przyciskow z kolami ratunkowymi.
*/
static const unsigned int KOLA[4][2] = {
    {1200, 20}, {1200, 90}, {1130, 20}, {1130, 90}};
#endif

#ifndef CONSTANTS

#define CONSTANTS
#define WINDOW_W 1280
#define WINDOW_H 720
#define FONT_SIZE 35
#define FRAMES 60
static const unsigned int ROUNDS[12] = {500,    1000,   2000,   5000,
                                        10000,  20000,  40000,  75000,
                                        125000, 250000, 500000, 1000000};
static const unsigned int BUTTONS[4][2] = {
    {0, 190}, {0, 458}, {640, 190}, {640, 458}};
static const unsigned int BUTTON_OFFSET[2] = {20, 90};
static const unsigned int BUTTON_SIZE[2] = {640, 262};
// DODAĆ WSZYSTKIE PLIKI Z PYTANIAMI JAKO KONSTANTY I RANDEM PRZEZ TABELE BY
// MIEĆ LOSOWE PYTANIE JAK I INDEX PYTANIA
#endif

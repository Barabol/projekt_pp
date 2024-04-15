#ifndef CONSTANTS

#define CONSTANTS
#define WINDOW_W 1280
#define WINDOW_H 720
#define FONT_SIZE 22
#define FRAMES 30
#define DEBUG
static const unsigned int ROUNDS[12] = {500,    1000,   2000,   5000,
                                        10000,  20000,  40000,  75000,
                                        125000, 250000, 500000, 1000000};
static const unsigned int GWARANTOWANE[12] = {
    0, 1000, 1000, 1000, 1000, 1000, 40000, 40000, 40000, 40000, 40000, 40000};

static const unsigned int BUTTONS[4][2] = {
    {20, 290}, {20, 508}, {660, 290}, {660, 508}};
static const unsigned int BUTTON_OFFSET[2] = {40, 80};
static const unsigned int BUTTON_SIZE[2] = {600, 200};
static const unsigned int KOLA[4][2] = {
    {1200, 20}, {1200, 90}, {1130, 20}, {1130, 90}};
// DODAĆ WSZYSTKIE PLIKI Z PYTANIAMI JAKO KONSTANTY I RANDEM PRZEZ TABELE BY
// MIEĆ LOSOWE PYTANIE JAK I INDEX PYTANIAMI
#endif

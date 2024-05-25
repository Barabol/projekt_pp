#include "constants.h"
#include "fileread.h"
#include "lists.h"
#include "questionList.h"
#include "ratunki.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <allegro5/timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// a

/*! \fn short goodQuestion(const float x, const float y)
    \brief
    \param x
    \param y
*/
short goodQuestion(const float x, const float y) {
  for (int i = 0; i < 4; i++) {
    if (x >= BUTTONS[i][0] && x <= BUTTONS[i][0] + BUTTON_SIZE[0] &&
        y >= BUTTONS[i][1] && y <= BUTTONS[i][1] + BUTTON_SIZE[1])
      return i;
  }
  for (int i = 0; i < 4; i++) {
    if (x >= KOLA[i][0] && x <= KOLA[i][0] + 66 && y >= KOLA[i][1] &&
        y <= KOLA[i][1] + 66)
      return 4 + i;
  }
  return -1;
}

/*! \fn void draw_messagebox(ALLEGRO_FONT *font[2], ALLEGRO_BITMAP *bg[2], char
   type, char *text, char round, unsigned long seed) \brief Funkcja renderujaca
   message box z informacja o wygranej. \param font Czcionka. \param bg \param
   type Typ message box'a, ktory ma zostac wyswietlony. \param text
   Niewykorzystywana zmienna. \param round Informacja o rundzie. \param seed
   Informacja o seed'dzie. Na podstawie informacji o tym, czy gra wykorzystuje
   custom'owy seed, funkcja poda nowe pytania, lub pytania z danego seed'a.
    Funkcja generuje przyciski z odpowiedziami, kolami ratunkowymi itp., w
   skrocie gre.
*/
void draw_messagebox(ALLEGRO_FONT *font[2], ALLEGRO_BITMAP *bg[2], char type,
                     char *text, char round, unsigned long seed) {
  al_draw_bitmap(bg[0], 0, 0, 0);
  al_draw_bitmap(bg[1], 0, 0, 0);
  const int POZ[][2] = {{437, 108}, {400, 200}, {400, 300}, {400, 400}};
  switch (type) {
  case 1:
    al_draw_text(font[1], al_map_rgb(255, 0, 0), POZ[0][0], POZ[0][1], 0,
                 "KONIEC GRY");
    al_draw_textf(font[0], al_map_rgb(255, 255, 255), POZ[1][0], POZ[1][1], 0,
                  "Zarobki: %dzł", GWARANTOWANE[round - 1]);
    al_draw_textf(font[0], al_map_rgb(255, 255, 255), POZ[2][0], POZ[2][1], 0,
                  "Runda: %d", round);
    al_draw_textf(font[0], al_map_rgb(255, 255, 255), POZ[3][0], POZ[3][1], 0,
                  "Seed: %lx", seed);

    break;
  case 2:
    al_draw_text(font[1], al_map_rgb(0, 255, 0), POZ[0][0], POZ[0][1], 0,
                 "KONIEC GRY");
    al_draw_textf(font[0], al_map_rgb(255, 255, 255), POZ[1][0], POZ[1][1], 0,
                  "Zarobki: %dzł!", ROUNDS[round - 1]);
    al_draw_textf(font[0], al_map_rgb(255, 255, 255), POZ[2][0], POZ[2][1], 0,
                  "Seed: %lx", seed);

    break;
  case 3:
    al_draw_textf(font[1], al_map_rgb(0, 0, 255), POZ[0][0] - 90, POZ[0][1], 0,
                  "KOLEJNA RUNDA #%d", round + 1);
    al_draw_textf(font[0], al_map_rgb(255, 255, 255), POZ[1][0], POZ[1][1], 0,
                  "Obecne zarobki: %dzł", ROUNDS[round - 1]);
    al_draw_textf(font[0], al_map_rgb(255, 255, 255), POZ[2][0], POZ[2][1], 0,
                  "Za tą runde: %dzł", ROUNDS[round]);

    break;
  }
}

/*! \fn char gameloop(time_t seed, const char is_seaded, ALLEGRO_DISPLAY
   *display) \brief Funkcja tworzaca nowe podejscie. \param seed Przechowuje
   informacje o seedzie. \param is_seaded Przechowuje informacje o tym, czy gra
   wykorzystuje custom'owy seed. \param display Okno aplikacji. Na podstawie
   informacji o tym, czy gra wykorzystuje custom'owy seed, funkcja poda nowe
   pytania, lub pytania z danego seed'a. Funkcja generuje przyciski z
   odpowiedziami, kolami ratunkowymi itp., w skrocie gre.
*/
char gameloop(time_t seed, const char is_seaded, ALLEGRO_DISPLAY *display) {
  if (is_seaded)
    srand(seed);
  else
    seed = time(NULL);
  srand(seed);
#ifdef DEBUG
  printf("SEED: %lx\n", seed);
#endif
  char in_game = 1;
  LIST *pytania = new_list();
  long toc[sizeof(AMMOUNT) / sizeof(short)];
  char lst = -1;
  genQuestions(pytania, &toc[0]);
  bool active = true;
  char ratunek = -1;
  unsigned int wait = 0, waiting = 0;
  char widzowie[5] = {0, 0, 0, 0, 0};
  char used_ratunek = 0;
  char widownia_text[5];
  unsigned char textures[4] = {0, 0, 0, 0};
  short quest_ = 0;
  char msgbox[2] = {0, 0};
  char round = 0;
  ALLEGRO_BITMAP *sed = al_load_bitmap("src/img/seed.png");
  ALLEGRO_BITMAP *msg[2] = {al_load_bitmap("src/img/bg.png"),
                            al_load_bitmap("src/img/msg.png")};

  ALLEGRO_BITMAP *background = al_load_bitmap("src/img/background.png");
  ALLEGRO_BITMAP *label = al_load_bitmap("src/img/pixil-frame-0_2.png");
  ALLEGRO_BITMAP *bttn[4] = {al_load_bitmap("src/img/buttons.png"),
                             al_load_bitmap("src/img/button_.png"),
                             al_load_bitmap("src/img/buttonB.png"),
                             al_load_bitmap("src/img/buttonG.png")};
  ALLEGRO_BITMAP *kolaR[4][3] = {
      {al_load_bitmap("src/img/circ_fifty.png"),
       al_load_bitmap("src/img/circ_fifty_dark.png"),
       al_load_bitmap("src/img/circ_fiftyL.png")},
      {al_load_bitmap("src/img/circ_audience.png"),
       al_load_bitmap("src/img/circ_audience_dark.png"),
       al_load_bitmap("src/img/circ_audienceL.png")},
      {al_load_bitmap("src/img/circ_phone.png"),
       al_load_bitmap("src/img/circ_phone_dark.png"),
       al_load_bitmap("src/img/circ_phoneL.png")},
      {al_load_bitmap("src/img/circ_reroll.png"),
       al_load_bitmap("src/img/circ_reroll_dark.png"),
       al_load_bitmap("src/img/circ_rerollL.png")}};

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

  ALLEGRO_TIMER *timer = al_create_timer(1.00 / FRAMES);

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_mouse_event_source());
  ALLEGRO_SAMPLE *sound = NULL;
  ALLEGRO_SAMPLE *button_click =
      al_load_sample("./src/sfx/extra/buttonclick.wav");

  ALLEGRO_SAMPLE_INSTANCE *sound_list = NULL;

  ALLEGRO_SAMPLE_INSTANCE *sounds = al_create_sample_instance(button_click);

  sound = al_load_sample("./src/sfx/sountrack/m1.wav");
  sound_list = al_create_sample_instance(sound);
  al_set_sample_instance_playmode(sound_list, ALLEGRO_PLAYMODE_LOOP);
  al_attach_sample_instance_to_mixer(sound_list, al_get_default_mixer());
  al_attach_sample_instance_to_mixer(sounds, al_get_default_mixer());

  ALLEGRO_EVENT event;
  al_start_timer(timer);

  ALLEGRO_FONT *font =
      al_load_font("src/font/NotoSans-Medium.ttf", FONT_SIZE, 0);
  ALLEGRO_FONT *fontmsg = al_load_font("src/font/NotoSans-Medium.ttf", 62, 0);
  ALLEGRO_FONT *fontholder[2] = {font, fontmsg};
  float MouseY, MouseX;
  float MouseY_, MouseX_;
  al_play_sample_instance(sound_list);
  while (active || waiting || wait) {
    al_wait_for_event(queue, &event);

    switch (event.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      active = false;
      in_game = 0;
      break;
    case ALLEGRO_EVENT_TIMER:
      if (waiting && !msgbox[0]) {
        waiting--;
        if (!waiting) {
          next(pytania);
          for (int x = 0; x < 4; x++)
            textures[x] = 0;
        }
        continue;
      }
      al_clear_to_color(al_map_rgb(255, 255, 255));

      al_draw_bitmap(background, 0, 0, 0);
      al_draw_bitmap(label, 35, 20, 0);
      if (is_seaded)
        al_draw_bitmap(sed, WINDOW_W - 90, WINDOW_H - 90, 0);
      for (int x = 0; x < 4; x++) {
        if (ratunek & 16 << x) {
          if (goodQuestion(MouseX, MouseY) == 4 + x && !used_ratunek) {
            al_draw_bitmap(kolaR[x][2], KOLA[x][0], KOLA[x][1], 0);
            if (x != lst)
              al_play_sample_instance(sounds);
            lst = x;
          } else
            al_draw_bitmap(kolaR[x][0], KOLA[x][0], KOLA[x][1], 0);

        } else
          al_draw_bitmap(kolaR[x][1], KOLA[x][0], KOLA[x][1], 0);
      }
      al_draw_bitmap(bttn[textures[0]], BUTTONS[0][0], BUTTONS[0][1], 0);
      al_draw_bitmap(bttn[textures[1]], BUTTONS[1][0], BUTTONS[1][1], 0);
      al_draw_bitmap(bttn[textures[2]], BUTTONS[2][0], BUTTONS[2][1], 0);
      al_draw_bitmap(bttn[textures[3]], BUTTONS[3][0], BUTTONS[3][1], 0);

      al_draw_text(font, al_map_rgb(255, 255, 255), 50, 95, 0,
                   value(pytania)->question);
      al_draw_text(font, al_map_rgb(255, 255, 255),
                   BUTTONS[0][0] + BUTTON_OFFSET[0],
                   BUTTONS[0][1] + BUTTON_OFFSET[1], 0, value(pytania)->q1);
      al_draw_text(font, al_map_rgb(255, 255, 255),
                   BUTTONS[1][0] + BUTTON_OFFSET[0],
                   BUTTONS[1][1] + BUTTON_OFFSET[1], 0, value(pytania)->q2);
      al_draw_text(font, al_map_rgb(255, 255, 255),
                   BUTTONS[2][0] + BUTTON_OFFSET[0],
                   BUTTONS[2][1] + BUTTON_OFFSET[1], 0, value(pytania)->q3);
      al_draw_text(font, al_map_rgb(255, 255, 255),
                   BUTTONS[3][0] + BUTTON_OFFSET[0],
                   BUTTONS[3][1] + BUTTON_OFFSET[1], 0, value(pytania)->q4);
      if (widzowie[4]) {
        make_text(&widzowie[0], &widownia_text[0]);
        al_draw_text(font, al_map_rgb(255, 255, 255), BUTTONS[0][0] + 450,
                     BUTTONS[0][1] + 30, 0, widownia_text);
        make_text(&widzowie[1], &widownia_text[0]);
        al_draw_text(font, al_map_rgb(255, 255, 255), BUTTONS[1][0] + 450,
                     BUTTONS[1][1] + 30, 0, widownia_text);
        make_text(&widzowie[2], &widownia_text[0]);
        al_draw_text(font, al_map_rgb(255, 255, 255), BUTTONS[2][0] + 450,
                     BUTTONS[2][1] + 30, 0, widownia_text);
        make_text(&widzowie[3], &widownia_text[0]);
        al_draw_text(font, al_map_rgb(255, 255, 255), BUTTONS[3][0] + 450,
                     BUTTONS[3][1] + 30, 0, widownia_text);
      }
      if (msgbox[0]) {
        draw_messagebox(fontholder, msg, msgbox[1], "text", round, seed);
        msgbox[0] = 0;
      }
      al_flip_display();
      if (wait) {
        waiting = wait;
        wait = 0;
        continue;
      }
      break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      if (waiting)
        waiting = 1;
      quest_ = goodQuestion(MouseX, MouseY);
#ifdef DEBUG
      printf(">--- (%d) (%d)\n", round, value(pytania)->trueQ);
#endif
      if (quest_ == -1 || (MouseY = MouseY_ && MouseX == MouseX_))
        continue;
      if (quest_ == value(pytania)->trueQ - 1) {
        MouseX_ = MouseX;
        MouseY_ = MouseY;
        textures[value(pytania)->trueQ - 1] = 3;
        wait = FRAMES << 1;
        round++;
        if (round >= 12) {
          msgbox[0] = 2;
          msgbox[1] = 2;
          active = 0;
          wait <<= 1;
        } else {
          msgbox[0] = 3;
          msgbox[1] = 3;
        }
        used_ratunek = 0;
        widzowie[4] = 0;
      } else if (quest_ < 4) {
        switch (quest_) {
        case 0:
          if (value(pytania)->q1[0] == 0)
            continue;
          break;
        case 1:
          if (value(pytania)->q2[0] == 0)
            continue;
          break;
        case 2:
          if (value(pytania)->q3[0] == 0)
            continue;
          break;
        case 3:
          if (value(pytania)->q4[0] == 0)
            continue;
          break;
        }
        textures[quest_] = 2;
        msgbox[0] = 1;
        msgbox[1] = 1;
        wait = FRAMES << 2;
        used_ratunek = 0;
        widzowie[4] = 0;
        active = 0;
      }
      switch (quest_ - 4) {
      case 0:
        if (!used_ratunek)
          if (na_pol(&ratunek, value(pytania)))
            used_ratunek = 1;
        break;
      case 2:
        if (!used_ratunek)
          if (tel_przyjaciela(&ratunek, value(pytania), &widzowie[0]))
            used_ratunek = 1;
        break;
      case 3:
        if (!used_ratunek)
          if (zamiana(&ratunek, value(pytania), &toc[0],
                      sizeof(toc) / sizeof(long)))
            used_ratunek = 1;
        break;
      case 1:
        if (!used_ratunek)
          if (widownia(&ratunek, value(pytania), &widzowie[0]))
            used_ratunek = 1;
        break;
      }
      break;
    case ALLEGRO_EVENT_MOUSE_AXES:
      if (wait || waiting)
        continue;
      MouseX = event.mouse.x;
      MouseY = event.mouse.y;
      quest_ = goodQuestion(MouseX, MouseY);
      for (int x = 0; x < 4; x++)
        if (textures[x] == 1 && x != quest_)
          textures[x] = 0;
      if (textures[quest_] != 1 && quest_ > -1 && quest_ < 4) {
        textures[quest_] = 1;
        al_play_sample_instance(sounds);
      }
      break;
    case 10:

      switch (event.keyboard.keycode) {
      case 59:
        active = false;
        break;
      case 17:
        if (!used_ratunek)
          if (na_pol(&ratunek, value(pytania)))
            used_ratunek = 1;
        break;
      case 5:
        if (!used_ratunek)
          if (tel_przyjaciela(&ratunek, value(pytania), &widzowie[0]))
            used_ratunek = 1;
        break;
      case 23:
        if (!used_ratunek)
          if (zamiana(&ratunek, value(pytania), &toc[0],
                      sizeof(toc) / sizeof(long)))
            used_ratunek = 1;
        break;
      case 18:
        if (!used_ratunek)
          if (widownia(&ratunek, value(pytania), &widzowie[0]))
            used_ratunek = 1;
        break;
      }
      break;
    }
  }
  al_destroy_sample(sound);
  al_destroy_sample(button_click);
  al_destroy_sample_instance(sound_list);
  al_destroy_sample_instance(sounds);
  al_destroy_event_queue(queue);
  for (int x = 0; x < 2; x++)
    al_destroy_bitmap(msg[x]);
  al_destroy_font(font);
  al_destroy_font(fontmsg);

  al_destroy_timer(timer);

  al_destroy_bitmap(background);
  for (int x = 0; x < 4; x++)
    al_destroy_bitmap(bttn[x]);
  al_destroy_bitmap(label);
  for (int x = 0; x < 4; x++)
    for (int y = 0; y < 3; y++)
      al_destroy_bitmap(kolaR[x][y]);
  clear(pytania);
  free(pytania);
  return in_game;
}

/*! \fn char parser(char str[11], unsigned int *index, unsigned int keycode)
    \brief Funkcja sprawdzajaca, czy seed jest prawidlowy
    \param str
    \param index
    \param keycode

*/
char parser(char str[11], unsigned int *index, unsigned int keycode) {
  if (*index < 10 && keycode > 26 && keycode < 37) {
    str[*index] = keycode + 21;
    (*index)++;
    return 1;
  } else if (*index < 10 && keycode < 7) {
    str[*index] = keycode + 64;
    (*index)++;
    return 1;
  } else if (keycode == 63 && (*index) > 0) {
    (*index)--;
    str[*index] = 0;
    return 1;
  }
  return 0;
}

/*! \fn char gamemenu(ALLEGRO_DISPLAY *display, time_t *seed, char *is_seaded)
    \brief Funkcja tworząca menu gry.
    \param display Okno aplikacji.
    \param seed Zapis danego podejscia.
    \param is_seaded Zmienna podajaca informacje, czy gra jest zaseedowana.
    Jesli gra jest zaseedowana, wyrenderowana zostaje dodatkowa ikonka podczas
   tworzenia nowego podejscia.
*/
char gamemenu(ALLEGRO_DISPLAY *display, time_t *seed, char *is_seaded) {
  ALLEGRO_SAMPLE *button_click =
      al_load_sample("./src/sfx/extra/buttonclick.wav");
  ALLEGRO_SAMPLE_INSTANCE *sounds = al_create_sample_instance(button_click);
  al_attach_sample_instance_to_mixer(sounds, al_get_default_mixer());

  ALLEGRO_FONT *font = al_load_font("src/font/NotoSans-Medium.ttf", 62, 0);
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  ALLEGRO_BITMAP *label = al_load_bitmap("src/img/question_label.png");
  ALLEGRO_BITMAP *gradient = al_load_bitmap("src/img/bg.png");
  ALLEGRO_BITMAP *secret = al_load_bitmap("src/img/seedscr.png");

  ALLEGRO_BITMAP *background = al_load_bitmap("src/img/background.png");
  ALLEGRO_BITMAP *button[4] = {al_load_bitmap("src/img/buttons.png"),
                               al_load_bitmap("src/img/button_.png"),
                               al_load_bitmap("src/img/buttonG.png"),
                               al_load_bitmap("src/img/buttonB.png")};

  ALLEGRO_TIMER *timer = al_create_timer(1.00 / FRAMES);

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_mouse_event_source());
  ALLEGRO_EVENT event;
  al_start_timer(timer);
  char active = 1;
  char go_game = 1;
  unsigned char waiting = 0, wait = 0;
  unsigned int index = 0;
  int MENU_BUTTONS[3][3] = {{343, 279, 0}, {343, 500, 0}, {343, 279, 0}};
  char Wseed = 0;
  float x, y;
  char str[11] = "";
  while (active) {
    al_wait_for_event(queue, &event);
    switch (event.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      active = false;
      go_game = 0;
      break;
    case ALLEGRO_EVENT_TIMER:
      if (waiting) {
        waiting--;
        if (!waiting)
          active = 0;
        continue;
      }
      if (wait) {
        waiting = wait;
        wait = 0;
      }
      al_clear_to_color(al_map_rgb(255, 255, 255));
      al_draw_bitmap(background, 0, 0, 0);
      al_draw_bitmap(label, 43, 18, 0);
      for (int i = 0; i < 2; i++)
        al_draw_bitmap(button[MENU_BUTTONS[i][2]], MENU_BUTTONS[i][0],
                       MENU_BUTTONS[i][1], 0);
      al_draw_text(font, al_map_rgb(255, 255, 255), 156, 75, 0, "MILIONERZY");
      al_draw_text(font, al_map_rgb(255, 255, 255), 569, 336, 0, "GRAJ");
      al_draw_text(font, al_map_rgb(255, 255, 255), 547, 555, 0, "WYJDŹ");

      if (Wseed) {
        al_draw_bitmap(gradient, 0, 0, 0);
        al_draw_bitmap(secret, 0, 580, 0);
        al_draw_bitmap(secret, 720, 580, 0);
        al_draw_bitmap(button[MENU_BUTTONS[2][2]], MENU_BUTTONS[2][0],
                       MENU_BUTTONS[2][1], 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), 380, 336, 0, "SEED:");
        al_draw_text(font, al_map_rgb(255, 255, 255), 550, 336, 0, str);
      }
      al_flip_display();
      break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      if (x > MENU_BUTTONS[0][0] && x < MENU_BUTTONS[0][0] + BUTTON_SIZE[0]) {
        if (y > MENU_BUTTONS[0][1] && y < MENU_BUTTONS[0][1] + BUTTON_SIZE[1]) {
          go_game = 1;
          *seed = strtol(str, NULL, 16);
          *is_seaded = 0;
          wait = FRAMES;
          MENU_BUTTONS[0][2] = 2;

        } else if (y > MENU_BUTTONS[1][1] &&
                   y < MENU_BUTTONS[1][1] + BUTTON_SIZE[1]) {
          go_game = 0;
          wait = FRAMES;
          MENU_BUTTONS[1][2] = 3;
        }
      }
      break;
    case ALLEGRO_EVENT_MOUSE_AXES:
      x = event.mouse.x;
      y = event.mouse.y;
      if (wait || waiting)
        continue;
      if (Wseed) {
        MENU_BUTTONS[1][2] = 0;
        MENU_BUTTONS[0][2] = 0;
        continue;
      }
      if (y > MENU_BUTTONS[0][1] && x > MENU_BUTTONS[0][0] &&
          x < MENU_BUTTONS[0][0] + BUTTON_SIZE[0]) {
        if (MENU_BUTTONS[0][2] == 0 &&
            y < MENU_BUTTONS[0][1] + BUTTON_SIZE[1]) {
          if (MENU_BUTTONS[0][2] == 0)
            al_play_sample_instance(sounds);
          MENU_BUTTONS[0][2] = 1;
          MENU_BUTTONS[1][2] = 0;
        } else if (MENU_BUTTONS[1][2] == 0 && y > MENU_BUTTONS[1][1] &&
                   y < MENU_BUTTONS[1][1] + BUTTON_SIZE[1]) {
          if (MENU_BUTTONS[1][2] == 0)
            al_play_sample_instance(sounds);
          MENU_BUTTONS[1][2] = 1;
          MENU_BUTTONS[0][2] = 0;
        }
      } else {
        MENU_BUTTONS[1][2] = 0;
        MENU_BUTTONS[0][2] = 0;
      }

      break;
    case 10:
      switch (event.keyboard.keycode) {
      case 19:
        Wseed = 1;
        break;
      case 59:
        if (Wseed) {
          Wseed = 0;
          break;
        }
        active = false;
        go_game = 0;
        break;
      case 67:
        if (Wseed) {
          go_game = 1;
          wait = FRAMES;
          MENU_BUTTONS[2][2] = 2;
          *seed = strtol(str, NULL, 16);
          *is_seaded = 1;
        }
        break;
      default:
        if (Wseed)
          if (parser(str, &index, event.keyboard.keycode))
            al_play_sample_instance(sounds);
      }
      break;
    }
  }
  al_destroy_bitmap(background);
  al_destroy_bitmap(label);
  al_destroy_bitmap(gradient);
  al_destroy_bitmap(secret);
  for (int v = 0; v < 3; v++)
    al_destroy_bitmap(button[v]);
  al_destroy_sample(button_click);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  al_destroy_font(font);
  al_destroy_sample_instance(sounds);
  return go_game;
}
int main() {
  al_init();
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_image_addon();
  al_install_keyboard();
  al_install_mouse();
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(10);
  ALLEGRO_DISPLAY *display = al_create_display(WINDOW_W, WINDOW_H);
  char in_game = 1;
  time_t seed;
  char is_seaded;
  while (in_game) {
    if (!gamemenu(display, &seed, &is_seaded))
      break;
    in_game = gameloop(seed, is_seaded, display);
  }
  al_destroy_display(display);
  al_uninstall_keyboard();
  al_uninstall_mouse();
  al_uninstall_audio();
}

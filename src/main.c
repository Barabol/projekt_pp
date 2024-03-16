#include "constants.h"
#include "fileread.h"
#include "lists.h"
#include "questionList.h"
#include <allegro5/allegro.h>
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

short goodQuestion(const float x, const float y, const short goodone) {
  const unsigned short GQ[2] = {BUTTONS[goodone - 1][0],
                                BUTTONS[goodone - 1][1]};
  if (x >= GQ[0] && x <= GQ[0] + BUTTON_SIZE[0] && y >= GQ[1] &&
      y <= GQ[1] + BUTTON_SIZE[1])
    return 1;
  return 0;
}
int main() {
  srand(time(NULL));
  LIST *pytania = new_list();
  genQuestions(pytania);
  bool active = true;

  al_init();
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_image_addon();
  al_install_keyboard();
  al_install_mouse();
  al_install_audio();

  ALLEGRO_BITMAP *background = al_load_bitmap("src/img/bg.png");
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

  ALLEGRO_DISPLAY *display = al_create_display(WINDOW_W, WINDOW_H);
  ALLEGRO_TIMER *timer = al_create_timer(1.00 / FRAMES);

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_mouse_event_source());
  ALLEGRO_EVENT event;
  al_start_timer(timer);

  ALLEGRO_FONT *font =
      al_load_font("src/font/NotoSans-Medium.ttf", FONT_SIZE, 0);
  float MouseY, MouseX;
  while (active) {
    al_wait_for_event(queue, &event);

    switch (event.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      active = false;
      break;
    case ALLEGRO_EVENT_TIMER:
      al_clear_to_color(al_map_rgb(255, 255, 255));
      al_draw_bitmap(background, 0, 0, 0);

      al_draw_text(font, al_map_rgb(0, 0, 0), 20, 50, 0,
                   value(pytania)->question);
      al_draw_text(font, al_map_rgb(0, 0, 0), BUTTONS[0][0] + BUTTON_OFFSET[0],
                   BUTTONS[0][1] + BUTTON_OFFSET[1], 0, value(pytania)->q1);
      al_draw_text(font, al_map_rgb(0, 0, 0), BUTTONS[1][0] + BUTTON_OFFSET[0],
                   BUTTONS[1][1] + BUTTON_OFFSET[1], 0, value(pytania)->q2);
      al_draw_text(font, al_map_rgb(0, 0, 0), BUTTONS[2][0] + BUTTON_OFFSET[0],
                   BUTTONS[2][1] + BUTTON_OFFSET[1], 0, value(pytania)->q3);
      al_draw_text(font, al_map_rgb(0, 0, 0), BUTTONS[3][0] + BUTTON_OFFSET[0],
                   BUTTONS[3][1] + BUTTON_OFFSET[1], 0, value(pytania)->q4);
      al_flip_display();
      break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      if (goodQuestion(MouseX, MouseY, value(pytania)->trueQ))
        next(pytania);
      break;
    case ALLEGRO_EVENT_MOUSE_AXES:
      MouseX = event.mouse.x;
      MouseY = event.mouse.y;
      break;
    }
  }
  al_uninstall_keyboard();
  al_uninstall_mouse();
  al_uninstall_audio();
  al_destroy_font(font);
  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_bitmap(background);
}

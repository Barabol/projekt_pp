#include "constants.h"
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
int main() {
  bool active = true;

  al_init();
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_image_addon();
  al_install_keyboard();
  al_install_mouse();
  al_install_audio();

  ALLEGRO_BITMAP *bitmap = al_load_bitmap("src/img/test.jpg");
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  ALLEGRO_DISPLAY *display = al_create_display(WINDOW_W, WINDOW_H);
  ALLEGRO_TIMER *timer = al_create_timer(1.00 / FRAMES);

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_mouse_event_source());
  ALLEGRO_EVENT eavent;

  al_start_timer(timer);

  ALLEGRO_FONT *font =
      al_load_font("src/font/NotoSans-Medium.ttf", FONT_SIZE, 0);
  float x = 0, y = 0;
  while (active) {
    al_wait_for_event(queue, &eavent);

    switch (eavent.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      active = false;
      break;
    case ALLEGRO_EVENT_TIMER:
      al_clear_to_color(al_map_rgb(255, 255, 255));
      al_draw_bitmap(bitmap, x, y, 0);
      al_draw_text(font, al_map_rgb(0, 0, 0), 0, 0, 0, "elo");
      al_flip_display();
      break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      x = 0;
      break;
    case ALLEGRO_EVENT_MOUSE_AXES:
      x = eavent.mouse.x;
      y = eavent.mouse.y;
      break;
    }
  }
  al_uninstall_keyboard();
  al_uninstall_mouse();
  al_uninstall_audio();
  al_destroy_font(font);
  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_bitmap(bitmap);
}

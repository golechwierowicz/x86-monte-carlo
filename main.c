#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>
#include "monte_carlo.h"

#define true 1
#define false 0
#define bool int

const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const unsigned char col = 127;
const int MAX_INT = 1 << 15;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S, KEY_A, KEY_D, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_P, KEY_O, KEY_B, KEY_N, KEY_Q
};

void fillArrayWithRandomNum(int count, float tab[count][2]){
    tab[0][0] = 200;
    tab[0][1] = 200;
    for(int i = 1; i < count; i++){
        tab[i][0] = rand()%SCREEN_W;
        tab[i][1] = rand()%SCREEN_H;
    }
}

void fillCircle(float x, float y, float r, float tab[3]){
    tab[0] = x;
    tab[1] = y;
    tab[2] = r;
}

void fillRect(float x, float y, float x_size, float y_size, float tab[4]){
    tab[0] = x;
    tab[1] = x_size;
    tab[2] = y;
    tab[3] = y_size;
}


int main(int argc, char **argv)
{
   srand(time(NULL));
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   unsigned int randomNumberCount = 10000;
   float movDistance = 4.0;
   int randomDiff = 1000;
   float bouncer_size_x = 30.0;
   float bouncer_size_y = 30.0;
   float bouncer_x = SCREEN_W / 2.0 - bouncer_size_x / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - bouncer_size_y / 2.0;
   float bouncer_circ_x = SCREEN_W / 2.0 - bouncer_size_x / 2.0;
   float bouncer_circ_y = SCREEN_H / 2.0 - bouncer_size_y / 2.0;
   float randomNumber[MAX_INT][2];
   float rectArray[4];
   float circleArray[3];
   float circle_radius = 20.0;
   float monte_carlo_result = 0;
   unsigned char * buffer;
   ALLEGRO_LOCKED_REGION *locked;
   char output[30];
   int pitch;

   bool key[17] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false ,false, false , false};
   bool redraw = true;
   bool doexit = false;
   bool calculate = false;


   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }


   if(!al_init_primitives_addon()){
      fprintf(stderr, "filed to init addons");
      return -1;
   }

 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
 
 
   al_init_font_addon();
   al_init_ttf_addon();    
   al_clear_to_color(al_map_rgb(255, 0, 255));
 
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   al_clear_to_color(al_map_rgb(255,255,255));
 
   al_flip_display();
 
   al_start_timer(timer);
 
   ALLEGRO_FONT *font = al_load_ttf_font("pirulen.ttf",15,0 );
   if(font == NULL){
        fprintf(stderr, "font");
        return -1;
   }

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if(key[KEY_W] && bouncer_y >= movDistance) {
            bouncer_y -= movDistance;
         }
 
         if(key[KEY_S] && bouncer_y <= SCREEN_H - bouncer_size_y - movDistance) {
            bouncer_y += movDistance;
         }
 
         if(key[KEY_A] && bouncer_x >= movDistance) {
            bouncer_x -= movDistance;
         }
 
         if(key[KEY_D] && bouncer_x <= SCREEN_W - bouncer_size_x - movDistance) {
            bouncer_x += movDistance;
         }

         if(key[KEY_UP] && (bouncer_circ_y - circle_radius) >= movDistance) {
            bouncer_circ_y -= movDistance;
         }
 
         if(key[KEY_DOWN] && bouncer_circ_y <= SCREEN_H - circle_radius - movDistance) {
            bouncer_circ_y += movDistance;
         }
 
         if(key[KEY_LEFT] && (bouncer_circ_x - circle_radius) >= movDistance) {
            bouncer_circ_x -= movDistance;
         }
 
         if(key[KEY_RIGHT] && bouncer_circ_x <= SCREEN_W - circle_radius - movDistance) {
            bouncer_circ_x += movDistance;
         }

         if(key[KEY_Z] && circle_radius < SCREEN_H / 2){
            circle_radius += movDistance;
         }
         if(key[KEY_X] && circle_radius > 10.0){
            circle_radius -= movDistance;
         }
         if(key[KEY_C] && bouncer_size_y < SCREEN_H / 2){
            bouncer_size_y += movDistance;
         }
         if(key[KEY_V] && bouncer_size_y > 10.0){
            bouncer_size_y -= movDistance;
         }
         if(key[KEY_B] && bouncer_size_x < SCREEN_W / 2){
            bouncer_size_x += movDistance;
         }
         if(key[KEY_N] && bouncer_size_x > 10.0){
            bouncer_size_x -= movDistance;
         }
         if(key[KEY_O] && randomNumberCount + randomDiff < MAX_INT){
                randomNumberCount+= randomDiff ;
         }
         if(key[KEY_P] && randomNumberCount - randomDiff > 0){
                randomNumberCount-= randomDiff ;
         }

         calculate = key[KEY_Q] ? true : false;
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = true;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;

            case ALLEGRO_KEY_W:
               key[KEY_W] = true;
               break;
 
            case ALLEGRO_KEY_S:
               key[KEY_S] = true;
               break;
 
            case ALLEGRO_KEY_A: 
               key[KEY_A] = true;
               break;
 
            case ALLEGRO_KEY_D:
               key[KEY_D] = true;
               break;

            case ALLEGRO_KEY_Z:
               key[KEY_Z] = true;
               break;

            case ALLEGRO_KEY_X:
               key[KEY_X] = true;
               break;

            case ALLEGRO_KEY_C:
               key[KEY_C] = true;
               break;

            case ALLEGRO_KEY_V:
               key[KEY_V] = true;
               break;

            case ALLEGRO_KEY_P:
                key[KEY_P] = true;
                break;

            case ALLEGRO_KEY_O:
                key[KEY_O] = true;
                break;
            
            case ALLEGRO_KEY_B:
                key[KEY_B] = true;
                break;

            case ALLEGRO_KEY_N:
                key[KEY_N] = true;
                break;
            case ALLEGRO_KEY_Q:
                key[KEY_Q] = true;
                break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;

            case ALLEGRO_KEY_W:
               key[KEY_W] = false;
               break;
 
            case ALLEGRO_KEY_S:
               key[KEY_S] = false;
               break;
 
            case ALLEGRO_KEY_A: 
               key[KEY_A] = false;
               break;
 
            case ALLEGRO_KEY_D:
               key[KEY_D] = false;
               break;

            case ALLEGRO_KEY_Z:
               key[KEY_Z] = false;
               break;

            case ALLEGRO_KEY_X:

               key[KEY_X] = false;
               break;

            case ALLEGRO_KEY_C:
               key[KEY_C] = false;
               break;

            case ALLEGRO_KEY_V:
               key[KEY_V] = false;
               break;
 
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;

            case ALLEGRO_KEY_O:
                key[KEY_O] = false;
                break;

            case ALLEGRO_KEY_P:
                key[KEY_P] = false;
                break;

            case ALLEGRO_KEY_B:
                key[KEY_B] = false;
                break;

            case ALLEGRO_KEY_N:
                key[KEY_N] = false;
                break;
            case ALLEGRO_KEY_Q:
                key[KEY_Q] = false;
                break;
         }
      }
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
         memset(output, 0, sizeof(output));
         fillCircle(bouncer_circ_x, bouncer_circ_y, circle_radius, circleArray);
         fillRect(bouncer_x, bouncer_y, bouncer_size_x, bouncer_size_y, rectArray);
         fillArrayWithRandomNum(randomNumberCount, randomNumber);

         al_clear_to_color(al_map_rgb(255, 255, 255));         
         locked = al_lock_bitmap(al_get_backbuffer(display), ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_READWRITE);
         pitch = locked->pitch;
         buffer = (unsigned char*)locked->data;
          if(calculate){
          monte_carlo_result = monte_carlo(randomNumberCount, 
          randomNumber, 
          rectArray, 
          circleArray, 
          SCREEN_W, 
          SCREEN_H,
          pitch, 
          buffer);
        }

         al_unlock_bitmap(al_get_backbuffer(display));
         //al_put_pixel(randomNumber[0][0], randomNumber[0][1], al_map_rgb(0.0, 0.0, 0.0));
         al_draw_rectangle(bouncer_x, bouncer_y, bouncer_x + bouncer_size_x, bouncer_y + bouncer_size_y, al_map_rgb(col, 0.0, col), 1.0);
         al_draw_circle(bouncer_circ_x, bouncer_circ_y, circle_radius, al_map_rgb(col, 0.0, col), 1.0);
         snprintf(output, 30, "%f\n", monte_carlo_result);
         al_draw_text(font, al_map_rgb(0.0, 0.0, 0.0), SCREEN_W/2, 40.0, ALLEGRO_ALIGN_CENTRE, output);
         al_flip_display();
      }
   }
 
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}

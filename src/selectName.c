#include "objects.h"
#include "prototypes.h"

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,KEY_ENTER
};

int selectName (char Name[], ALLEGRO_DISPLAY *display,  ALLEGRO_FONT *font, CFG *config) {
	const float FPS = 60;
	const int BOUNCER_SIZE = 20;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *CUADRO = NULL;
	ALLEGRO_BITMAP *fondo = NULL;
	float CUADRO_x = config->SCREEN_W / 2.0 - BOUNCER_SIZE*2;
	float CUADRO_y = config->SCREEN_H / 2.0 - BOUNCER_SIZE;
	bool key[5] = { false, false, false, false ,false};
	bool redraw = true;
	bool doexit = false;
	int L1_S=0;
	int L2_S=255;
	int L3_S=255;
	int y=0;
	int L_S=1;

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	CUADRO = al_create_bitmap(4*BOUNCER_SIZE, BOUNCER_SIZE);
	if(!CUADRO) {
		fprintf(stderr, "failed to create CUADRO bitmap!\n");
		al_destroy_timer(timer);
		return -1;
	}

	fondo= al_load_bitmap("./assets/F1.jpg");
	al_convert_mask_to_alpha(fondo, al_map_rgb(0, 0, 0));

	al_set_target_bitmap(CUADRO);
	al_clear_to_color(al_map_rgb(0, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(CUADRO);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0,0,0));

	al_flip_display();
	al_start_timer(timer);

	while(!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			if(key[KEY_UP] && L_S==1 ) {
				Name[y]=Name[y]+1;
					if(Name[y]>90) {
						Name[y]=65;
					}
					L_S=0;
				}

			if(key[KEY_DOWN] && L_S==1) {
				Name[y]=Name[y]-1;
				if(Name[y]<65) {
					Name[y]=90;
				}
				L_S=0;
			}

			if(key[KEY_LEFT] && L_S==1) {
				y--;
				if(y<0) {
					y=2;
				}
				L_S=0;
			}

			if(key[KEY_RIGHT] && L_S==1) {
				y++;
				if(y>2) {
				y=0;
				}
				L_S=0;
			}

			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return -1;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				L_S=1;
				break;

				case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				L_S=1;
				break;

				case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				L_S=1;
				break;

				case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				L_S=1;
				break;
				case ALLEGRO_KEY_ENTER:
				doexit = 1;
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

				case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				return -1;
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			if(y==0) {
				L1_S=0;
				L2_S=255;
				L3_S=255;
			}
			if(y==1) {
				L1_S=255;
				L2_S=0;
				L3_S=255;
			}
			if(y==2) {
				L1_S=255;
				L2_S=255;
				L3_S=0;
			}
			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_scaled_bitmap(fondo, 0, 0, 1920, 1200, 0, 0, config->SCREEN_W, config->SCREEN_H, 0);
			al_draw_textf(font, al_map_rgb(255, 255, 255), CUADRO_x + BOUNCER_SIZE, CUADRO_y - BOUNCER_SIZE, ALLEGRO_ALIGN_CENTRE, "Nombre del jugador: %s ",Name);
			al_draw_bitmap(CUADRO, CUADRO_x - BOUNCER_SIZE, CUADRO_y, 0);

			al_draw_textf(font, al_map_rgb(255, L1_S, L1_S), CUADRO_x + 00, CUADRO_y + 5, ALLEGRO_ALIGN_CENTRE, "%c",Name[0]);
			al_draw_textf(font, al_map_rgb(255, L2_S, L2_S), CUADRO_x + 15, CUADRO_y + 5, ALLEGRO_ALIGN_CENTRE, "%c",Name[1]);
			al_draw_textf(font, al_map_rgb(255, L3_S, L3_S), CUADRO_x + 30, CUADRO_y + 5, ALLEGRO_ALIGN_CENTRE, "%c",Name[2]);

			al_flip_display();
		}
	}

	al_destroy_bitmap(CUADRO);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	return 0;
}

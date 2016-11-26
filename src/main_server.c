//-lallegro -lallegro_image -lallegro_dialog -lallegro_acodec -lallegro_audio -lallegro_ttf -lallegro_font
#include "objects.h"
#include "prototypes.h"

int main(int argc, char **argv) {
	/**Variables de la lista*/
	Lista *p = NULL;
	cargarDatos(&p);
	/**CFG*/
	CFG config;
	config.SCREEN_W				= 680;										// Ancho de la ventana inicial
	config.SCREEN_H				= 382;										// Altura del fondo inicial
	config.NUM_PLAYERS		= 2;											// Jugadores maximos inicial
	config.NUM_BULLETS		= 10;											// Balas maximas en pantalla
	config.NUM_ENEMIES		= 4;											// Enemigos maximos en pantalla
	config.NUM_ENEMIESDEAD= 10;											// Efectos de enemigos muertos maximos en pantalla
	config.NUM_EXPLOSIONS	= 20;											// Explosiones maximas en pantalla
	config.gameOverWidth	= 800;										// Ancho de la imagen de Game over
	config.gameOverHeight	= 300;										// Altura de la imagen de Game over (No depende de nada, se autoescala)
	config.FPS						= 50;											// FPS
	config.font						= 10;											// Tamaño de la fuente
	config.ground					= 180;										// Piso del juego
	INI_LEVEL(&config);// INICIALIZO TODAS LAS VARIABLES RESTANTES
	ALV ALVAR;
	int x = 0;
	while (!x) {
		if (AL_INIT(&config, &ALVAR)) return -1;	// Iniciar componentes y cargar variables de ALLEGRO
		/**Iniciando el juego*/
		al_register_event_source(ALVAR.event_queue, al_get_display_event_source(ALVAR.display));	// Comenzar registro de eventos de la ventana
		al_register_event_source(ALVAR.event_queue, al_get_timer_event_source(ALVAR.timer));			// Comenzar registro de eventos del timer
		al_register_event_source(ALVAR.event_queue, al_get_keyboard_event_source());							// Comenzar registro de eventos del teclado
		al_start_timer(ALVAR.timer);																															// Empezar timer
		x = 1;
		if (title_screen(&config, &ALVAR)) {
			if (menu_screen(&config, &ALVAR, p)) {
				if (selection_screen(&ALVAR)) {
					x = gameLoop(&config, &ALVAR, p);
				}
			}
		}
	}
	alvar_free(&ALVAR);
	eliminarDatos(&p);
	return 0;
}

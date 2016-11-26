#include "objects.h"

int AL_INIT (CFG *config, ALV *ALVAR) {

	//ALV *ALVAR = NULL;
	//ALVAR = (ALV *) malloc (sizeof(ALV));
	//if (!ALVAR) return NULL;

	/**Iniciacion de componentes basicos de allegro*/
	if(!al_init()) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al iniciar allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al iniciar al_init!\n");
			return -1;
	}

	if(!al_init_image_addon()) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al iniciar el addon de imagenes!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al iniciar al_init_image_addon!\n");
			return -1;
	}

	ALVAR->timer = al_create_timer(1.0 / config->FPS);
	if(!ALVAR->timer) {
		al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al crear timer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		fprintf(stderr, "Error al crear timer!\n");
		return -1;
	}

	ALVAR->event_queue = al_create_event_queue();	// Creacion de variable de registro de eventos
	if(!ALVAR->event_queue) {
		al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al crear registro de eventos!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		fprintf(stderr, "Error al crear event_queue!\n");
		al_destroy_timer(ALVAR->timer);
		return -1;
	}

	ALVAR->display = al_create_display(config->SCREEN_W, config->SCREEN_H);	// Creacion del display
	if(!ALVAR->display) {
		al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar la ventana!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		fprintf(stderr, "Error al crear display!\n");
		al_destroy_timer(ALVAR->timer);
		al_destroy_event_queue(ALVAR->event_queue);
		return -1;
	}
	al_set_window_title(ALVAR->display, "Server - Metal Slug - TPO - R1021 - GRUPO 2 - 2016");	// Titulo del display

	ALVAR->fondoImage = al_load_bitmap("./assets/Fondo1.png");	// Cargar imagen del fondo 1
	if(!ALVAR->fondoImage) {
		al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen de fondo!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		fprintf(stderr, "Error al cargar imagen de fondo!\n");
		al_destroy_timer(ALVAR->timer);
		al_destroy_event_queue(ALVAR->event_queue);
		al_destroy_display(ALVAR->display);
		return -1;
	}

	ALVAR->playerImage = al_load_bitmap("./assets/MarcoRossi - Body.png");	// Cargar imagen del player
	if(!ALVAR->playerImage) {
		al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen del jugador!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		fprintf(stderr, "Error al cargar imagen de player!\n");
		al_destroy_timer(ALVAR->timer);
		al_destroy_event_queue(ALVAR->event_queue);
		al_destroy_display(ALVAR->display);
		al_destroy_bitmap(ALVAR->fondoImage);
		return -1;
	}

	if(!al_install_keyboard()) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al iniciar teclado!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al instalar teclado!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			return -1;
	}

	ALVAR->bulletImage = al_load_bitmap("./assets/bullet-machingun.png");	// Cargar imagen de la bala
	if(!ALVAR->bulletImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen de la bala!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen de bullet!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			return -1;
	}

	if(!al_install_audio()) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al iniciar el audio", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al instalar el audio!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			return -1;
 }

	if(!al_init_acodec_addon()) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar codecs de audio!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar iniciar addon de codecs!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			return -1;
	}

	if (!al_reserve_samples(20)) {	// Pedir espacio para la cantidad de sonidos a la vez maximo que se van a usar
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al reservar sonido!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al reservar samples (al_reserve_samples)!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			return -1;
	}

	ALVAR->m1start = al_load_sample( "./assets/MisionOneStart.wav" );	// Cargar sonido de inicio de mision 1
	if (!ALVAR->m1start) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar MisionOneStart.wav!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar sonido de inicio de mision 1!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			return -1;
	}

	ALVAR->bulletSound = al_load_sample("./assets/bulletSound.wav");	// Cargar sonido de la bala
	if (!ALVAR->bulletSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar sonido de la bala!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar sonido de la bala!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			return -1;
	}

	ALVAR->music1 = al_load_sample( "./assets/Music1.wav" );	// Cargar sonido de la mision 1
	if (!ALVAR->music1) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar Music1.wav!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar sonido de la mision 1!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			return -1;
	}

	al_init_font_addon();
	if (!al_init_ttf_addon()) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar el addon de ttf", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al iniciar addon ttf!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			return -1;
	}

	ALVAR->font = al_load_ttf_font("./assets/pirulen.ttf", config->font, 0);	// Cargar fuente
	if(!ALVAR->font) {
		al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar la fuente!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		fprintf(stderr, "Error al cargar el font!\n");
		al_destroy_timer(ALVAR->timer);
		al_destroy_event_queue(ALVAR->event_queue);
		al_destroy_display(ALVAR->display);
		al_destroy_bitmap(ALVAR->fondoImage);
		al_destroy_bitmap(ALVAR->playerImage);
		al_destroy_bitmap(ALVAR->bulletImage);
		al_destroy_sample(ALVAR->m1start);
		al_destroy_sample(ALVAR->bulletSound);
		al_destroy_sample(ALVAR->music1);
			return -1;
	}

	ALVAR->foot_playerImage = al_load_bitmap("./assets/MarcoRossi - Foot.png");	// Cargar imagen de los pies del player
	if(!ALVAR->foot_playerImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen del jugador!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen de los pies del player!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			return -1;
	}

	ALVAR->gameOverImage = al_load_bitmap("./assets/GameOver.png");	// Cargar imagen del fin del juego
	if(!ALVAR->gameOverImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen de Game over!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen de Game over!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			return -1;
	}

	ALVAR->gameOverSound = al_load_sample( "./assets/gameOverSound.wav" );	// Cargar sonido del fin del juego
	if (!ALVAR->gameOverSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar gameOverSound.wav!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar sonido de fin del juego!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			return -1;
	}

	ALVAR->enemyImage = al_load_bitmap("./assets/RebelSoldier.png");	// Cargar imagen del enemigo
	if(!ALVAR->enemyImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen del enemigo!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen de RebelSoldier!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			return -1;
	}

	ALVAR->grenadeImage = al_load_bitmap("./assets/grenade.png");	// Cargar imagen de la granada
	if(!ALVAR->grenadeImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen de la granada!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen de grenade!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			return -1;
	}

	ALVAR->rocketImage = al_load_bitmap("./assets/rocket.png");	// Cargar imagen del cohete
	if(!ALVAR->rocketImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen del cohete!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen de rocket!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			return -1;
	}

	ALVAR->explosionImage = al_load_bitmap("./assets/Explosions.png");	// Cargar imagen de las explosiones
	if(!ALVAR->explosionImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen de las explosiones!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen de explosion!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			return -1;
	}

	ALVAR->enemyDeadSound = al_load_sample("./assets/enemyDead.wav");	// Cargar sonido de las muertes de enemigos
	if(!ALVAR->enemyDeadSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar sonido de las muertes!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar sonido de muertes de enemigos!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			return -1;
	}

	ALVAR->explosionSound = al_load_sample("./assets/explosion.wav");	// Cargar sonido de las explosiones
	if(!ALVAR->explosionSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar sonido de las explosiones!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar sonido de explosion!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			return -1;
	}

	ALVAR->playerGrenadeImage = al_load_bitmap("./assets/playerGrenade.png");	// Cargar imagen de la granada del jugador
	if(!ALVAR->playerGrenadeImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen de la granada del jugador!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen de la granada del jugador!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			return -1;
	}

	ALVAR->titleScreenImage = al_load_bitmap("./assets/titleScreen.png");	// Cargar imagen del title Screen
	if(!ALVAR->titleScreenImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen del title screen!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen del title screen!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			return -1;
	}

	ALVAR->menuImage = al_load_bitmap("./assets/menu.png");	// Cargar imagen del menu
	if(!ALVAR->menuImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen del menu!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen del menu!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			return -1;
	}

	ALVAR->selectionImage = al_load_bitmap("./assets/soldierSelection.png");	// Cargar imagen de soldier selection
	if(!ALVAR->selectionImage) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar imagen de soldier selection!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar imagen de soldier selection!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			al_destroy_bitmap(ALVAR->menuImage);
			return -1;
	}

	ALVAR->okaySound = al_load_sample("./assets/Okay.wav");	// Cargar sonido de okay
	if(!ALVAR->okaySound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar el sonido de okay!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar el sonido de okay!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			al_destroy_bitmap(ALVAR->menuImage);
			al_destroy_bitmap(ALVAR->selectionImage);
			return -1;
	}

	ALVAR->menuSound = al_load_sample("./assets/Menu.wav");	// Cargar sonido del menu
	if(!ALVAR->menuSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar el sonido del menu!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar el sonido del menu!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			al_destroy_bitmap(ALVAR->menuImage);
			al_destroy_bitmap(ALVAR->selectionImage);
			al_destroy_sample(ALVAR->okaySound);
			return -1;
	}

	ALVAR->rechargeSound = al_load_sample("./assets/Recharge.wav");	// Cargar sonido de recargar
	if(!ALVAR->rechargeSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar el sonido de recargar!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar el sonido de recharge!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			al_destroy_bitmap(ALVAR->menuImage);
			al_destroy_bitmap(ALVAR->selectionImage);
			al_destroy_sample(ALVAR->okaySound);
			al_destroy_sample(ALVAR->menuSound);
			return -1;
	}

	ALVAR->soldierSelectionSound = al_load_sample("./assets/soldierSelection.wav");	// Cargar sonido de seleccion de personaje
	if(!ALVAR->soldierSelectionSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar el sonido de seleccion de personaje!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar el sonido de seleccion de personaje!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			al_destroy_bitmap(ALVAR->menuImage);
			al_destroy_bitmap(ALVAR->selectionImage);
			al_destroy_sample(ALVAR->okaySound);
			al_destroy_sample(ALVAR->menuSound);
			al_destroy_sample(ALVAR->rechargeSound);
			return -1;
	}

	ALVAR->marcoSound = al_load_sample("./assets/Marco.wav");	// Cargar sonido de seleccion de marco
	if(!ALVAR->marcoSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar el sonido de seleccion de marco!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar el sonido de seleccion de marco!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			al_destroy_bitmap(ALVAR->menuImage);
			al_destroy_bitmap(ALVAR->selectionImage);
			al_destroy_sample(ALVAR->okaySound);
			al_destroy_sample(ALVAR->menuSound);
			al_destroy_sample(ALVAR->rechargeSound);
			al_destroy_sample(ALVAR->soldierSelectionSound);
			return -1;
	}

	ALVAR->tarmaSound = al_load_sample("./assets/Tarma.wav");	// Cargar sonido de seleccion de tarma
	if(!ALVAR->tarmaSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar el sonido de seleccion de tarma!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar el sonido de seleccion de tarma!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			al_destroy_bitmap(ALVAR->menuImage);
			al_destroy_bitmap(ALVAR->selectionImage);
			al_destroy_sample(ALVAR->okaySound);
			al_destroy_sample(ALVAR->menuSound);
			al_destroy_sample(ALVAR->rechargeSound);
			al_destroy_sample(ALVAR->soldierSelectionSound);
			al_destroy_sample(ALVAR->marcoSound);
			return -1;
	}

	ALVAR->swapSelectionSound = al_load_sample("./assets/swapSelection.wav");	// Cargar sonido de cambio de seleccion
	if(!ALVAR->swapSelectionSound) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar el sonido de cambio seleccion!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar el sonido de cambio seleccion!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			al_destroy_bitmap(ALVAR->menuImage);
			al_destroy_bitmap(ALVAR->selectionImage);
			al_destroy_sample(ALVAR->okaySound);
			al_destroy_sample(ALVAR->menuSound);
			al_destroy_sample(ALVAR->rechargeSound);
			al_destroy_sample(ALVAR->soldierSelectionSound);
			al_destroy_sample(ALVAR->marcoSound);
			al_destroy_sample(ALVAR->tarmaSound);
			return -1;
	}

	ALVAR->player2Image = al_load_bitmap("./assets/TarmaRoving - Body.png");	// Cargar segunda imagen del player
	if(!ALVAR->player2Image) {
			al_show_native_message_box(ALVAR->display, "Error", "Error", "Error al cargar la segunda imagen del player!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			fprintf(stderr, "Error al cargar la segunda imagen del player!\n");
			al_destroy_timer(ALVAR->timer);
			al_destroy_event_queue(ALVAR->event_queue);
			al_destroy_display(ALVAR->display);
			al_destroy_bitmap(ALVAR->fondoImage);
			al_destroy_bitmap(ALVAR->playerImage);
			al_destroy_bitmap(ALVAR->bulletImage);
			al_destroy_sample(ALVAR->m1start);
			al_destroy_sample(ALVAR->bulletSound);
			al_destroy_sample(ALVAR->music1);
			al_destroy_font(ALVAR->font);
			al_destroy_bitmap(ALVAR->foot_playerImage);
			al_destroy_bitmap(ALVAR->gameOverImage);
			al_destroy_sample(ALVAR->gameOverSound);
			al_destroy_bitmap(ALVAR->enemyImage);
			al_destroy_bitmap(ALVAR->grenadeImage);
			al_destroy_bitmap(ALVAR->rocketImage);
			al_destroy_bitmap(ALVAR->explosionImage);
			al_destroy_sample(ALVAR->enemyDeadSound);
			al_destroy_sample(ALVAR->explosionSound);
			al_destroy_bitmap(ALVAR->playerGrenadeImage);
			al_destroy_bitmap(ALVAR->titleScreenImage);
			al_destroy_bitmap(ALVAR->menuImage);
			al_destroy_bitmap(ALVAR->selectionImage);
			al_destroy_sample(ALVAR->okaySound);
			al_destroy_sample(ALVAR->menuSound);
			al_destroy_sample(ALVAR->rechargeSound);
			al_destroy_sample(ALVAR->soldierSelectionSound);
			al_destroy_sample(ALVAR->marcoSound);
			al_destroy_sample(ALVAR->tarmaSound);
			al_destroy_sample(ALVAR->swapSelectionSound);
			return -1;
	}

	return 0;
}


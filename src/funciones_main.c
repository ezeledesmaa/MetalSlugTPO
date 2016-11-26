#include "objects.h"
#include "prototypes.h"

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_LEFT_U, KEY_RIGHT, KEY_RIGHT_U, KEY_EXIT, KEY_SPACE, KEY_SPACE_U, KEY_S, KEY_S_U, KEY_A
};

ALLEGRO_SAMPLE_ID	sound1;												// Creacion de la variable para poder para el sonido identificado con esta
/**Variables de Server TCP*/
int sockfd, newsockfd;
char buffer[1024];
int net, status, sentkey;

int selectImage				= 0;											// 0 = player 1 es marco, player 2 tarma - 1 = Al reves
int redraw = 1;

int title_screen (CFG *config, ALV *ALVAR) {
	/**Variables*/
	int frameCount		= 0;
	int frameDelay		= 30;
	int curFrame			= 0;
	int maxFrame			= 2;
	int frameHeight		= 382;
	int frameWidth		= 680;
	int title = 1;
	while (title) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(ALVAR->event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = 1;
			frameCount++;
			if(frameCount >= frameDelay) {
					frameCount = 0;
					curFrame++;
					if(curFrame >= maxFrame) {
						curFrame = 0;
					}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			title = 0;
			config->NUM_PLAYERS = 1;
			return 0;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_SPACE:
				title = 0;
				al_play_sample(ALVAR->okaySound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_play_sample(ALVAR->menuSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &sound1);
				break;
				case ALLEGRO_KEY_ESCAPE:
				title = 0;
				config->NUM_PLAYERS = 1;
				return 0;
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(ALVAR->event_queue)) {
			al_draw_bitmap_region(ALVAR->titleScreenImage, curFrame*frameWidth, 0, frameWidth, frameHeight, 0, 0, 0);
			al_flip_display();
			redraw = 0;
		}
	}
	return 1;
}

int menu_screen (CFG *config, ALV *ALVAR, Lista *p) {
	/**Variables*/
	int curFrame			= 0;
	int frameHeight		= 382;
	int frameWidth		= 680;
	int menu = 1;
		while (menu) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(ALVAR->event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = 1;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			menu = 0;
			config->NUM_PLAYERS = 1;
			return 0;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
				if (curFrame > 0) {
					curFrame--;
				}
				break;

				case ALLEGRO_KEY_DOWN:
				if (curFrame < 4) {
					curFrame++;
				}
				break;

				case ALLEGRO_KEY_ENTER:
				al_play_sample(ALVAR->rechargeSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				switch (curFrame) {
					case 0:		// Mision principal (un jugador)
					menu = 0;
					config->NUM_PLAYERS = 1;
					al_stop_sample(&sound1);
					al_play_sample(ALVAR->soldierSelectionSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &sound1);
					break;
					case 1:		// Multijugador
					menu = 0;
					InitServer(config, ALVAR->font, &sockfd, &newsockfd);
					al_stop_sample(&sound1);
					al_play_sample(ALVAR->soldierSelectionSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &sound1);
					break;
					case 2:		// Leaderborads
					while (ev.keyboard.keycode != ALLEGRO_KEY_ESCAPE) {
						al_wait_for_event(ALVAR->event_queue, &ev);
						al_draw_scaled_bitmap(ALVAR->gameOverImage, 0, 0, config->gameOverWidth, config->gameOverHeight, 0, 0, config->SCREEN_W, config->SCREEN_H, 0);
						imprimirDatos(&p, ALVAR->font, config);
						al_flip_display();
					}
					al_play_sample(ALVAR->swapSelectionSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
					case 3:		// Opciones

					break;
					case 4:		// Salir
					menu = 0;
					config->NUM_PLAYERS = 1;
					return 0;
					al_rest(0.3);
					break;
				}
				break;

				case ALLEGRO_KEY_ESCAPE:
				menu = 0;
				config->NUM_PLAYERS = 1;
				return 0;
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(ALVAR->event_queue)) {
			al_draw_bitmap_region(ALVAR->menuImage, curFrame*frameWidth, 0, frameWidth, frameHeight, 0, 0, 0);
			al_flip_display();
			redraw = 0;
		}
	}
	return 1;
}

int selection_screen (ALV *ALVAR) {
	int animationRow	= 0;
	int frameCount		= 0;
	int frameDelay		= 30;
	int curFrame			= 0;
	int maxFrame			= 2;
	int frameHeight		= 382;
	int frameWidth		= 680;
	int selection = 1;
		if (selection) {		// Soluciona el bug de multiplayer de pantalla negra en la seleccion de personaje (si no se presiona ninguna tecla queda negro)
		al_draw_bitmap_region(ALVAR->selectionImage, curFrame*frameWidth, animationRow*frameHeight, frameWidth, frameHeight, 0, 0, 0);
		al_flip_display();
	}

	while (selection) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(ALVAR->event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = 1;
			if (curFrame <= maxFrame) {
			frameCount++;
				if(frameCount >= frameDelay) {
					frameCount = 0;
					curFrame++;
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			selection = 0;
			return 0;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ENTER:
			selection = 0;
			switch (animationRow) {
				case 0:		// Si esta parado en marco
				al_play_sample(ALVAR->marcoSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				selectImage = 0;
				break;

				case 1:		// Si esta parado en tarma
				al_play_sample(ALVAR->tarmaSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				selectImage = 1;
				break;
			}
			al_rest(1);
			al_stop_sample(&sound1);
			break;

			case ALLEGRO_KEY_ESCAPE:
			selection = 0;
			return 0;
			break;

			case ALLEGRO_KEY_LEFT:
			if (animationRow > 0){
				animationRow--;
				al_play_sample(ALVAR->swapSelectionSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				curFrame = 0;
				frameCount = 0;
			}
			break;

			case ALLEGRO_KEY_RIGHT:
			if (animationRow < 1) {
				animationRow++;
				al_play_sample(ALVAR->swapSelectionSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				curFrame = 0;
				frameCount = 0;
			}
			break;

			}
		}
		if (redraw && al_is_event_queue_empty(ALVAR->event_queue)) {
			al_draw_bitmap_region(ALVAR->selectionImage, curFrame*frameWidth, animationRow*frameHeight, frameWidth, frameHeight, 0, 0, 0);
			al_flip_display();
			redraw = 0;
		}
	}
	return 1;
}

int gameLoop (CFG *config, ALV *ALVAR, Lista *p) {
	int game = 0;
	/**Variables de los objetos*/
	Player jugador[config->NUM_PLAYERS];
	Bullet bullets[config->NUM_BULLETS];
	Enemy enemies[config->NUM_ENEMIES];
	EnemyDead enemiesDead[config->NUM_ENEMIESDEAD];
	EnemyBullet enemiesBullet[config->NUM_E_BULLETS];
	Explosion explosions[config->NUM_EXPLOSIONS];
	strcpy(jugador[0].name,"AAA\0");
	strcpy(jugador[1].name,"AAA\0");

	/**Variables del player 1*/
	int RIGHT							= 0;
	int LEFT							= 0;
	int SPACE							= 0;
	int S									= 0;
	/**Variables del player 2*/
	int RIGHT2						= 0;
	int LEFT2							= 0;
	int SPACE2						= 0;
	int S2 								= 0;
	/**Variables del juego*/
	int redraw						= 1;											// Variable para el refresco de la pantalla
	int exitGameLoop			= 0;											// Variable para salir del gameloop
	int isGameOver				= 0;											// Variable para terminar el juego
	int playGameOver			= 1;											// Variable para ejecutar una sola vez ciertas cosas en el Game Over
	int maxtime						= 240;										// Tiempo maximo (en segundos)
	float timeElapsed			= 0;											// Tiempo que paso desde que se inicio el juego (en segundos)

////////////////////////////////////////////////////////////////////////////////////////
//JUAN
//BOSS
	int b1=0;// si boss1 esta vivo es 0, si esta muerto es 1
	int b2=0;// si boss2 esta vivo es 0, si esta muerto es 1
	int b3=0;// si boss3 esta vivo es 0, si esta muerto es 1
	struct BOSS BOSS1;
	struct BOSS BOSS2;
	struct BOSS BOSS3;
	int MY_TIME=0;
	int boss_sound=0;
////BOSS1////
	BOSS1.VIDA = al_load_bitmap("./assets/health.jpg");
	al_convert_mask_to_alpha(BOSS1.VIDA, al_map_rgb(255, 255, 255));
	BOSS1.MISSION_COMPLETE = al_load_bitmap("./assets/MISSION COMPLETE.png");
	al_convert_mask_to_alpha(BOSS1.MISSION_COMPLETE, al_map_rgb(255, 255, 255));

	BOSS1.BOSS_SOUND_MUSIC=al_load_sample( "./assets/BOSSFIGHT.wav" );
	if (!BOSS1.BOSS_SOUND_MUSIC){
		printf( "Audio clip sample not loaded!\n" );
		return -1;
	}
	BOSS1.BOSS_STAND = al_load_bitmap("./assets/allen_stand.png");
	al_convert_mask_to_alpha(BOSS1.BOSS_STAND, al_map_rgb(255, 255, 255));

	BOSS1.BOSS_FIRE = al_load_bitmap("./assets/allen_fire.png");
	al_convert_mask_to_alpha(BOSS1.BOSS_FIRE, al_map_rgb(255, 255, 255));

	BOSS1.BOSS_BULLET = al_load_bitmap("./assets/allen_bullet.png");
	al_convert_mask_to_alpha(BOSS1.BOSS_BULLET, al_map_rgb(255, 255, 255));

	BOSS1.BOSS_RUN = al_load_bitmap("./assets/allen_run.png");
	al_convert_mask_to_alpha(BOSS1.BOSS_RUN, al_map_rgb(255, 255, 255));

	BOSS1.BOSS_SOUND_STAND=al_load_sample( "./assets/allen_stand.wav" );
	if (!BOSS1.BOSS_SOUND_STAND){
		printf( "Audio clip sample not loaded!\n" );
		return -1;
	}

	BOSS1.BOSS_SOUND_FIRE=al_load_sample( "./assets/allen_fire.wav" );
	if (!BOSS1.BOSS_SOUND_FIRE){
		printf( "Audio clip sample not loaded!\n" );
		return -1;
	}


	BOSS1.BOSS_SOUND_MUSIC=al_load_sample( "./assets/BOSSFIGHT.wav" );
	if (!BOSS1.BOSS_SOUND_MUSIC){
		printf( "Audio clip sample not loaded!\n" );
		return -1;
	}

	BOSS1.BOSS_SOUND_MISSION_COMP=al_load_sample( "./assets/Mission_complete.wav" );
	if (!BOSS1.BOSS_SOUND_MISSION_COMP){
		printf( "Audio clip sample not loaded!\n" );
		return -1;
	}

////BOSS2////

	BOSS2.BOSS_STAND = al_load_bitmap("./assets/stank_stand.png");
	al_convert_mask_to_alpha(BOSS2.BOSS_STAND, al_map_rgb(0, 248, 0));

	BOSS2.BOSS_FIRE = al_load_bitmap("./assets/stank_fire.png");
	al_convert_mask_to_alpha(BOSS2.BOSS_FIRE, al_map_rgb(0, 248, 0));

	BOSS2.BOSS_BULLET = al_load_bitmap("./assets/tank_energy_ball1.png");
	al_convert_mask_to_alpha(BOSS2.BOSS_BULLET, al_map_rgb(0, 248, 0));

		BOSS2.VIDA = al_load_bitmap("./assets/health.jpg");
	al_convert_mask_to_alpha(BOSS2.VIDA, al_map_rgb(255, 255, 255));

	BOSS2.MISSION_COMPLETE = al_load_bitmap("./assets/MISSION COMPLETE.png");
	al_convert_mask_to_alpha(BOSS2.MISSION_COMPLETE, al_map_rgb(255, 255, 255));

	BOSS2.BOSS_SOUND_MISSION_COMP=al_load_sample( "./assets/Mission_complete.wav" );
	if (!BOSS2.BOSS_SOUND_MISSION_COMP){
		printf( "Audio clip sample not loaded!\n" );
		return -1;
	}

/////BOSS3///////////////////////////////////////////////

	BOSS3.VIDA = al_load_bitmap("./assets/health.jpg");
	al_convert_mask_to_alpha(BOSS3.VIDA, al_map_rgb(255, 255, 255));
	BOSS3.MISSION_COMPLETE = al_load_bitmap("./assets/MISSION COMPLETE.png");
	al_convert_mask_to_alpha(BOSS3.MISSION_COMPLETE, al_map_rgb(255, 255, 255));

	BOSS3.BOSS_SOUND_MUSIC=al_load_sample( "./assets/BOSSFIGHT.wav" );
	if (!BOSS3.BOSS_SOUND_MUSIC){
		printf( "Audio clip sample not loaded!\n" );
		return -1;
	}
	BOSS3.BOSS_STAND = al_load_bitmap("./assets/HAND_STAND1.png");
	al_convert_mask_to_alpha(BOSS3.BOSS_STAND, al_map_rgb(0, 255, 0));

	BOSS3.BOSS_FIRE = al_load_bitmap("./assets/HAND_FIRE.png");
	al_convert_mask_to_alpha(BOSS3.BOSS_FIRE, al_map_rgb(255, 255, 255));

	BOSS3.BOSS_BULLET = al_load_bitmap("./assets/HAND_BULLET.png");
	al_convert_mask_to_alpha(BOSS3.BOSS_BULLET, al_map_rgb(0, 255, 0));

	BOSS3.BOSS_RUN = al_load_bitmap("./assets/HAND_RUN.png");
	al_convert_mask_to_alpha(BOSS3.BOSS_RUN, al_map_rgb(0, 255, 0));

	BOSS3.BOSS_SOUND_MUSIC=al_load_sample( "./assets/BOSSFIGHT.wav" );
	if (!BOSS3.BOSS_SOUND_MUSIC){
		printf( "Audio clip sample not loaded!\n" );
		return -1;
	}

	BOSS3.BOSS_SOUND_MISSION_COMP=al_load_sample( "./assets/Mission_complete.wav" );
	if (!BOSS3.BOSS_SOUND_MISSION_COMP){
		printf( "Audio clip sample not loaded!\n" );
		return -1;
	}

BOSS3.BOSS_EX = al_load_bitmap("./assets/explosion.png");
al_convert_mask_to_alpha(BOSS3.BOSS_EX, al_map_rgb(0, 248, 0));

//////////////////////////////////////////////////////////
//JUAN
////////////////////////////////////////////////////////////////////////////////////////

	///Informar al cliente///
	if (!exitGameLoop && config->NUM_PLAYERS > 1) {
		if(write(newsockfd,"START",5) < 0) {
			error("ERROR writing to socket");
		}
	}
	else if (exitGameLoop && config->NUM_PLAYERS > 1) {
		if (write(newsockfd,"EXIT",4) < 0) {
			error("ERROR writing to socket");
		}
	}
	///Fin informar al cliente///

	srand(time(NULL));
	InitPlayer(jugador, ALVAR->playerImage, ALVAR->player2Image, ALVAR->foot_playerImage, selectImage ,config);
	InitBullet(bullets, ALVAR->bulletImage, ALVAR->playerGrenadeImage, ALVAR->bulletSound, config);
	InitEnemy(enemies, ALVAR->enemyImage, config);
	InitEnemyDead(enemiesDead, ALVAR->enemyImage, ALVAR->enemyDeadSound, config);
	Enemy_InitBullet(enemiesBullet, ALVAR->grenadeImage, ALVAR->rocketImage, config);
	InitExplosions(explosions, ALVAR->explosionImage, ALVAR->explosionSound, config);

	config->SCREEN_W	= 800;
	config->SCREEN_H = 224;
	al_resize_display(ALVAR->display, config->SCREEN_W, config->SCREEN_H);
	double tiempo = al_get_time();
	//BOSS
	InitBoss(&BOSS1,config);
	InitBoss2(&BOSS2,config);
	InitBoss3(&BOSS3,config);
	//																											// Variable para contar segundos despues
	al_play_sample(ALVAR->m1start, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);					// Reproducir sonido de inicio de mision 1
	al_play_sample(ALVAR->music1, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &sound1);				// Reproducir musica de mision 1

		while(!exitGameLoop) {
			ALLEGRO_EVENT ev;																													// Variable que recibe los eventos del juego
			al_wait_for_event(ALVAR->event_queue, &ev);
			/// Net ///
			if(net == 1) {
				switch(sentkey) {
				case KEY_LEFT:
				jugador[1].isMoving = status;
				LEFT2 = status;
				jugador[1].foot_curFrame = 0;
				jugador[1].foot_frameCount = 0;
				break;
				case KEY_RIGHT:
				jugador[1].isMoving = status;
				jugador[1].foot_curFrame = 0;
				jugador[1].foot_frameCount = 0;
				RIGHT2 = status;
				break;
				case KEY_EXIT:
				exitGameLoop = 1;
				break;
				case KEY_SPACE:
				SPACE2 = status;
				break;
				case KEY_S:
				S2 = status;
				if (!jugador[1].machineGun && status) {																	// Si no tiene machinGun
					if (!jugador[1].animationDirection) {																	// Si el jugador esta mirando hacia la derecha
						FireBullet(bullets, jugador, 1, 0, config, 1);
					}
					else {
						FireBullet(bullets, jugador, -1, 0,config, 1);
					}
				}
				break;
				case KEY_A:
				if (jugador[1].bombs > 0) {																							// Si tiene municion
					if (jugador[1].count2 < jugador[1].shoot_delay*2) {
						jugador[1].count2++;
					}
					else {
						if (!jugador[1].animationDirection) {																// Si el jugador esta mirando hacia la derecha
							FireBullet(bullets, jugador, 1, 1, config, 1);
						}
						else {
							FireBullet(bullets, jugador, -1, 1, config, 1);
						}
						jugador[1].bombs--;
						jugador[1].count2 = 0;
					}
				}
				break;
				}
			}
			///Fin net///

			///Timer///
			if(ev.type == ALLEGRO_EVENT_TIMER) {
				net = get_network_data(newsockfd, buffer, &status, &sentkey);
				redraw = 1;																														// Refrescar pantalla al terminar
				if(SPACE) {																														// Mientras este presionado el boton arriba
					if (jugador[0].jump_allowed) {
						jugador[0].jump = 1;
					}
				}
				if(SPACE2) {
					if (jugador[1].jump_allowed) {
						jugador[1].jump = 1;
						SPACE2 = 0;
					}
				}
				if(LEFT && jugador[0].x >= jugador[0].speed) {												// Mientras este presionada la izquierda
					MovePlayerLeft(jugador, 0, config);
				}
				if(LEFT2 && jugador[1].x >= jugador[1].speed) {												// Mientras este presionada la izquierda
					MovePlayerLeft(jugador, 1, config);
				}
				if(RIGHT) {																														// Mientras este presionada la derecha
					MovePlayerRight(jugador, 0, enemiesDead, config, enemies);
				}
				if(RIGHT2) {																													// Mientras este presionada la derecha
					MovePlayerRight(jugador, 1, enemiesDead, config, enemies);
				}
				if(S) {																																// Mientras este presionada la tecla espacio
					if (jugador[0].machineGun && jugador[0].ammo) {											// Si tiene machineGun y municion
						if (jugador[0].count < jugador[0].shoot_delay) {
							jugador[0].count++;
						}
						else {
							if (!jugador[0].animationDirection) {														// Si el jugador esta mirando hacia la derecha
								FireBullet(bullets, jugador, 1, 0, config, 0);
							}
							else {
								FireBullet(bullets, jugador, -1, 0, config, 0);
							}
							jugador[0].ammo--;
							jugador[0].count = 0;
						}
					}
					else {
						jugador[0].machineGun = 0;
					}
				}
				if (S2) {
					if (jugador[1].machineGun && jugador[1].ammo) {											// Si tiene machineGun y municion
						if (jugador[1].count < jugador[1].shoot_delay) {
							jugador[1].count++;
						}
						else {
							if (!jugador[1].animationDirection) {														// Si el jugador esta mirando hacia la derecha
								FireBullet(bullets, jugador, 1, 0, config, 1);
							}
							else {
								FireBullet(bullets, jugador, -1, 0, config, 1);
							}
							jugador[1].ammo--;
							jugador[1].count = 0;
						}
					}
					else {
						jugador[1].machineGun = 0;
					}
				}
				if(!isGameOver) {																											// Mientras el juego no halla terminado
					UpdatePlayer(jugador, config);
					UpdateBullet(bullets, explosions, config);
					UpdateExplosions(explosions, config);
					//#JUAN
					if(config->FONDO_X>=2200) { //actulizar boss
						boss_sound++;
						if(boss_sound==1) {
							al_stop_samples();
							al_play_sample(BOSS1.BOSS_SOUND_MUSIC, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
							boss_sound=2;	//para que ejecute el sonido una vez
						}
						if(BOSS1.damage<=1 && BOSS2.damage==0 && b1==0){//ACTIVAR COLISIONES BOSS1
					Boss_colision(&BOSS1,jugador,bullets,config,explosions);
					BOSS_CollideBullet(&BOSS1,jugador,config,explosions);
					}

					if(BOSS1.damage>=1 && BOSS2.damage<=1 && b1==1 && b2==0){//ACTIVAR COLISIONES BOSS2
					Boss_colision2(&BOSS2,jugador,bullets,config,explosions);
					BOSS_CollideBullet2(&BOSS2,jugador,config,explosions);
					}

					if(BOSS3.damage<=1 && b1==1 && b2==1 && b3==0 ){//ACTIVAR COLISIONES BOSS3
					Boss_colision3(&BOSS3,jugador,bullets,config,explosions);
					BOSS_CollideBullet3(&BOSS3,jugador,config,explosions);
					if(MY_TIME>=7*60 && MY_TIME<8*60){
				BOSS3_EXPLOTION(&BOSS3,jugador,config);
					}
					}

				}
				else//actulizar enemigos
				{
					StartEnemy(enemies, config);
					UpdateEnemy(enemies, jugador, enemiesBullet, config);
					CollideBullet(bullets, enemies, jugador, enemiesDead, explosions, config);
					UpdateEnemyDead(enemiesDead, config);
					Enemy_UpdateBullet(enemiesBullet, explosions, config);
					Enemy_CollideBullet(enemiesBullet, jugador, explosions, config);
				}
					jugador[0].count2++;
					if (config->NUM_PLAYERS > 1) {
						jugador[1].count2++;
					}
					if(jugador[0].lives <= 0) {																				// Si no quedan vidas terminar el juego
						if (config->NUM_PLAYERS > 1) {
							if (jugador[1].lives <= 0) {
								isGameOver = 1;
							}
						}
						else {
							isGameOver = 1;
						}
					}
				}
			}
			///Fin timer///

			///Cerrar ventana///
			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {													// Si se cierra la ventana, terminar juego
				exitGameLoop = 1;
				game = 1;
			}
			///Fin cerrar ventanta///

			///Tecla presionada///
			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {															// Si se presiona una tecla
				switch(ev.keyboard.keycode) {
					case ALLEGRO_KEY_LEFT:
					LEFT = 1;
					jugador[0].foot_curFrame = 0;
					jugador[0].foot_frameCount = 0;
					break;
					case ALLEGRO_KEY_RIGHT:
					jugador[0].foot_curFrame = 0;
					jugador[0].foot_frameCount = 0;
					RIGHT = 1;
					break;
					case ALLEGRO_KEY_SPACE:
					SPACE = 1;
					break;
					case ALLEGRO_KEY_S:
					S = 1;
					if (!jugador[0].machineGun) {																			// Si no tiene machinGun
						if (!jugador[0].animationDirection) {														// Si el jugador esta mirando hacia la derecha
							FireBullet(bullets, jugador, 1, 0, config, 0);
						}
						else {
							FireBullet(bullets, jugador, -1, 0,config, 0);
						}
					}
					break;
					case ALLEGRO_KEY_A:
					if (jugador[0].bombs > 0) {																				// Si tiene municion
						if (jugador[0].count2 < jugador[0].shoot_delay*2) {
							jugador[0].count2++;
						}
						else {
							if (!jugador[0].animationDirection) {													// Si el jugador esta mirando hacia la derecha
									FireBullet(bullets, jugador, 1, 1, config, 0);
								}
							else {
									FireBullet(bullets, jugador, -1, 1, config, 0);
							}
							jugador[0].bombs--;
							jugador[0].count2 = 0;
						}
					}
					break;
				}
			}
			///Fin tecla presionada///

			///Tecla soltada///
			else if(ev.type == ALLEGRO_EVENT_KEY_UP) {																// Si se suelta una tecla
				switch(ev.keyboard.keycode) {
					case ALLEGRO_KEY_LEFT:
					LEFT = 0;
					jugador[0].isMoving = 0;
					jugador[0].foot_curFrame = 0;
					jugador[0].foot_frameCount = 0;
					break;
					case ALLEGRO_KEY_RIGHT:
					RIGHT = 0;
					jugador[0].isMoving = 0;
					jugador[0].foot_curFrame = 0;
					jugador[0].foot_frameCount = 0;
					break;
					case ALLEGRO_KEY_SPACE:
					SPACE = 0;
					break;
					case ALLEGRO_KEY_ESCAPE:
					exitGameLoop = 1;
					game = 1;
					break;
					case ALLEGRO_KEY_S:
					S	= 0;
					break;
				}
			}
			///Fin tecla soltada///

			///Refrescar pantalla///
			if(redraw && al_is_event_queue_empty(ALVAR->event_queue)) {					// Si hay que refrescar y no hay eventos
				if(!isGameOver) {																							// Si el juego no se termino
					al_clear_to_color (al_map_rgb(0, 0, 0));
					if(config->FONDO_X>=2200) { //BOSS FONDO ROJO
						al_draw_tinted_bitmap(ALVAR->fondoImage, al_map_rgba_f(1,0.5, 0.5, 1), -config->FONDO_X, config->SCREEN_H - config->FONDO_H, 0);
					}
					else {
						al_draw_bitmap(ALVAR->fondoImage, -config->FONDO_X, config->SCREEN_H - config->FONDO_H, 0);
					}
					DrawPlayer(jugador, config);
					DrawBullet(bullets, config);
					DrawExplosions(explosions, config);
					if(config->FONDO_X>=2200) { //cargar imagen de boss
						MY_TIME++;
						if(MY_TIME>10*config->FPS) {
							MY_TIME=0;
						}
						if(b1==0){
						DrawBOSS1(&BOSS1, config->FPS, MY_TIME, jugador);
						DrawBOSS1_VIDA(&BOSS1, ALVAR->font);
					}

					if(b1==1 && b2==0)
					{
						DrawBOSS2(&BOSS2, config->FPS, MY_TIME, jugador);
						DrawBOSS1_VIDA(&BOSS2, ALVAR->font);
					}

					if(b1==1 && b2==1 && b3==0)
					{
						DrawBOSS3(&BOSS3, config->FPS, MY_TIME, jugador,config);
						DrawBOSS1_VIDA(&BOSS3, ALVAR->font);
					}

						if(BOSS1.music_1==1 && b1==0){//cuando el boss muere es =1 ; entonces cargo el nivel 2 //NIVEL 2
							boss_sound=0;
							MY_TIME=0;
							INI_LEVEL(config);
							INI_LEVEL_2(jugador,config);
							maxtime=maxtime+timeElapsed;//RESETEO EL TIEMPO
							ALVAR->rocketImage = al_load_bitmap("./assets/espada_proyectil.png");
							ALVAR->fondoImage = al_load_bitmap("./assets/desierto2.png");	// Cargar imagen del fondo 1
							ALVAR->enemyImage = al_load_bitmap("./assets/arab.png");
							ALVAR->grenadeImage = al_load_bitmap("./assets/espada.png");
							InitEnemy_LEVEL2(enemies, ALVAR->enemyImage, config);
							Enemy_InitBullet_LEVEL2(enemiesBullet, ALVAR->grenadeImage, ALVAR->rocketImage, config);
							InitEnemyDead_LEVEL2(enemiesDead, ALVAR->enemyImage, ALVAR->enemyDeadSound, config);
							ALVAR->music1 = al_load_sample( "./assets/mission2.wav" );
							al_play_sample(ALVAR->music1, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
							BOSS1.music_1=2;
							b1=1;//EL BOSS 1 MURIO :(
						}
						if(BOSS2.music_1==1 && b1==1 && b2==0){//cuando el boss muere es =1 ; entonces cargo el nivel 3 //NIVEL 3
							boss_sound=0;
							MY_TIME=0;
							INI_LEVEL(config);
							INI_LEVEL_2(jugador,config);
							maxtime=maxtime+timeElapsed;//RESETEO EL TIEMPO
							ALVAR->rocketImage = al_load_bitmap("./assets/rocket-3.png");
							ALVAR->fondoImage = al_load_bitmap("./assets/Fondo3.png");	// Cargar imagen del fondo 1
							ALVAR->enemyImage = al_load_bitmap("./assets/RebelSoldier-3.png");
							ALVAR->grenadeImage = al_load_bitmap("./assets/grenade.png");
							InitEnemy_LEVEL2(enemies, ALVAR->enemyImage, config);
							Enemy_InitBullet_LEVEL2(enemiesBullet, ALVAR->grenadeImage, ALVAR->rocketImage, config);
							InitEnemyDead_LEVEL2(enemiesDead, ALVAR->enemyImage, ALVAR->enemyDeadSound, config);
							ALVAR->music1 = al_load_sample( "./assets/mission3.wav" );
							BOSS1.BOSS_SOUND_MUSIC=al_load_sample( "./assets/FINAL-BOSS.wav" );
							al_play_sample(ALVAR->music1, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
							BOSS2.music_1=2;
							BOSS3.damage=0;
							b2=1;//EL BOSS 2 MURIO :(
						}

						if(BOSS3.music_1==1)
						{
							ALVAR->gameOverSound = al_load_sample( "./assets/WIN.wav" );	// Cargar sonido del fin del juego
							jugador[0].lives = 0;
							jugador[1].lives = 0;

					}

					}
					else { //cargar imagen de enemigos
						DrawEnemy(enemies, config);
						DrawEnemyDead(enemiesDead, config);
						Enemy_DrawBullet(enemiesBullet, config);
					}
					al_draw_textf(ALVAR->font, al_map_rgb(255, 255, 255), 0, 0, 0, "P1 - Vidas: %d  - Score: %d - Ammo: %d - Bombs: %d", jugador[0].lives, jugador[0].score, jugador[0].ammo, jugador[0].bombs);
					if (config->NUM_PLAYERS == 2) {
						al_draw_textf(ALVAR->font, al_map_rgb(255, 255, 255), 0, config->font, 0, "P2 - Vidas: %d  - Score: %d - Ammo: %d - Bombs: %d", jugador[1].lives, jugador[1].score, jugador[1].ammo, jugador[1].bombs);
					}
					al_draw_textf(ALVAR->font, al_map_rgb(255, 255, 255), config->SCREEN_W/2, 0, ALLEGRO_ALIGN_LEFT, "Tiempo: %.1f",maxtime - timeElapsed);
					timeElapsed = (al_get_time() - tiempo);
					if ((maxtime - (int)timeElapsed) <= 0) {
						isGameOver = 1;
					}
				}
				else {																															// Si el juego se termino
					if (playGameOver) {																								// Como el game loop sigue esto hace que se ejecute una sola vez
						al_stop_samples();																							// Parar todos los sonidos
						al_play_sample(ALVAR->gameOverSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						playGameOver = 0;
						if (selectName(jugador[0].name, ALVAR->display, ALVAR->font, config)) {
							exitGameLoop = 1;
						}
						if (config->NUM_PLAYERS > 1 && !exitGameLoop) {
							if (selectName(jugador[1].name, ALVAR->display, ALVAR->font, config)) {
								exitGameLoop = 1;
							}
						}
						if (!exitGameLoop) {
							al_draw_scaled_bitmap(ALVAR->gameOverImage, 0, 0, config->gameOverWidth, config->gameOverHeight, 0, 0, config->SCREEN_W, config->SCREEN_H, 0);
							int j = 0;
							while (j < config->NUM_PLAYERS) {
								Score *scoreJugador;
								scoreJugador = malloc (sizeof(Score));
								if (!scoreJugador) return -1;
								strcpy(scoreJugador->nombre, jugador[j].name);
								scoreJugador->puntos = jugador[j].score;
								agregarDatos(&p, scoreJugador);
								al_draw_textf(ALVAR->font, al_map_rgb(255, 255, 255), config->SCREEN_W/4, config->SCREEN_H/1.25 + j*config->font, ALLEGRO_ALIGN_CENTRE, "Score Player %d \"%s\": %d", j+1, jugador[j].name, jugador[j].score);
								j++;
							}
						}
						imprimirDatos(&p, ALVAR->font, config);
						guardarDatos(&p);
					}
				}
				al_flip_display();
				redraw = 0;
			}
			///Fin refrescar pantalla///
		}

	if (config->NUM_PLAYERS > 1) {
		close(newsockfd);
		close(sockfd);
	}
	return game;
}

void alvar_free(ALV *ALVAR) {
	/**Liberar memoria*/
	al_destroy_display(ALVAR->display);
	al_destroy_bitmap(ALVAR->fondoImage);
	al_destroy_bitmap(ALVAR->playerImage);
	al_destroy_event_queue(ALVAR->event_queue);
	al_destroy_timer(ALVAR->timer);
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
	al_destroy_bitmap(ALVAR->player2Image);
}

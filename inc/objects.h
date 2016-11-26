#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PUERTO 9125

#include <stdlib.h>

struct P {
	float x;
	float y;
	int lives;
	float speed;
	int boundx;
	int boundy;
	int score;
	char name[4];

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationDirection;
	int animationRow;
	int isMoving;
	int ajuste;
	int jump;
	int jump_allowed;
	float speed_y;
	int machineGun;
	int ammo;
	int bombs;
	int shoot_delay;
	int count;
	int count2;

	int foot_x;
	int foot_y;

	int foot_maxFrame;
	int foot_curFrame;
	int foot_frameCount;
	int foot_frameDelay;
	int foot_frameWidth;
	int foot_frameHeight;

	int foot_animationRow;

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *foot_image;
};
typedef struct P Player;

struct B {
	float x;
	float y;
	int lives;
	int speed;
	float speed_y;
	float angle;
	int direction;
	int bulletImage;
	int player;

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *image2;
	ALLEGRO_SAMPLE *bulletSound;
};
typedef struct B Bullet;

struct E {
	int x;
	int y;
	int lives;
	int speed;
	int boundx;
	int boundy;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationRow;
	int animationDirection;
	int action;

	int ajuste;

	ALLEGRO_BITMAP *image;
};
typedef struct E Enemy;

struct ED {
	int x;
	int y;
	int lives;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationRow;
	int animationDirection;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sound;
};
typedef struct ED EnemyDead;

struct EB {
	float x;
	float y;
	float c_x;
	float c_y;
	int lives;
	float speed;
	int direction;
	int animationDirection;
	int bulletImage;
	float speed_y;
	float angle;

	ALLEGRO_BITMAP *image1;
	ALLEGRO_BITMAP *image2;
};
typedef struct EB EnemyBullet;

struct EX {
	int x;
	int y;
	int lives;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationRow;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sound;
};
typedef struct EX Explosion;

struct CO {
	int SCREEN_W;
	int SCREEN_H;
	int NUM_PLAYERS;
	int NUM_BULLETS;
	int NUM_ENEMIES;
	int NUM_ENEMIESDEAD;
	int NUM_EXPLOSIONS;
	int NUM_E_BULLETS;
	int FONDO_X;
	int FONDO_W;
	int FONDO_H;
	int gameOverWidth;
	int gameOverHeight;
	float FPS;
	int font;
	float ground;
};
typedef struct CO CFG;

// Listas
struct SC {
	char nombre[4];
	int puntos;
};
typedef struct SC Score;

struct nodo {
	void *dato;
	struct nodo *sig;
	struct nodo *ant;
};
typedef struct nodo Lista;
//

struct BOSS {
	int x;
	int y;
	int BOSS_SPEED;
	int BOSS_TIMER;

	//vida
	float damage;
	int VIDA_ANCHO;
	int VIDA_ALTO;
	//variables para las sprites


	//Variables para Boss parado
	int BOSS_maxFrame;
	int BOSS_curFrame;
	int BOSS_frameCount;
	int BOSS_frameDelay;
	int BOSS_frameWidth;
	int BOSS_frameHeight;

	//Variables para Boss corriendo
	int BOSS_RUN_maxFrame;
	int BOSS_RUN_curFrame;
	int BOSS_RUN_frameCount;
	int BOSS_RUN_frameDelay;
	int BOSS_RUN_frameWidth;
	int BOSS_RUN_frameHeight;

	//Variables para Boss disparando
	int BOSS_FIRE_maxFrame;
	int BOSS_FIRE_curFrame;
	int BOSS_FIRE_frameCount;
	int BOSS_FIRE_frameDelay;
	int BOSS_FIRE_frameWidth;
	int BOSS_FIRE_frameHeight;
	int BOSS_BULLET_X;
	int BOSS_BULLET_Y;
	int BOSS_BULLET_SPEED;
	int BOSS_BULLET_W;
	int BOSS_BULLET_H;
	int dir;
	int state;
	

	int music_1;
	ALLEGRO_BITMAP *BOSS_FIRE;
	ALLEGRO_BITMAP *BOSS_RUN;
	ALLEGRO_BITMAP *BOSS_STAND;
	ALLEGRO_BITMAP *BOSS_BULLET;
	ALLEGRO_BITMAP *VIDA;
	ALLEGRO_BITMAP *MISSION_COMPLETE;

	ALLEGRO_SAMPLE *BOSS_SOUND_STAND;
	ALLEGRO_SAMPLE *BOSS_SOUND_FIRE;
	ALLEGRO_SAMPLE *BOSS_SOUND_DEAD;
	ALLEGRO_SAMPLE *BOSS_SOUND_MUSIC;
	ALLEGRO_SAMPLE *BOSS_SOUND_MISSION_COMP;
	
	//EXPLOSIONES
	
	int BOSS_EX_maxFrame;
	int BOSS_EX_curFrame;
	int BOSS_EX_frameCount;
	int BOSS_EX_frameDelay;
	int BOSS_EX_frameWidth;
	int BOSS_EX_frameHeight;
	ALLEGRO_BITMAP *BOSS_EX;

};

struct AV {
	/**Variables de allegro*/
	ALLEGRO_DISPLAY	*display;//								= NULL;	// Creacion de la variable para la ventana
	ALLEGRO_BITMAP	*fondoImage;//							= NULL;	// Creacion de la variable para la imagen fondo
	ALLEGRO_BITMAP	*playerImage;//						= NULL;	// Creacion de la variable para la imagen del jugador
	ALLEGRO_BITMAP	*player2Image;//						= NULL;	// Creacion de la variable para la segunda imagen del jugador
	ALLEGRO_BITMAP	*foot_playerImage;//				= NULL;	// Creacion de la variable para la imagen de los pies del jugador
	ALLEGRO_BITMAP	*gameOverImage;//					= NULL;	// Creacion de la variable para la imagen del fin del juego
	ALLEGRO_BITMAP	*bulletImage;//						= NULL;	// Creacion de la variable para la imagen de la bala
	ALLEGRO_BITMAP	*enemyImage;//							= NULL;	// Creacion de la variable para la imagen del enemigo
	ALLEGRO_BITMAP	*grenadeImage;//						= NULL;	// Creacion de la variable para la imagen de la granada
	ALLEGRO_BITMAP	*playerGrenadeImage;//			= NULL;	// Creacion de la variable para la imagen de la granada del jugador
	ALLEGRO_BITMAP	*rocketImage;//						= NULL;	// Creacion de la variable para la imagen del cohete
	ALLEGRO_BITMAP	*explosionImage;//					= NULL;	// Creacion de la variable para la imagen de las explosiones
	ALLEGRO_BITMAP	*titleScreenImage;//				= NULL;	// Creacion de la variable para la imagen del titleScreen
	ALLEGRO_BITMAP	*menuImage;//							= NULL;	// Creacion de la variable para la imagen del menu
	ALLEGRO_BITMAP	*selectionImage;//					= NULL;	// Creacion de la variable para la imagen del soldier selection
	ALLEGRO_EVENT_QUEUE	*event_queue;//				= NULL;	// Creacion de la variable para los eventos del juego
	ALLEGRO_TIMER		*timer;//									= NULL;	// Creacion de la variable para los FPS del juego
	ALLEGRO_SAMPLE	*m1start;//								= NULL;	// Creacion de la variable para el sonido de inicio
	ALLEGRO_SAMPLE	*bulletSound;//						= NULL;	// Creacion de la variable para el sonido de disparo
	ALLEGRO_SAMPLE	*music1;//									= NULL;	// Creacion de la variable para el sonido de la musica de fondo
	ALLEGRO_SAMPLE	*gameOverSound;//					= NULL;	// Creacion de la variable para el sonido del fin del juego
	ALLEGRO_SAMPLE	*enemyDeadSound;//					= NULL;	// Creacion de la variable para el sonido de muerte de un enemigo
	ALLEGRO_SAMPLE	*explosionSound;//					= NULL;	// Creacion de la variable para el sonido de las explosiones
	ALLEGRO_SAMPLE	*okaySound;//							= NULL;	// Creacion de la variable para el sonido de okay
	ALLEGRO_SAMPLE	*menuSound;//							= NULL;	// Creacion de la variable para el sonido del menu
	ALLEGRO_SAMPLE	*rechargeSound;//					= NULL;	// Creacion de la variable para el sonido de recargar
	ALLEGRO_SAMPLE	*soldierSelectionSound;//	= NULL;	// Creacion de la variable para el sonido de seleccion de personaje
	ALLEGRO_SAMPLE	*marcoSound;//							= NULL;	// Creacion de la variable para el sonido de seleccion de marco
	ALLEGRO_SAMPLE	*tarmaSound;//							= NULL;	// Creacion de la variable para el sonido de seleccion de tarma
	ALLEGRO_SAMPLE	*swapSelectionSound;//			= NULL;	// Creacion de la variable para el sonido de cambio de seleccion
	ALLEGRO_FONT	*font;//											= NULL;	// Creacion de la variable para la fuente del texto
};
typedef struct AV ALV;

#include "objects.h"
#include "prototypes.h"

void INI_LEVEL(CFG *config) {
	config->NUM_E_BULLETS	= 10;											// Balas de enemigos maximas en pantalla
	config->FONDO_X			= 0;											// Inicio del fondo (se usa para recorrerlo)
	config->FONDO_W 		= 3054;										// Variable para establecer el fin del fondo // al_get_bitmap_width
	config->FONDO_H 		= 224;										// Variable para establecer la altura del fondo // al_get_bitmap_height
}

void INI_LEVEL_2(Player jugador[],CFG *config) {
	int i=0;
	while (i < config->NUM_PLAYERS) {
		jugador[i].x = 0;
		jugador[i].machineGun=1;
		jugador[i].ammo=200;																// PONE LA CANTIDAD DE BALAS A 100.
		jugador[i].bombs=50;
		config->ground = config->SCREEN_H /1.15;
		jugador[i].y = config->ground;								// Posicion en y del jugador
		jugador[i].foot_x = jugador[i].x;
		jugador[i].foot_y = jugador[i].y;
		i++;
	}
}

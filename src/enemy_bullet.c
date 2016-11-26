#include "objects.h"
#include "prototypes.h"
void Enemy_InitBullet(EnemyBullet enemiesBullet[], ALLEGRO_BITMAP *image1, ALLEGRO_BITMAP *image2, CFG *config) {
		int i = 0;
		while (i < config->NUM_E_BULLETS) {
				enemiesBullet[i].speed = 2;
				enemiesBullet[i].lives = 0;
				enemiesBullet[i].c_x = 5;
				enemiesBullet[i].c_y = 7;
				enemiesBullet[i].direction = 1;
				enemiesBullet[i].animationDirection = 1;
				enemiesBullet[i].image1 = image1;
				enemiesBullet[i].image2 = image2;
				enemiesBullet[i].angle = 0;
				i++;
		}
}

void Enemy_InitBullet_LEVEL2(EnemyBullet enemiesBullet[], ALLEGRO_BITMAP *image1, ALLEGRO_BITMAP *image2, CFG *config) {
		int i = 0;
		while (i < config->NUM_E_BULLETS) {
				enemiesBullet[i].speed = 3;
				enemiesBullet[i].lives = 0;
				enemiesBullet[i].c_x = 12.5;
				enemiesBullet[i].c_y = 20;
				enemiesBullet[i].direction = 1;
				enemiesBullet[i].animationDirection = 1;
				enemiesBullet[i].image1 = image1;
				enemiesBullet[i].image2 = image2;
				enemiesBullet[i].angle = 0;
				i++;
		}
}



void Enemy_DrawBullet(EnemyBullet enemiesBullet[], CFG *config) {
		int i = 0;
		while (i < config->NUM_E_BULLETS) {
				if(enemiesBullet[i].lives > 0){
						if (!enemiesBullet[i].bulletImage) {
							al_draw_rotated_bitmap(enemiesBullet[i].image1, enemiesBullet[i].c_x, enemiesBullet[i].c_y, enemiesBullet[i].x, enemiesBullet[i].y, enemiesBullet[i].angle,enemiesBullet[i].animationDirection);
						}
						else {
							al_draw_bitmap(enemiesBullet[i].image2, enemiesBullet[i].x, enemiesBullet[i].y, enemiesBullet[i].animationDirection);
						}
				}
				i++;
		}
}
//
void Enemy_FireBullet(EnemyBullet enemiesBullet[], Enemy enemies[], int eNum, int Enemy_bulletDirection, CFG *config) {
	int i = 0;
	while (i < config->NUM_E_BULLETS) {
		if(enemiesBullet[i].lives <= 0) {
			enemiesBullet[i].direction = Enemy_bulletDirection;
			enemiesBullet[i].animationDirection = enemies[eNum].animationDirection;
			enemiesBullet[i].speed = 2;
			enemiesBullet[i].speed_y = -2;
			enemiesBullet[i].angle = 0;
			if (enemies[i].animationRow == 2) {																									// Si estan lanzando granadas
				enemiesBullet[i].bulletImage = 0;
				enemiesBullet[i].speed = 4;
			}
			else if (enemies[i].animationRow == 3) {																						// Si estan lanzando cohetes
				enemiesBullet[i].bulletImage = 1;
				enemiesBullet[i].speed = 2;
			}
			//al_play_sample(bullet[i].bulletSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (enemies[eNum].animationDirection) {
				enemiesBullet[i].x = enemies[eNum].x + enemies[eNum].frameWidth/2 * -(enemies[eNum].animationDirection) + enemies[eNum].ajuste;
			}
			else {
				enemiesBullet[i].x = enemies[eNum].x + enemies[eNum].frameWidth/2 * -(enemies[eNum].animationDirection);
			}
			enemiesBullet[i].y = enemies[eNum].y - enemies[eNum].frameHeight/1.75;
			enemiesBullet[i].lives = 1;
			break;
		}
		i++;
	}
}

void Enemy_UpdateBullet(EnemyBullet enemiesBullet[], Explosion explosions[], CFG *config) {
		int i = 0;
		while (i < config->NUM_E_BULLETS) {
				if(enemiesBullet[i].lives > 0) {
						enemiesBullet[i].x += (enemiesBullet[i].speed) * enemiesBullet[i].direction;
						if(enemiesBullet[i].x > config->SCREEN_W || enemiesBullet[i].x <0) {																// Si la bala llega a cualquier borde
								enemiesBullet[i].lives = 0;
						}
						if (enemiesBullet[i].y > config->ground) {																										// Si llega al piso
								enemiesBullet[i].lives = 0;
								StartExplosions(explosions, enemiesBullet[i].x, enemiesBullet[i].y - 30, 0, config);
						}
						if(enemiesBullet[i].bulletImage == 0) {
								enemiesBullet[i].angle += 0.1;
								enemiesBullet[i].y += enemiesBullet[i].speed_y*2;
								enemiesBullet[i].speed_y += 0.05;
						}
				}
				i++;
		}
}

void Enemy_CollideBullet(EnemyBullet enemiesBullet[], Player *jugador, Explosion explosions[], CFG *config) {
		int i = 0;
		while (i < config->NUM_E_BULLETS) {
				if(enemiesBullet[i].lives > 0) {
					int j = 0;
					while (j < config->NUM_PLAYERS) {
						if(jugador[j].lives > 0) {
								if(enemiesBullet[i].x > (jugador[j].x - jugador[j].boundx*-(jugador[j].animationDirection-1)) && enemiesBullet[i].x < (jugador[j].x + jugador[j].boundx) && enemiesBullet[i].y > (jugador[j].y - jugador[j].boundy) && enemiesBullet[i].y < (jugador[j].y)) {
										// Si hay colision con un jugador
										enemiesBullet[i].lives--;
										jugador[j].lives--;
										StartExplosions(explosions, enemiesBullet[i].x, enemiesBullet[i].y - 20, 0, config);
								}
						}
						j++;
					}
				}
				i++;
		}
}










void BOSS_CollideBullet(struct BOSS *BOSS1,Player *jugador,CFG *config,Explosion explosions[]) {
int j = 0;
	while (j < config->NUM_PLAYERS) {
		if(jugador[j].lives > 0) {
			//printf("Boss X: %d - Jugador x: %f - jugador x + boundx: %f\n", BOSS1->BOSS_BULLET_X, jugador[j].x, jugador[j].x + jugador[j].boundx);
			//printf("Boss Y: %d - Jugador y: %f - jugador y + boundy: %f\n", BOSS1->y+53, jugador[j].y, jugador[j].y + jugador[j].boundy);
			//if(((BOSS1->BOSS_BULLET_X + BOSS1->BOSS_BULLET_W*2*BOSS1->dir) < (jugador[j].x - jugador[j].boundx*-(jugador[j].animationDirection-1)) &&  (BOSS1->BOSS_BULLET_X ) > (jugador[j].x + jugador[j].boundx) && (BOSS1->y +15) > (jugador[j].y - jugador[j].boundy) && (BOSS1->y +15) < (jugador[j].y))||( (BOSS1->BOSS_BULLET_X + BOSS1->BOSS_BULLET_W*2*BOSS1->dir)> (jugador[j].x - jugador[j].boundx*-(jugador[j].animationDirection-1)) &&  (BOSS1->BOSS_BULLET_X +50)< (jugador[j].x + jugador[j].boundx) && (BOSS1->y +15) > (jugador[j].y - jugador[j].boundy) && (BOSS1->y +15) < (jugador[j].y))) {
			if( (BOSS1->x + BOSS1->BOSS_BULLET_X > jugador[j].x) && (BOSS1->x + BOSS1->BOSS_BULLET_X < (jugador[j].x + jugador[j].boundx)) && (BOSS1->y+80> jugador[j].y) && (BOSS1->y+80 < (jugador[j].y + jugador[j].boundy))) {
				// Si hay colision con un jugador
				if (BOSS1->BOSS_BULLET_X) {
					jugador[j].lives--;StartExplosions(explosions, BOSS1->x + BOSS1->BOSS_BULLET_X , BOSS1->y, 0, config);
					BOSS1->BOSS_BULLET_X= -4000;
				}
			}
		}
		j++;
	}
}




void BOSS_CollideBullet2(struct BOSS *BOSS2,Player *jugador,CFG *config,Explosion explosions[]) {
int j = 0;
	while (j < config->NUM_PLAYERS) {
		if(jugador[j].lives > 0) {
			
			if( (BOSS2->x + BOSS2->BOSS_BULLET_X > jugador[j].x) && (BOSS2->x + BOSS2->BOSS_BULLET_X < (jugador[j].x + jugador[j].boundx)) && (BOSS2->y+80 > jugador[j].y) && (BOSS2->y+80 < (jugador[j].y + jugador[j].boundy))) {
				// Si hay colision con un jugador
				if (BOSS2->BOSS_BULLET_X) {
					jugador[j].lives--;
					StartExplosions(explosions, BOSS2->x + BOSS2->BOSS_BULLET_X , BOSS2->y, 0, config);
					BOSS2->BOSS_BULLET_X= -4000;
				}
			}
		}
		j++;
	}
}


void BOSS_CollideBullet3(struct BOSS *BOSS3,Player *jugador,CFG *config,Explosion explosions[]) {
int j = 0;
	while (j < config->NUM_PLAYERS) {
		if(jugador[j].lives > 0) {
			
			if( (BOSS3->x + BOSS3->BOSS_BULLET_X > jugador[j].x) && (BOSS3->x + BOSS3->BOSS_BULLET_X < (jugador[j].x + jugador[j].boundx)) && (BOSS3->y+80 > jugador[j].y) && (BOSS3->y+80 < (jugador[j].y + jugador[j].boundy))) {
				// Si hay colision con un jugador
				if (BOSS3->BOSS_BULLET_X) {
					jugador[j].lives--;
					StartExplosions(explosions, BOSS3->x + BOSS3->BOSS_BULLET_X , BOSS3->y, 0, config);
					BOSS3->BOSS_BULLET_X= -4000;
				}
			}
		}
		j++;
	}
}


void BOSS3_EXPLOTION(struct BOSS *BOSS3,Player *jugador,CFG *config) {
int j = 0;
	while (j < config->NUM_PLAYERS) {
		if(jugador[j].lives > 0) {
			
			if( (BOSS3->x + BOSS3->BOSS_EX_frameWidth +30 > jugador[j].x) && (BOSS3->x - BOSS3->BOSS_EX_frameWidth -30  < (jugador[j].x + jugador[j].boundx)) ){
				// Si hay colision con un jugador
				
					jugador[j].lives--;
					
			}
		}
		j++;
	}
}

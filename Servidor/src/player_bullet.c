#include "objects.h"
#include "prototypes.h"
void InitBullet(Bullet bullet[], ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *image2, ALLEGRO_SAMPLE *bulletSound, CFG *config) {
		int i = 0;
		while (i < config->NUM_BULLETS) {
				bullet[i].speed = 20;
				bullet[i].lives = 0;
				bullet[i].direction = 1;
				bullet[i].image = image;
				bullet[i].image2 = image2;
				bullet[i].bulletSound = bulletSound;
				i++;
		}
}

void DrawBullet(Bullet bullet[], CFG *config) {
		int i = 0;
		while (i < config->NUM_BULLETS) {
				if(bullet[i].lives > 0){
					if (!bullet[i].bulletImage) {
						al_draw_bitmap(bullet[i].image, bullet[i].x, bullet[i].y, 0);
					}
					else {
						al_draw_rotated_bitmap(bullet[i].image2, 5.5, 9, bullet[i].x, bullet[i].y, bullet[i].angle, (bullet[i].direction+1)/2); // La direccion vale 1 o -1, asi lo transformo a 1 y 0 (lo que necesito), respectivamente
					}
				}
				i++;
		}
}

void FireBullet(Bullet bullet[], Player jugador[], int bulletDirection, int bulletSelection, CFG *config, int nPlayer) {
		int i = 0;
		while (i < config->NUM_BULLETS) {
				if(bullet[i].lives <= 0) {
					bullet[i].speed_y = -2;
					bullet[i].angle = 0;
					bullet[i].player = nPlayer;
					if (!bulletSelection) {
						bullet[i].bulletImage = 0;
						jugador[nPlayer].maxFrame = 10;
						jugador[nPlayer].animationRow = 1;
						jugador[nPlayer].curFrame = 0;
						jugador[nPlayer].frameCount = 0;
						bullet[i].direction = bulletDirection;
						al_play_sample(bullet[i].bulletSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						bullet[i].x = jugador[nPlayer].x + jugador[nPlayer].frameWidth/2 * -(jugador[nPlayer].animationDirection - 1);
						bullet[i].y = jugador[nPlayer].y - jugador[nPlayer].frameHeight/1.75;
						bullet[i].lives = 1;
						break;
					}
					else {
						bullet[i].bulletImage = 1;
						jugador[nPlayer].maxFrame = 5;
						jugador[nPlayer].animationRow = 2;
						jugador[nPlayer].curFrame = 0;
						jugador[nPlayer].frameCount = 0;
						bullet[i].direction = bulletDirection;
						bullet[i].x = jugador[nPlayer].x + jugador[nPlayer].frameWidth/2 * -(jugador[nPlayer].animationDirection - 1);
						bullet[i].y = jugador[nPlayer].y - jugador[nPlayer].frameHeight;
						bullet[i].lives = 1;
						break;
					}
				}
				i++;
		}
}

void UpdateBullet(Bullet bullet[], Explosion explosions[], CFG *config) {
		int i = 0;
		while (i < config->NUM_BULLETS) {
				if(bullet[i].lives > 0) {
					if (bullet[i].bulletImage) {
						bullet[i].angle += 0.1;
						bullet[i].y += bullet[i].speed_y*2;
						bullet[i].speed_y += 0.2;
						bullet[i].x += (bullet[i].speed/2) * bullet[i].direction;
					}
					else {
						bullet[i].x += (bullet[i].speed) * bullet[i].direction;
					}
					if(bullet[i].x > config->SCREEN_W || bullet[i].x <0) {														// Si la bala llega a cualquier borde
							bullet[i].lives = 0;
					}
					else if (bullet[i].y > config->ground) {
						StartExplosions(explosions, bullet[i].x, bullet[i].y, 1, config);
						bullet[i].lives = 0;
					}
				}
				i++;
		}
}

void CollideBullet(Bullet bullet[], Enemy enemies[], Player jugador[], EnemyDead enemiesDead[], Explosion explosions[], CFG *config) {
		int i = 0;
		int col = 0;
		while (i < config->NUM_BULLETS) {
				if(bullet[i].lives > 0) {
						int j = 0;
						while (j < config->NUM_ENEMIES) {
								if(enemies[j].lives > 0) {
									if(bullet[i].x > (enemies[j].x - enemies[j].boundx*enemies[j].animationDirection) && bullet[i].x < (enemies[j].x + enemies[j].boundx) && bullet[i].y > (enemies[j].y - enemies[j].boundy) && bullet[i].y < enemies[j].y) {
										// Si hay colision con un enemigo
										bullet[i].lives--;
										if (bullet[i].bulletImage){																							// Si es una granada
											enemies[j].lives -= 2;																								// La granada hace doble daño
											col = 1;
										}
										else {																																	// Si es una bala
											enemies[j].lives--;
										}
											if (enemies[j].lives <= 0) {																					// Si el enemigo "muere"
												jugador[bullet[i].player].score++;
												StartEnemyDead(enemiesDead, enemies, j, config);
										}
										if (!bullet[i].bulletImage) {																						// Si es una bala
											break;																																// La bala colisiona con un solo enemigo y la granada en "area"
										}
									}
								}
								j++;
								if (col && j == config->NUM_ENEMIES) {																			// Si la granada ya colisiono con todos los enemigos en esa posicion
									StartExplosions(explosions, bullet[i].x, bullet[i].y, 1, config);
									col = 0;
								}
						}
				}
				i++;
		}
}




void Boss_colision(struct BOSS *BOSS1,Player jugador[],Bullet bullet[], CFG *config,Explosion explosions[]) {
	float dmg=0.03;
	int i=0;
		while (i < config->NUM_BULLETS) {
			if(bullet[i].lives > 0) {
				if(bullet[i].x > (BOSS1->x- BOSS1->BOSS_frameWidth+70) && bullet[i].x < (BOSS1->x + BOSS1->BOSS_frameWidth) && bullet[i].y > (BOSS1->y- BOSS1->BOSS_frameHeight) && bullet[i].y < BOSS1->y +30) {
				// Si hay colision con BOSS
					if (bullet[i].bulletImage){		// Si es una granada
						BOSS1->damage+=	dmg;				//granada
						StartExplosions(explosions, bullet[i].x, bullet[i].y+30, 1, config);
					}
					else {
						BOSS1->damage+=	dmg/2;			//bala
					
					}
				bullet[i].lives = 0;
				}
			}
			i++;
		}
}



void Boss_colision2(struct BOSS *BOSS2,Player jugador[],Bullet bullet[], CFG *config,Explosion explosions[]) {
	float dmg=0.02;
	int i=0;
		while (i < config->NUM_BULLETS) {
			if(bullet[i].lives > 0) {
				if(bullet[i].x > (BOSS2->x - BOSS2->BOSS_frameWidth+200) && bullet[i].x < (BOSS2->x + BOSS2->BOSS_frameWidth) && bullet[i].y < (BOSS2->y+ BOSS2->BOSS_frameHeight) && bullet[i].y > BOSS2->y ) {
				// Si hay colision con BOSS
					if (bullet[i].bulletImage){		// Si es una granada
						BOSS2->damage+=	dmg;		//granada
						StartExplosions(explosions, bullet[i].x, bullet[i].y+30, 1, config);
					}
					else {
						BOSS2->damage+=	dmg/2;			//bala
					}
				bullet[i].lives = 0;
				}
			}
			i++;
		}
}


void Boss_colision3(struct BOSS *BOSS3,Player jugador[],Bullet bullet[], CFG *config,Explosion explosions[]) {
	float dmg=0.02;
	int i=0;
		while (i < config->NUM_BULLETS) {
			if(bullet[i].lives > 0) {
				if(bullet[i].x > (BOSS3->x - BOSS3->BOSS_frameWidth) && bullet[i].x < (BOSS3->x + BOSS3->BOSS_frameWidth) && bullet[i].y < (BOSS3->y+ BOSS3->BOSS_frameHeight) && bullet[i].y > BOSS3->y ) {
				// Si hay colision con BOSS
					if (bullet[i].bulletImage){		// Si es una granada
						BOSS3->damage+=	dmg;		//granada
						StartExplosions(explosions, bullet[i].x, bullet[i].y+30, 1, config);
					}
					else {
						BOSS3->damage+=	dmg/2;			//bala
					}
					
				bullet[i].lives = 0;
				}
			}
			i++;
		}
}

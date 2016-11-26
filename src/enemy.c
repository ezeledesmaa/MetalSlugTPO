#include "objects.h"
#include "prototypes.h"
void InitEnemy(Enemy enemies[], ALLEGRO_BITMAP *image, CFG *config) {
		int i = 0;
		while (i < config->NUM_ENEMIES) {
				enemies[i].lives = 0;
				enemies[i].speed = 3;
				enemies[i].boundx = 30;
				enemies[i].boundy = 40;

				enemies[i].maxFrame = 12;
				enemies[i].curFrame = 0;
				enemies[i].frameCount = 0;
				enemies[i].frameDelay = 4;
				enemies[i].frameWidth = 40;
				enemies[i].frameHeight = 50;
				enemies[i].animationRow = 1;

				enemies[i].ajuste = 40;																														// Ajuste para cuando dispara (el frame es mas largo)
				enemies[i].action = 0;
				enemies[i].image = image;
				i++;
		}
}

void InitEnemy_LEVEL2(Enemy enemies[], ALLEGRO_BITMAP *image, CFG *config) {
		int i = 0;
		while (i < config->NUM_ENEMIES) {
				enemies[i].lives = 0;
				enemies[i].ajuste = 30;																														// Ajuste para cuando dispara (el frame es mas largo)
				enemies[i].action = 0;
				enemies[i].image = image;
				i++;
		}
}


void DrawEnemy(Enemy enemies[], CFG *config) {
		int i = 0;
		int fx;
		int fy;
		while (i < config->NUM_ENEMIES) {
				if(enemies[i].lives > 0) {
						if ((enemies[i].animationRow == 2 || enemies[i].animationRow == 3) && enemies[i].animationDirection) {
							fx = enemies[i].curFrame * enemies[i].frameWidth - enemies[i].ajuste;
						}
						else {
							fx = enemies[i].curFrame * enemies[i].frameWidth;
						}
						fy = enemies[i].animationRow * enemies[i].frameHeight;
						al_draw_bitmap_region(enemies[i].image, fx, fy, enemies[i].frameWidth, enemies[i].frameHeight, enemies[i].x, enemies[i].y - enemies[i].frameHeight, enemies[i].animationDirection);
				}
				i++;
		}
}

void StartEnemy(Enemy enemies[], CFG *config) {
		int i = 0;
		while (i < config->NUM_ENEMIES && config->FONDO_X > 0) {
				if(enemies[i].lives <= 0) {
						if(rand() % 200 == 0) {
								enemies[i].lives = 2;
								if(rand() % 2) {
										enemies[i].animationDirection = 0;																			// 0 es mirando hacia la izquierda (al reves de los demas sprites)
								}
								else {
										enemies[i].animationDirection = 1;																			// 1 es mirando hacia la derecha
								}
								if (!enemies[i].animationDirection) {
										enemies[i].x = config->SCREEN_W;
								}
								else {
										enemies[i].x = -enemies[i].frameWidth;
								}
								enemies[i].y = config->ground;
								break;
						}
				}
				i++;
		}
}

void UpdateEnemy(Enemy enemies[], Player jugador[], EnemyBullet enemiesBullet[], CFG *config) {
		int i = 0;
		while (i < config->NUM_ENEMIES) {
				if(enemies[i].lives > 0) {
						enemies[i].frameCount++;
						if(enemies[i].frameCount >= enemies[i].frameDelay) {
								enemies[i].curFrame++;
								enemies[i].frameCount = 0;
								if(enemies[i].curFrame >= enemies[i].maxFrame) {
										if (enemies[i].animationRow == 2 || enemies[i].animationRow == 3) {
												if (enemies[i].animationDirection == 0) {
														Enemy_FireBullet(enemiesBullet, enemies, i, -1, config);
												}
												else {
														Enemy_FireBullet(enemiesBullet, enemies, i, 1, config);
												}
										}
										enemies[i].speed = 3;
										enemies[i].maxFrame = 12;
										enemies[i].curFrame = 0;
										enemies[i].frameCount = 0;
										enemies[i].frameDelay = 4;
										enemies[i].frameWidth = 40;
										enemies[i].frameHeight = 50;
										enemies[i].animationRow = 1;
										enemies[i].action = 0;
								}
						}
						/**Inteligencia artificial del enemigo*/
						if (jugador[0].lives > 0) {
							if ((jugador[0].x - enemies[i].x) < 0) {																						// Si esta a la derecha del jugador 1
								enemies[i].x -= enemies[i].speed;
								enemies[i].animationDirection = 0;
							}
							else if ((jugador[0].x - enemies[i].x) > 0) {
								enemies[i].x += enemies[i].speed;
								enemies[i].animationDirection = 1;
							}
						}
						else if (jugador[1].lives > 0 && config->NUM_PLAYERS > 1) {
							if ((jugador[1].x - enemies[i].x) < 0) {																						// Si esta a la derecha del jugador 2
								enemies[i].x -= enemies[i].speed;
								enemies[i].animationDirection = 0;
							}
							else if ((jugador[1].x - enemies[i].x) > 0) {
								enemies[i].x += enemies[i].speed;
								enemies[i].animationDirection = 1;
							}
						}

						else {                                                                                                                                                      // Aca iria el cuchillo?
										enemies[i].speed = 0;
										enemies[i].frameDelay = 6;
										enemies[i].maxFrame = 14;
										enemies[i].curFrame = 0;
										enemies[i].frameCount = 0;
										enemies[i].animationRow = 0;
										enemies[i].frameWidth = 40;
										enemies[i].action = 1;
						}
						if (!enemies[i].action) {																												// Si no se esta haciendo ninguna accion
								if (rand() % 500 == 1) {
										enemies[i].speed = 0;
										enemies[i].frameDelay = 6;
										enemies[i].maxFrame = 11;
										enemies[i].curFrame = 0;
										enemies[i].frameCount = 0;
										enemies[i].animationRow = 3;
										enemies[i].frameWidth = 80;
										enemies[i].action = 1;
								}
								else if (rand() % 500 == 2) {
										enemies[i].speed = 0;
										enemies[i].frameDelay = 6;
										enemies[i].maxFrame = 11;
										enemies[i].curFrame = 0;
										enemies[i].frameCount = 0;
										enemies[i].animationRow = 2;
										enemies[i].frameWidth = 80;
										enemies[i].action = 1;
								}
								else if (rand() % 100 == 0) {
										enemies[i].speed = 0;
										enemies[i].frameDelay = 6;
										enemies[i].maxFrame = 14;
										enemies[i].curFrame = 0;
										enemies[i].frameCount = 0;
										enemies[i].animationRow = 0;
										enemies[i].frameWidth = 40;
										enemies[i].action = 1;
								}
						}
				}
				i++;
		}
}


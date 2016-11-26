#include "objects.h"
void InitEnemyDead(EnemyDead enemiesDead[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound, CFG *config) {
		int i = 0;
		while (i < config->NUM_ENEMIESDEAD){
				enemiesDead[i].lives = 0;
				enemiesDead[i].maxFrame = 15;
				enemiesDead[i].curFrame = 0;
				enemiesDead[i].frameCount = 0;
				enemiesDead[i].frameDelay = 2;
				enemiesDead[i].frameWidth = 80;
				enemiesDead[i].frameHeight = 50;
				enemiesDead[i].animationRow = 4;
				enemiesDead[i].animationDirection = 0;
				enemiesDead[i].image = image;
				enemiesDead[i].sound = sound;
				i++;
		}
}

void InitEnemyDead_LEVEL2(EnemyDead enemiesDead[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound, CFG *config) {
		int i = 0;
		while (i < config->NUM_ENEMIESDEAD){
				enemiesDead[i].lives = 0;
				enemiesDead[i].animationDirection = 0;
				enemiesDead[i].image = image;
				enemiesDead[i].sound = sound;
				i++;
		}
}

void DrawEnemyDead(EnemyDead enemiesDead[], CFG *config) {
		int i = 0;
		while (i < config->NUM_ENEMIESDEAD) {
				if(enemiesDead[i].lives > 0) {
						int fx = enemiesDead[i].curFrame * enemiesDead[i].frameWidth;
						int fy = enemiesDead[i].animationRow * enemiesDead[i].frameHeight;
						al_draw_bitmap_region(enemiesDead[i].image, fx, fy, enemiesDead[i].frameWidth, enemiesDead[i].frameHeight, enemiesDead[i].x, enemiesDead[i].y, enemiesDead[i].animationDirection);
				}
				i++;
		}
}

void StartEnemyDead(EnemyDead enemiesDead[], Enemy enemies[], int j, CFG *config) {
		int i = 0;
		while (i < config->NUM_ENEMIESDEAD) {
				if(enemiesDead[i].lives <= 0) {
						enemiesDead[i].lives = 1;
						enemiesDead[i].x = enemies[j].x - enemies[j].ajuste/2;													// -20 porque el frame esta corrido 20 pixeles
						enemiesDead[i].y = enemies[j].y - enemies[j].frameHeight;
						enemiesDead[i].animationDirection = enemies[j].animationDirection;
						al_play_sample(enemiesDead[i].sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
				}
				i++;
		}
}

void UpdateEnemyDead(EnemyDead enemiesDead[], CFG *config) {
		int i = 0;
		while (i < config->NUM_ENEMIESDEAD) {
				if(enemiesDead[i].lives > 0) {
						enemiesDead[i].frameCount++;
						if(enemiesDead[i].frameCount >= enemiesDead[i].frameDelay) {
								enemiesDead[i].curFrame++;
								enemiesDead[i].frameCount = 0;
								if(enemiesDead[i].curFrame >= enemiesDead[i].maxFrame) {
										enemiesDead[i].curFrame = 0;
										enemiesDead[i].lives = 0;
								}
						}
				}
				i++;
		}
}

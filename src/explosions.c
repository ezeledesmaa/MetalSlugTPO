#include "objects.h"
void InitExplosions(Explosion explosions[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound, CFG *config) {
		int i = 0;
		while (i < config->NUM_EXPLOSIONS) {
				explosions[i].lives = 0;
				explosions[i].maxFrame = 8;
				explosions[i].curFrame = 0;
				explosions[i].frameCount = 0;
				explosions[i].frameDelay = 2;
				explosions[i].frameWidth = 40;
				explosions[i].frameHeight = 50;
				explosions[i].animationRow = 0;
				explosions[i].image = image;
				explosions[i].sound = sound;
				i++;
		}
}

void DrawExplosions(Explosion explosions[], CFG *config) {
		int i = 0;
		while (i < config->NUM_EXPLOSIONS) {
				if(explosions[i].lives > 0) {
						int fx = explosions[i].curFrame * explosions[i].frameWidth;
						int fy = explosions[i].animationRow * explosions[i].frameHeight;
						if (!explosions[i].animationRow) {
							al_draw_bitmap_region(explosions[i].image, fx, fy, explosions[i].frameWidth, explosions[i].frameHeight, explosions[i].x, explosions[i].y, 0);
						}
						else {
							al_draw_bitmap_region(explosions[i].image, fx, fy, explosions[i].frameWidth, explosions[i].frameHeight*3, explosions[i].x - explosions[i].frameWidth/2, explosions[i].y-explosions[i].frameHeight*2, 0);
						}

				}
				i++;
		}
}

void StartExplosions(Explosion explosions[], int x, int y, int selection, CFG *config) {
		int i = 0;
		while (i < config->NUM_EXPLOSIONS) {
				if(explosions[i].lives <= 0) {
					if (!selection) {
						explosions[i].maxFrame = 8;
						explosions[i].curFrame = 0;
						explosions[i].frameCount = 0;
						explosions[i].frameDelay = 2;
						explosions[i].frameWidth = 40;
						explosions[i].frameHeight = 50;
						explosions[i].animationRow = 0;
					}
					else {
						explosions[i].maxFrame = 27;
						explosions[i].curFrame = 0;
						explosions[i].frameCount = 0;
						explosions[i].frameDelay = 2;
						explosions[i].frameWidth = 80;
						explosions[i].frameHeight = 50;
						explosions[i].animationRow = 1;
					}
					explosions[i].lives = 1;
					explosions[i].x = x;
					explosions[i].y = y;
					al_play_sample(explosions[i].sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				}
				i++;
		}
}

void UpdateExplosions(Explosion explosions[], CFG *config) {
		int i = 0;
		while (i < config->NUM_EXPLOSIONS) {
				if(explosions[i].lives > 0) {
						explosions[i].frameCount++;
						if(explosions[i].frameCount >= explosions[i].frameDelay) {
								explosions[i].curFrame++;
								explosions[i].frameCount = 0;
								if(explosions[i].curFrame >= explosions[i].maxFrame) {
										explosions[i].curFrame = 0;
										explosions[i].lives = 0;
								}
						}
				}
				i++;
		}
}

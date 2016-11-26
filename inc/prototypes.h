void InitPlayer(Player jugador[], ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *image2, ALLEGRO_BITMAP *foot_image, int selectImage, CFG *config);
void UpdatePlayer(Player jugador[], CFG *config);
void DrawPlayer(Player jugador[], CFG *config);
void MovePlayerLeft(Player jugador[], int nPlayer, CFG *config);
void MovePlayerRight(Player jugador[], int nPlayer, EnemyDead enemiesDead[], CFG *config, Enemy enemies[]);

void InitBullet(Bullet bullet[], ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *image2, ALLEGRO_SAMPLE *bulletSound, CFG *config);
void DrawBullet(Bullet bullet[], CFG *config);
void FireBullet(Bullet bullet[], Player jugador[], int bulletDirection, int bulletSelection, CFG *config, int nPlayer);
void UpdateBullet(Bullet bullet[], Explosion explosions[], CFG *config);
void CollideBullet(Bullet bullet[], Enemy enemies[], Player jugador[], EnemyDead enemiesDead[], Explosion explosions[], CFG *config);

void InitEnemy(Enemy enemies[], ALLEGRO_BITMAP *image, CFG *config);
void InitEnemy_LEVEL2(Enemy enemies[], ALLEGRO_BITMAP *image, CFG *config);
void DrawEnemy(Enemy enemies[], CFG *config);
void StartEnemy(Enemy enemies[], CFG *config);
void UpdateEnemy(Enemy enemies[], Player jugador[], EnemyBullet enemiesBullet[], CFG *config);

void InitEnemyDead(EnemyDead enemiesDead[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound, CFG *config);
void InitEnemyDead_LEVEL2(EnemyDead enemiesDead[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound, CFG *config);
void DrawEnemyDead(EnemyDead enemiesDead[], CFG *config);
void StartEnemyDead(EnemyDead enemiesDead[], Enemy enemies[], int jsize, CFG *config);
void UpdateEnemyDead(EnemyDead enemiesDead[], CFG *config);

void Enemy_InitBullet(EnemyBullet enemiesBullet[], ALLEGRO_BITMAP *image1, ALLEGRO_BITMAP *image2, CFG *config);
void Enemy_InitBullet_LEVEL2(EnemyBullet enemiesBullet[], ALLEGRO_BITMAP *image1, ALLEGRO_BITMAP *image2, CFG *config);
void Enemy_DrawBullet(EnemyBullet enemiesBullet[], CFG *config);
void Enemy_FireBullet(EnemyBullet enemiesBullet[], Enemy enemies[], int eNum, int Enemy_bulletDirection, CFG *config);
void Enemy_UpdateBullet(EnemyBullet enemiesBullet[], Explosion explosions[], CFG *config);
void Enemy_CollideBullet(EnemyBullet enemiesBullet[], Player jugador[], Explosion explosions[], CFG *config);

void InitExplosions(Explosion explosions[], ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sound, CFG *config);
void DrawExplosions(Explosion explosions[], CFG *config);
void StartExplosions(Explosion explosions[], int x, int y, int selection, CFG *config);
void UpdateExplosions(Explosion explosions[], CFG *config);

// Server
void error(const char *msg);
int get_network_data(int sockfd, char *buffer, int *s, int *k);
void InitServer(CFG *config, ALLEGRO_FONT	*font, int *sockfd, int *newsockfd);

// Listas
int agregarDatos (Lista **p, Score *jugador);
void imprimirDatos(Lista **p, ALLEGRO_FONT *font, CFG *config);
void eliminarDatos(Lista **p);
int cargarDatos(Lista **p);
int guardarDatos(Lista **p);

// Main
int title_screen(CFG *config, ALV *ALVAR);
int menu_screen(CFG *config, ALV *ALVAR, Lista *p);
int selection_screen (ALV *ALVAR);
int gameLoop (CFG *config, ALV *ALVAR, Lista *p);
void alvar_free(ALV *ALVAR);

// Juan
int selectName (char Name[], ALLEGRO_DISPLAY *display,  ALLEGRO_FONT *font, CFG *config);
void InitBoss(struct BOSS *BOSS1,CFG *config);
void DrawBOSS1(struct BOSS *BOSS1,int FPS, int MY_TIME,Player jugador[]);
void DrawBOSS2(struct BOSS *BOSS2,int FPS, int MY_TIME,Player jugador[]);
void DrawBOSS3(struct BOSS *BOSS3,int FPS, int MY_TIME,Player jugador[],CFG *config);
int colision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h);
void DrawBOSS1_VIDA(struct BOSS *BOSS1,ALLEGRO_FONT *font);
void DrawBOSS2_VIDA(struct BOSS *BOSS1,ALLEGRO_FONT *font);
void Boss_colision(struct BOSS *BOSS1,Player jugador[],Bullet bullet[], CFG *config,Explosion explosions[]);
void Boss_colision2(struct BOSS *BOSS2,Player jugador[],Bullet bullet[], CFG *config,Explosion explosions[]);
void Boss_colision3(struct BOSS *BOSS3,Player jugador[],Bullet bullet[], CFG *config,Explosion explosions[]);
void DrawBOSS1_DEAD(struct BOSS *BOSS1);
void DrawBOSS2_DEAD(struct BOSS *BOSS2);
void DrawBOSS3_DEAD(struct BOSS *BOSS3);

void BOSS_CollideBullet(struct BOSS *BOSS1,Player *jugador,CFG *config,Explosion explosions[]);
void BOSS_CollideBullet2(struct BOSS *BOSS2,Player *jugador,CFG *config,Explosion explosions[]);
void BOSS_CollideBullet3(struct BOSS *BOSS3,Player *jugador,CFG *config,Explosion explosions[]);
void DrawBOSS1_DEAD(struct BOSS *BOSS1);
void BOSS3_EXPLOTION(struct BOSS *BOSS3,Player *jugador,CFG *config);
//cargar NIVELES
void INI_LEVEL_2(Player jugador[],CFG *config);
void Nivel_3();
void INI_LEVEL(CFG *config);

// AL_INIT
int AL_INIT (CFG *config, ALV *ALVAR);

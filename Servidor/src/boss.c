#include "objects.h"
#include "prototypes.h"

//BOSES

void InitBoss(struct BOSS *BOSS1,CFG *config)
{
BOSS1->x=config->SCREEN_W -100;
BOSS1->y=config->SCREEN_H / 2 +15 ;
BOSS1->BOSS_TIMER=0;
BOSS1->damage=0;

BOSS1->BOSS_maxFrame = 5;
BOSS1->BOSS_curFrame = 0;
BOSS1->BOSS_frameCount = 0;
BOSS1->BOSS_frameDelay = 6;
BOSS1->BOSS_frameWidth = 86;
BOSS1->BOSS_frameHeight = 53;

BOSS1->BOSS_RUN_maxFrame = 5;
BOSS1->BOSS_RUN_curFrame = 0;
BOSS1->BOSS_RUN_frameCount = 0;
BOSS1->BOSS_RUN_frameDelay = 4;
BOSS1->BOSS_RUN_frameWidth = 84;
BOSS1->BOSS_RUN_frameHeight = 53;

BOSS1->BOSS_FIRE_maxFrame = 4;
BOSS1->BOSS_FIRE_curFrame = 0;
BOSS1->BOSS_FIRE_frameCount = 0;
BOSS1->BOSS_FIRE_frameDelay = 7;
BOSS1->BOSS_FIRE_frameWidth = 130;
BOSS1->BOSS_FIRE_frameHeight = 69;
BOSS1->BOSS_BULLET_SPEED=15	;
BOSS1->BOSS_SPEED=10;
BOSS1->BOSS_BULLET_W=50;
BOSS1->BOSS_BULLET_H=18;
BOSS1->VIDA_ANCHO=100;
BOSS1->VIDA_ALTO=50;
BOSS1->dir=1;
BOSS1->state=0;//el boss esta vivo
BOSS1->music_1=0;
}

void InitBoss2(struct BOSS *BOSS2,CFG *config)
{
BOSS2->x=config->SCREEN_W -200;
BOSS2->y=config->SCREEN_H -150;
BOSS2->BOSS_TIMER=0;
BOSS2->damage=0;

BOSS2->BOSS_maxFrame = 4;
BOSS2->BOSS_curFrame = 0;
BOSS2->BOSS_frameCount = 0;
BOSS2->BOSS_frameDelay = 3;
BOSS2->BOSS_frameWidth = 178;
BOSS2->BOSS_frameHeight = 151;

BOSS2->BOSS_FIRE_maxFrame = 4;
BOSS2->BOSS_FIRE_curFrame = 0;
BOSS2->BOSS_FIRE_frameCount = 0;
BOSS2->BOSS_FIRE_frameDelay = 7;
BOSS2->BOSS_FIRE_frameWidth = 176;
BOSS2->BOSS_FIRE_frameHeight = 151;	

BOSS2->BOSS_BULLET_SPEED=15	;
BOSS2->BOSS_SPEED=10;
BOSS2->BOSS_BULLET_Y=BOSS2->BOSS_frameHeight-50;
BOSS2->BOSS_BULLET_X=BOSS2->x-300;
BOSS2->BOSS_BULLET_W=50;
BOSS2->BOSS_BULLET_H=18;
BOSS2->VIDA_ANCHO=100;
BOSS2->VIDA_ALTO=50;
BOSS2->dir=1;
BOSS2->state=0;//el boss esta vivo
BOSS2->music_1=0;
}

void InitBoss3(struct BOSS *BOSS3,CFG *config)
{
BOSS3->x=config->SCREEN_W -200;
BOSS3->y=config->SCREEN_H / 2 +15 ;
BOSS3->BOSS_TIMER=0;
BOSS3->damage=0;

BOSS3->BOSS_maxFrame = 7;
BOSS3->BOSS_curFrame = 0;
BOSS3->BOSS_frameCount = 0;
BOSS3->BOSS_frameDelay = 5;
BOSS3->BOSS_frameWidth = 70;
BOSS3->BOSS_frameHeight = 61;

BOSS3->BOSS_RUN_maxFrame = 1;
BOSS3->BOSS_RUN_curFrame = 0;
BOSS3->BOSS_RUN_frameCount = 0;
BOSS3->BOSS_RUN_frameDelay = 5;
BOSS3->BOSS_RUN_frameWidth = 66;
BOSS3->BOSS_RUN_frameHeight = 61;

BOSS3->BOSS_FIRE_maxFrame = 10;
BOSS3->BOSS_FIRE_curFrame = 0;
BOSS3->BOSS_FIRE_frameCount = 0;
BOSS3->BOSS_FIRE_frameDelay = 5;
BOSS3->BOSS_FIRE_frameWidth = 100;
BOSS3->BOSS_FIRE_frameHeight = 100;

BOSS3->BOSS_EX_maxFrame = 5;
BOSS3->BOSS_EX_curFrame = 0;
BOSS3->BOSS_EX_frameCount = 0;
BOSS3->BOSS_EX_frameDelay = 5;
BOSS3->BOSS_EX_frameWidth = 107;
BOSS3->BOSS_EX_frameHeight = 123;



BOSS3->BOSS_BULLET_SPEED=8	;
BOSS3->BOSS_SPEED=10;
BOSS3->BOSS_BULLET_W=46;
BOSS3->BOSS_BULLET_H=36;
BOSS3->VIDA_ANCHO=100;
BOSS3->VIDA_ALTO=50;
BOSS3->dir=1;
BOSS3->state=0;//el boss esta vivo
BOSS3->music_1=0;



}

void DrawBOSS1(struct BOSS *BOSS1,int FPS, int MY_TIME,Player jugador[])
{
	
	BOSS1->dir=1;
			if(++BOSS1->BOSS_frameCount >=   BOSS1->BOSS_frameDelay)
			{
				if(++BOSS1->BOSS_curFrame >= BOSS1->BOSS_maxFrame)
					BOSS1->BOSS_curFrame = 0;

				BOSS1->BOSS_frameCount = 0;
			}

if(BOSS1->damage<=1)
{//si el vos esta vivo

if(++BOSS1->BOSS_RUN_frameCount >= BOSS1->BOSS_RUN_frameDelay)
			{
				if(++BOSS1->BOSS_RUN_curFrame >= BOSS1->BOSS_RUN_maxFrame)
					BOSS1->BOSS_RUN_curFrame = 0;

				BOSS1->BOSS_RUN_frameCount = 0;
			}


			if(++BOSS1->BOSS_FIRE_frameCount >= BOSS1->BOSS_FIRE_frameDelay)
			{
				if(++BOSS1->BOSS_FIRE_curFrame >= BOSS1->BOSS_FIRE_maxFrame)
					BOSS1->BOSS_FIRE_curFrame = 0;

				BOSS1->BOSS_FIRE_frameCount = 0;
			}


		 // acciones del boss
			if(MY_TIME>=0 && MY_TIME<2*FPS)// 2 SEGUNDOS
			{
				// Boss parado mirando a la izq
			BOSS1->BOSS_BULLET_X=0;
			al_draw_bitmap_region(BOSS1->BOSS_STAND, BOSS1->BOSS_curFrame * BOSS1->BOSS_frameWidth, 0, BOSS1->BOSS_frameWidth, BOSS1->BOSS_frameHeight, BOSS1->x, BOSS1->y, 1);
			return ;
		}

	if(MY_TIME>=2*FPS && MY_TIME<3*FPS)// 1 SEGUNDO
	{
		// Boss CORRE A LA IZQ
		BOSS1->BOSS_BULLET_X=0;
		BOSS1->x-=BOSS1->BOSS_SPEED;
		al_draw_bitmap_region(BOSS1->BOSS_RUN, BOSS1->BOSS_RUN_curFrame * BOSS1->BOSS_RUN_frameWidth, 0, BOSS1->BOSS_RUN_frameWidth, BOSS1->BOSS_RUN_frameHeight, BOSS1->x, BOSS1->y, 1);
		return ;

	}


	if(MY_TIME>=3*FPS && MY_TIME<=5*FPS)// 2 SEGUNDOS
	{
	 // Boss parado mirando a la derecha
	BOSS1->BOSS_BULLET_X=0;
	al_draw_bitmap_region(BOSS1->BOSS_STAND, BOSS1->BOSS_curFrame * BOSS1->BOSS_frameWidth, 0, BOSS1->BOSS_frameWidth, BOSS1->BOSS_frameHeight, BOSS1->x, BOSS1->y, 0);
	return ;

	}

	if(MY_TIME>=5*FPS && MY_TIME<=6*FPS)// 1 SEGUNDO
	{
		//BOSS DISPARA HACIA LA DERECHA
		BOSS1->dir=1;
			BOSS1->BOSS_BULLET_X+=BOSS1->BOSS_BULLET_SPEED*BOSS1->dir;
			al_draw_bitmap_region(BOSS1->BOSS_FIRE, BOSS1->BOSS_FIRE_curFrame * BOSS1->BOSS_FIRE_frameWidth, 0, BOSS1->BOSS_FIRE_frameWidth, BOSS1->BOSS_FIRE_frameHeight, BOSS1->x-40, BOSS1->y -20, 0);
			al_draw_bitmap(BOSS1->BOSS_BULLET, BOSS1->x + BOSS1->BOSS_BULLET_X  ,BOSS1->y +15, 1);

		return ;

	}

	if(MY_TIME>=6*FPS && MY_TIME<=7*FPS)// 1 SEGUNDO
	{
	 // boss corre hacia la derecha

		BOSS1->BOSS_BULLET_X=0;
		BOSS1->x+=BOSS1->BOSS_SPEED;
		al_draw_bitmap_region(BOSS1->BOSS_RUN, BOSS1->BOSS_RUN_curFrame * BOSS1->BOSS_RUN_frameWidth, 0, BOSS1->BOSS_RUN_frameWidth, BOSS1->BOSS_RUN_frameHeight, BOSS1->x, BOSS1->y, 0);

		return ;

	}

	if(MY_TIME>=7*FPS && MY_TIME<=8*FPS)// 1 SEGUNDO
	{
	BOSS1->BOSS_BULLET_X=0;
	al_draw_bitmap_region(BOSS1->BOSS_STAND, BOSS1->BOSS_curFrame * BOSS1->BOSS_frameWidth, 0, BOSS1->BOSS_frameWidth, BOSS1->BOSS_frameHeight, BOSS1->x, BOSS1->y, 1);
	return ; // Boss mira a la izq

	}

	if(MY_TIME>=8*FPS && MY_TIME<=10*FPS)// 1 SEGUNDO
	{
			 // boss dispara hacia la izq
			 BOSS1->dir=-1;
			BOSS1->BOSS_BULLET_X+=BOSS1->BOSS_BULLET_SPEED*BOSS1->dir;
			al_draw_bitmap_region(BOSS1->BOSS_FIRE, BOSS1->BOSS_FIRE_curFrame * BOSS1->BOSS_FIRE_frameWidth, 0, BOSS1->BOSS_FIRE_frameWidth, BOSS1->BOSS_FIRE_frameHeight, BOSS1->x-40, BOSS1->y -20, 1);
			al_draw_bitmap(BOSS1->BOSS_BULLET, BOSS1->x + BOSS1->BOSS_BULLET_X  ,BOSS1->y +15, 0);
		return ;

	}

}//	si el boss esta vivo

if(BOSS1->damage>=1)
{
	if(BOSS1->state==0)
	{
	BOSS1->state=1;
	jugador[0].score = jugador[0].score+100;
	jugador[1].score = jugador[1].score+100;
}
DrawBOSS1_DEAD(BOSS1);
}

	}


void DrawBOSS1_VIDA(struct BOSS *BOSS1,ALLEGRO_FONT *font)
{

//fprintf( stdout, "%f\n",BOSS1->damage ); //descomentar para debug
	if(((BOSS1->VIDA_ANCHO)-(BOSS1->VIDA_ANCHO*BOSS1->damage))>=0)//si la vida es menor a cero desaparece la barra y el texto
	{
	if(((BOSS1->VIDA_ANCHO)-(BOSS1->VIDA_ANCHO*BOSS1->damage))>=50)//Verde
{

	al_draw_tinted_scaled_bitmap(BOSS1->VIDA,al_map_rgba_f(0,1, 0, 1),0,0,BOSS1->VIDA_ANCHO,BOSS1->VIDA_ALTO,600,40,(BOSS1->VIDA_ANCHO)-(BOSS1->VIDA_ANCHO)*(BOSS1->damage),BOSS1->VIDA_ALTO/2,1);
}

else//ROJO
{
al_draw_tinted_scaled_bitmap(BOSS1->VIDA,al_map_rgba_f(1,0, 0, 1),0,0,BOSS1->VIDA_ANCHO,BOSS1->VIDA_ALTO,600,40,(BOSS1->VIDA_ANCHO)-(BOSS1->VIDA_ANCHO)*(BOSS1->damage),BOSS1->VIDA_ALTO/2,0);
}
al_draw_textf(font, al_map_rgb(0, 0, 255), 600, 20, 0, "BOSS:");
}



}

void DrawBOSS1_DEAD(struct BOSS *BOSS1)
{
	
	al_draw_bitmap(BOSS1->MISSION_COMPLETE,700/2 ,224/10, 0);
	if(BOSS1->music_1==0)
	{
	al_stop_samples();
	al_play_sample(BOSS1->BOSS_SOUND_MISSION_COMP, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	BOSS1->music_1=1;
	al_flip_display();
	al_rest(7);
}



}


void DrawBOSS2(struct BOSS *BOSS2,int FPS, int MY_TIME,Player jugador[])
{
	
			if(++BOSS2->BOSS_frameCount >=   BOSS2->BOSS_frameDelay)
			{
				if(++BOSS2->BOSS_curFrame >= BOSS2->BOSS_maxFrame)
					BOSS2->BOSS_curFrame = 0;

				BOSS2->BOSS_frameCount = 0;
			}

if(BOSS2->damage<=1)
{//si el vos esta vivo


			if(++BOSS2->BOSS_FIRE_frameCount >= BOSS2->BOSS_FIRE_frameDelay)
			{
				if(++BOSS2->BOSS_FIRE_curFrame >= BOSS2->BOSS_FIRE_maxFrame)
					BOSS2->BOSS_FIRE_curFrame = 0;

				BOSS2->BOSS_FIRE_frameCount = 0;
			}

		 // acciones del boss
			if(MY_TIME>=0 && MY_TIME<2*FPS)// 2 SEGUNDOS
			{
				// Boss parado mirando a la izq
			
			BOSS2->BOSS_BULLET_Y=BOSS2->BOSS_frameHeight-40;
			BOSS2->BOSS_BULLET_X=BOSS2->x;
			al_draw_bitmap_region(BOSS2->BOSS_STAND, BOSS2->BOSS_curFrame * BOSS2->BOSS_frameWidth, 0, BOSS2->BOSS_frameWidth, BOSS2->BOSS_frameHeight, BOSS2->x, BOSS2->y, 0);
			return ;
		}

	if(MY_TIME>=2*FPS && MY_TIME<4*FPS)// 2 SEGUNDO
	{
		   
			// boss dispara hacia la izq una bala 
		    BOSS2->BOSS_BULLET_X-=BOSS2->BOSS_BULLET_SPEED;
		    BOSS2->BOSS_BULLET_Y+=((80-BOSS2->BOSS_BULLET_X/6)*BOSS2->dir); //la bala sube y baja rapidamente para dar un efecto que esta vibrando,queda piola
		  BOSS2->dir=BOSS2->dir*-1;
		   
		   
			al_draw_bitmap_region(BOSS2->BOSS_FIRE, BOSS2->BOSS_FIRE_curFrame * BOSS2->BOSS_FIRE_frameWidth, 0, BOSS2->BOSS_FIRE_frameWidth, BOSS2->BOSS_FIRE_frameHeight, BOSS2->x, BOSS2->y , 0);
			al_draw_bitmap(BOSS2->BOSS_BULLET,  BOSS2->BOSS_BULLET_X  ,BOSS2->BOSS_BULLET_Y, 0);
		return ;

	}
if(MY_TIME>=5 && MY_TIME<6*FPS)// 1 SEGUNDOS
			{
			// Boss parado mirando a la izq
			BOSS2->BOSS_BULLET_X=BOSS2->x;
			BOSS2->BOSS_BULLET_Y=BOSS2->BOSS_frameHeight-40;
			al_draw_bitmap_region(BOSS2->BOSS_STAND, BOSS2->BOSS_curFrame * BOSS2->BOSS_frameWidth, 0, BOSS2->BOSS_frameWidth, BOSS2->BOSS_frameHeight, BOSS2->x, BOSS2->y, 0);
			return ;
		}

if(MY_TIME>=6*FPS && MY_TIME<8*FPS)// 2 SEGUNDO
	{
		
			// boss dispara hacia la izq una bala 
			if(BOSS2->BOSS_BULLET_X>500)// la bala se mueve solo en x
			{
			BOSS2->BOSS_BULLET_X-=BOSS2->BOSS_BULLET_SPEED;
			BOSS2->BOSS_BULLET_Y= BOSS2->BOSS_BULLET_Y+5*BOSS2->dir;
			BOSS2->dir=BOSS2->dir*-1;
		    }
		    if(BOSS2->BOSS_BULLET_X<=500 && BOSS2->BOSS_BULLET_Y<=150) // la bala se mueve solo en y
		    {
			BOSS2->BOSS_BULLET_Y+=BOSS2->BOSS_BULLET_SPEED*1.1;
			BOSS2->BOSS_BULLET_Y= BOSS2->BOSS_BULLET_Y+10*BOSS2->dir;
			BOSS2->dir=BOSS2->dir*-1;
			}
		    else
		    {
		    BOSS2->BOSS_BULLET_X-=BOSS2->BOSS_BULLET_SPEED;
			BOSS2->BOSS_BULLET_Y= BOSS2->BOSS_BULLET_Y+10*BOSS2->dir;
			BOSS2->dir=BOSS2->dir*-1;
		}
			al_draw_bitmap_region(BOSS2->BOSS_FIRE, BOSS2->BOSS_FIRE_curFrame * BOSS2->BOSS_FIRE_frameWidth, 0, BOSS2->BOSS_FIRE_frameWidth, BOSS2->BOSS_FIRE_frameHeight, BOSS2->x, BOSS2->y , 0);
			al_draw_bitmap(BOSS2->BOSS_BULLET, BOSS2->BOSS_BULLET_X  ,BOSS2->BOSS_BULLET_Y, 0);
		return ;

	}
if(MY_TIME>=8 && MY_TIME<10*FPS)// 2 SEGUNDOS
			{
				// Boss parado mirando a la izq
			BOSS2->BOSS_BULLET_X=BOSS2->x;
			BOSS2->BOSS_BULLET_Y=BOSS2->BOSS_frameHeight-40;
			al_draw_bitmap_region(BOSS2->BOSS_STAND, BOSS2->BOSS_curFrame * BOSS2->BOSS_frameWidth, 0, BOSS2->BOSS_frameWidth, BOSS2->BOSS_frameHeight, BOSS2->x, BOSS2->y, 0);
			return ;
		}
		
		

}//	si el boss esta vivo

if(BOSS2->damage>=1)
{
	if(BOSS2->state==0)
	{
	BOSS2->state=1;
	jugador[0].score = jugador[0].score+150;
	jugador[1].score = jugador[1].score+150;
}
DrawBOSS2_DEAD(BOSS2);
}

	}

void DrawBOSS2_DEAD(struct BOSS *BOSS2)
{

	al_draw_bitmap(BOSS2->MISSION_COMPLETE,700/2 ,224/10, 0);
	if(BOSS2->music_1==0)
	{
	al_stop_samples();
	al_play_sample(BOSS2->BOSS_SOUND_MISSION_COMP, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	BOSS2->music_1=1;
	al_flip_display();
	al_rest(7);
}

}

void DrawBOSS3(struct BOSS *BOSS3,int FPS, int MY_TIME,Player jugador[],CFG *config)
{
	//fprintf( stdout, "%d\n",MY_TIME);
			if(++BOSS3->BOSS_frameCount >=   BOSS3->BOSS_frameDelay)
			{
				if(++BOSS3->BOSS_curFrame >= BOSS3->BOSS_maxFrame)
					BOSS3->BOSS_curFrame = 0;

				BOSS3->BOSS_frameCount = 0;
			}

if(BOSS3->damage<=1)
{//si el vos esta vivo


			if(++BOSS3->BOSS_FIRE_frameCount >= BOSS3->BOSS_FIRE_frameDelay)
			{
				if(++BOSS3->BOSS_FIRE_curFrame >= BOSS3->BOSS_FIRE_maxFrame)
					BOSS3->BOSS_FIRE_curFrame = 0;

				BOSS3->BOSS_FIRE_frameCount = 0;
			}

	if(++BOSS3->BOSS_EX_frameCount >= BOSS3->BOSS_EX_frameDelay)
			{
				if(++BOSS3->BOSS_EX_curFrame >= BOSS3->BOSS_EX_maxFrame)
					BOSS3->BOSS_EX_curFrame = 0;

				BOSS3->BOSS_EX_frameCount = 0;
			}
// acciones del boss

		if(MY_TIME>=0 && MY_TIME<1*FPS)
		{// parado mirando hacia la izq
		
			BOSS3->BOSS_BULLET_X=0;
			al_draw_bitmap_region(BOSS3->BOSS_STAND, BOSS3->BOSS_curFrame * BOSS3->BOSS_frameWidth, 0, BOSS3->BOSS_frameWidth, BOSS3->BOSS_frameHeight, BOSS3->x, BOSS3->y, 0);
			
			return;
		}	
		// corre hacia la izq
		if(MY_TIME>=1*FPS && MY_TIME<2*FPS)
		{
		BOSS3->BOSS_BULLET_X=0;
			BOSS3->x-=BOSS3->BOSS_SPEED;
		
			al_draw_bitmap_region(BOSS3->BOSS_RUN, BOSS3->BOSS_RUN_curFrame * BOSS3->BOSS_RUN_frameWidth, 0, BOSS3->BOSS_RUN_frameWidth, BOSS3->BOSS_RUN_frameHeight, BOSS3->x, BOSS3->y, 0);
		
		return;
	}
	
		// boss mira hacia la derecha
		if(MY_TIME>=2*FPS && MY_TIME<3*FPS)
		{
		BOSS3->BOSS_BULLET_X=0;
			
		al_draw_bitmap_region(BOSS3->BOSS_STAND, BOSS3->BOSS_curFrame * BOSS3->BOSS_frameWidth, 0, BOSS3->BOSS_frameWidth, BOSS3->BOSS_frameHeight, BOSS3->x, BOSS3->y, 1);			
		
		return;
	}
	
		if(MY_TIME>=3*FPS && MY_TIME<4*FPS)
		{ // boss dispara hacia la derecha
		BOSS3->BOSS_BULLET_X+=BOSS3->BOSS_BULLET_SPEED*2;
	
			al_draw_bitmap_region(BOSS3->BOSS_FIRE, BOSS3->BOSS_FIRE_curFrame * BOSS3->BOSS_FIRE_frameWidth, 0, BOSS3->BOSS_FIRE_frameWidth, BOSS3->BOSS_FIRE_frameHeight, BOSS3->x-40, BOSS3->y -20, 1);
			al_draw_bitmap(BOSS3->BOSS_BULLET, BOSS3->x + BOSS3->BOSS_BULLET_X  ,BOSS3->y +15, 1);

		return;
	}
	
	if(MY_TIME>=4*FPS && MY_TIME<5*FPS) // boss corre hacia la derecha
		{
		BOSS3->BOSS_BULLET_X=0;
			BOSS3->x+=BOSS3->BOSS_SPEED;
			
			
			al_draw_bitmap_region(BOSS3->BOSS_RUN, BOSS3->BOSS_RUN_curFrame * BOSS3->BOSS_RUN_frameWidth, 0, BOSS3->BOSS_RUN_frameWidth, BOSS3->BOSS_RUN_frameHeight, BOSS3->x, BOSS3->y, 1);
		
		return;
	}
	
		if(MY_TIME>=5*FPS && MY_TIME<6*FPS)
		{ // boss mira la izq
		
			BOSS3->BOSS_BULLET_X=0;
			al_draw_bitmap_region(BOSS3->BOSS_STAND, BOSS3->BOSS_curFrame * BOSS3->BOSS_frameWidth, 0, BOSS3->BOSS_frameWidth, BOSS3->BOSS_frameHeight, BOSS3->x, BOSS3->y, 0);
		
		return;
	}
		
		if(MY_TIME>=6*FPS && MY_TIME<7*FPS)
		{ // boss dispara hacia la izq
		BOSS3->BOSS_BULLET_X-=BOSS3->BOSS_BULLET_SPEED;
			al_draw_bitmap_region(BOSS3->BOSS_FIRE, BOSS3->BOSS_FIRE_curFrame * BOSS3->BOSS_FIRE_frameWidth, 0, BOSS3->BOSS_FIRE_frameWidth, BOSS3->BOSS_FIRE_frameHeight, BOSS3->x-40, BOSS3->y -20, 0);
			al_draw_bitmap(BOSS3->BOSS_BULLET, BOSS3->x + BOSS3->BOSS_BULLET_X  ,BOSS3->y +15, 0);
			al_draw_bitmap(BOSS3->BOSS_BULLET, BOSS3->x + BOSS3->BOSS_BULLET_X -50  ,BOSS3->y +15, 0);
		return;
	}		
		if(MY_TIME>=7*FPS && MY_TIME<8*FPS) //boss vuela hacia arriba		
				{
				BOSS3->BOSS_BULLET_X=0;
			BOSS3->y-=BOSS3->BOSS_SPEED/2;
			BOSS3->x-=BOSS3->BOSS_SPEED/2;
			al_draw_bitmap_region(BOSS3->BOSS_RUN, BOSS3->BOSS_RUN_curFrame * BOSS3->BOSS_RUN_frameWidth, 0, BOSS3->BOSS_RUN_frameWidth, BOSS3->BOSS_RUN_frameHeight, BOSS3->x, BOSS3->y, 0);
				return;
			}
				if(MY_TIME>=8*FPS && MY_TIME<9*FPS)
				{ //boss golpea el piso y sale FUEGO!!!!!		
				BOSS3->BOSS_BULLET_X=0;
				if(BOSS3->y < (config->SCREEN_H/2 +15 ))
				{
			BOSS3->y+=BOSS3->BOSS_SPEED*2;
		}
	//	fprintf( stdout, "%d\n",BOSS3->y);
			al_draw_bitmap_region(BOSS3->BOSS_RUN, BOSS3->BOSS_RUN_curFrame * BOSS3->BOSS_RUN_frameWidth, 0, BOSS3->BOSS_RUN_frameWidth, BOSS3->BOSS_RUN_frameHeight, BOSS3->x, BOSS3->y, 0);
				if(BOSS3->y>(config->SCREEN_H/2 +10) )
				{
				
			al_draw_bitmap_region(BOSS3->BOSS_EX, BOSS3->BOSS_EX_curFrame * BOSS3->BOSS_EX_frameWidth, 0, BOSS3->BOSS_EX_frameWidth, BOSS3->BOSS_EX_frameHeight, BOSS3->x, BOSS3->y-40, 0);
			al_draw_bitmap_region(BOSS3->BOSS_EX, BOSS3->BOSS_EX_curFrame * BOSS3->BOSS_EX_frameWidth, 0, BOSS3->BOSS_EX_frameWidth, BOSS3->BOSS_EX_frameHeight, BOSS3->x-100, BOSS3->y-40, 0);
			al_draw_bitmap_region(BOSS3->BOSS_EX, BOSS3->BOSS_EX_curFrame * BOSS3->BOSS_EX_frameWidth, 0, BOSS3->BOSS_EX_frameWidth, BOSS3->BOSS_EX_frameHeight, BOSS3->x+100, BOSS3->y-40, 0);
				}
				return;
			}
		if(MY_TIME>=9 && MY_TIME<10*FPS){ // boss corre hacia la derecha
		BOSS3->BOSS_BULLET_X=0;
		BOSS3->x+=BOSS3->BOSS_SPEED/2;
			
			
			al_draw_bitmap_region(BOSS3->BOSS_RUN, BOSS3->BOSS_RUN_curFrame * BOSS3->BOSS_RUN_frameWidth, 0, BOSS3->BOSS_RUN_frameWidth, BOSS3->BOSS_RUN_frameHeight, BOSS3->x, BOSS3->y, 1);
		
		return;			
}
}

if(BOSS3->damage>=1)
{
	if(BOSS3->state==0)
	{
	BOSS3->state=1;
	jugador[0].score = jugador[0].score+250;
	jugador[1].score = jugador[1].score+250;
}
DrawBOSS3_DEAD(BOSS3);
}

	}


void DrawBOSS3_DEAD(struct BOSS *BOSS3)
{

	al_draw_bitmap(BOSS3->MISSION_COMPLETE,700/2 ,224/10, 0);
	if(BOSS3->music_1==0)
	{
	al_stop_samples();
	al_play_sample(BOSS3->BOSS_SOUND_MISSION_COMP, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	BOSS3->music_1=1;
	al_flip_display();
	al_rest(7);
}

}

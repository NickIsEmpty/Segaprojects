#include <genesis.h>
#include <resources.h> 	//Позволяет нам использовать спрайты и тайлы , инициалищированные в файле resources.res
#include <string.h>		//Это дает нам доступ к некоторому коду, упрощающему работу со строками.

/*Определять левый и правый края экрана. Хорошо использовать определения 
  (или переменные) для этих значений, чтобы мы могли легко изменить границы игровой 
  области позже.*/
#define LEFT_EDGE 0
#define RIGHT_EDGE 320
#define ANIM_STRAIGHT 0
#define ANIM_MOVE 1 
#define MAX_BULLETS 6 
#define MAX_ENEMIES 6
#define BOTTOM_EDGE 224
#define SHOT_INTERVAL 120
#define MAX_PLAYER_BULLETS 3
#define SFX_LASER 64
#define POWERUP_DURATION 180

u16 shotByPlayer = 0;
u16 bulletsOnScreen = 0;
u16 shotTicker = 0;
u16 enemiesLeft = 0;
u16 maxPlayerBullets = MAX_PLAYER_BULLETS;
u16 powerupTimer = 0;

int i = 0;
int thex = 0;
int they = 0;
int val = 1;

int score = 0;
char hud_string[40] = "";

char msg_reset[25] = "PRESS START TO RESTART";
char msg_start[20] = "PRESS START TO BEGIN";

bool game_on = FALSE;


void updateScoreDisplay()
{
	sprintf(hud_string,"SCORE: %d - LEFT:%d", score,enemiesLeft);
	VDP_clearText(0,0,40);
	VDP_drawText(hud_string,0,0);
}

void showText(char s[])
{
	VDP_drawText(s, 20 - strlen(s)/2 ,15);
}

void endGame()
{
	showText(msg_reset);
	game_on = FALSE;
}



typedef struct 
{
	int x;
	int y;
	int w;
	int h;
	int velx;
	int vely;
	int health;

	Sprite* sprite;
	char name[6];
} Entity;

/*И чтобы быть очень ленивым, мы поместим все вражеские объекты в массив, 
  чтобы нам было легче справляться с ними сразу.*/

Entity enemies[MAX_ENEMIES];
Entity player = {0,0,16,16,0,0,0,NULL,"PLAYER"};
Entity bullets [MAX_BULLETS];
Entity powerup = { 0,0,8,8,0,0,0, NULL,"POWER"};

typedef enum 
{
	RapidFire
}Powerup;


void killEntity(Entity* e)
{
	e->health = 0;
	SPR_setVisibility(e->sprite,HIDDEN);
}

void reviveEntity(Entity* e)
{
	e->health = 1;
	SPR_setVisibility(e->sprite,VISIBLE);
}

void shootBullet(Entity Shooter)
{
	bool fromPlayer = (Shooter.y > 100);
 
 
	if(bulletsOnScreen < MAX_BULLETS)
	{
		if(shotByPlayer >= maxPlayerBullets)
		{
        	return;
    	}
		Entity* b ;
		u16 i =0;
		for(i = 0; i < MAX_BULLETS; i++)
		{
			b = &bullets[i];

			if(b->health == 0 && Shooter.health > 0)
			{
				b->x = Shooter.x + 4;
				b->y = Shooter.y;

				reviveEntity(b);
				if(fromPlayer == TRUE)
				{
					b->vely = -3;
					shotByPlayer++;
				}
				else
				{
					b->vely = 3;
				}

				SPR_setPosition(b->sprite,b->x,b->y);
				bulletsOnScreen++;

				XGM_startPlayPCM(SFX_LASER,15,SOUND_PCM_CH2);


				break;
			}
		}
 	}
}
/*Заставим этих врагов двигаться. Мы создадим функцию, которая будет 
проходить по всем вражеским объектам в цикле и обрабатывать движение для каждого из 
них.*/

void positionEnemies()
{
	shotTicker++;
	/*Во-первых, давайте переберем всех врагов и сохраним текущего в переменной,
	 чтобы мы могли манипулировать его значениями.*/

	 u16 i =0;

	/*Мы перебираем всех врагов, берем адрес текущего и сохраняем его внутри 
	  указателя e.*/

	 for(i = 0; i < MAX_ENEMIES; i++)
	 {
		Entity* e = &enemies[i];
		if( (e->x+e->w) > RIGHT_EDGE)
		{
    		e->velx = -1;
		}
		else if(e->x < LEFT_EDGE)
		{
    		e->velx = 1;
		}
		e->x += e->velx;
		SPR_setPosition(e->sprite,e->x,e->y);

		if(shotTicker >= SHOT_INTERVAL)
		{
			if((random()%(10-1+1)+1) > 4 )
			{
				shootBullet(*e);
				shotTicker = 0;
			}
		}
		

	/*Мы хотим перемещать только живых врагов, поэтому давайте добавим это условие:*/

		if(e->health > 0)
		{
			
		}
		
		/*Стрельба*/
		

		
	 }
}

int collideEntities(Entity* a, Entity* b)
{
    return (a->x < b->x + b->w && a->x + a->w > b->x && a->y < b->y + b->h && a->y + a->h >= b->y);
}

void positionBullets()
{
	u16 i = 0;
	Entity *b;

	for(i = 0; i <MAX_BULLETS;i++)
	{
		b = &bullets[i];

		if(b->health > 0)
		{
			b->y += b->vely;

			if(b->y + b->h < 0)
			{
				killEntity(b);
				bulletsOnScreen--;
				shotByPlayer--;
			}
			else if (b->y >BOTTOM_EDGE)
			{
				killEntity(b);
				bulletsOnScreen--;
			}
			else
			{
				SPR_setPosition(b->sprite, b->x,b->y);
			}
		}
	}
}

void spawnPowerupAt(u16 X, u16 Y)
{
	powerup.x = X;
	powerup.y = Y;
	reviveEntity(&powerup);
}


void activatePowerup(Powerup Type)
{
	switch(Type)
	{
		case RapidFire:
		{
			maxPlayerBullets = MAX_BULLETS;
			powerupTimer = POWERUP_DURATION;
			PAL_setColor(18, RGB24_TO_VDPCOLOR(0xf8fc00));
		}
		default: return;
	}
}

void positionPowerup()
{
	if(powerup.health > 0)
	{
		powerup.y++;

		if(powerup.y > BOTTOM_EDGE)
		{
			killEntity(&powerup);
		}

		if(collideEntities(&player,&powerup))
		{
			activatePowerup(RapidFire);
			killEntity(&powerup);
		}
	}
	SPR_setPosition(powerup.sprite,powerup.x,powerup.y);
}

void deactivatePowerup()
{
	maxPlayerBullets = MAX_PLAYER_BULLETS;
	PAL_setColor(18, RGB24_TO_VDPCOLOR(0xf83800));
}

void positionPlayer()
{
	/*Создаем скорость движения игрока к его позиции:*/
	player.x += player.velx;

	/*Не даем игроку выйти за рамки экрана:*/
	if(player.x < LEFT_EDGE) player.x = LEFT_EDGE;
	if(player.x + player.w > RIGHT_EDGE) player.x = RIGHT_EDGE- player.w;

	/*Даём движку спрайта расположить спрайт:*/
	SPR_setPosition(player.sprite,player.x,player.y);
}

void enemiesSpawn()
{
	Entity* e = enemies;
	for(i = 0; i < MAX_ENEMIES; i++)
	{
		/*Обратите внимание, что теперь нам придется использовать оператор стрелки 
		(вместо точки) для доступа к элементу в структуре, поскольку e — это указатель. 
		К вашему сведению, e->x эквивалентно (*e).x.*/
		e->x = i*32;
		e->y = 32;
		e->w = 16;
		e->h = 16;
		e->velx = 1;
		e->health = 1;

		/*Теперь добавим спрайты. Помните, что в структуре Entity есть элемент Sprite*, 
		в котором будет храниться наш спрайт.*/
		e->sprite = SPR_addSprite(&ship,e->x,e->y,TILE_ATTR(PAL2,0,TRUE,FALSE));

		/*Мы дадим каждому врагу имя. Сгенерируйте его следующим образом:*/
		sprintf(e->name, "En%d",i);

		enemiesLeft++;
		e++;
	}
}

void startGame()
{
	reviveEntity(&player);
	game_on = TRUE;
	score = 0;
	updateScoreDisplay();
	VDP_clearTextArea(0,10,40,10);	
	enemiesSpawn();
	killEntity(&powerup);

}

void myJoyHandler(u16 joy, u16 changed, u16 state)
{

	
	if(joy == JOY_1)
	{
	
		if(state & BUTTON_START)
		{
			if(!game_on)
			{
				startGame();
			}
		}

		if(state & BUTTON_RIGHT)
		{
			player.velx = 2;
			SPR_setAnim(player.sprite, ANIM_MOVE);
			SPR_setHFlip(player.sprite,TRUE);
		}
		else if (state & BUTTON_LEFT)
		{
			player.velx = -2;
			SPR_setAnim(player.sprite, ANIM_MOVE);
			SPR_setHFlip(player.sprite,FALSE);
		}
		else
		{
			if( (changed & BUTTON_RIGHT) | (changed * BUTTON_LEFT))
			{
				player.velx = 0;
				SPR_setAnim(player.sprite,ANIM_STRAIGHT);
			}
		}

		if(state & BUTTON_B & changed)
		{
			shootBullet(player);
		}

		
		
	}
}


void handlerCollisions()
{
	Entity* e;
	Entity* b;
	int i = 0;
	int j = 0;

	for(i = 0; i < MAX_BULLETS; i++)
	{
		b = &bullets[i];	
		/*if(game_on == FALSE)
		{
			if(b->health > 0)
			{
				killEntity(b);
				bulletsOnScreen = 0;
				shotByPlayer = 0;
			}
		}*/
		if(b->health > 0)
		{
			if(b->vely < 0)
			{
				for(j = 0 ; j < MAX_ENEMIES; j++)
				{
					e = &enemies[j];
					if(e->health > 0)
					{
						if( collideEntities(b,e))
						{
							killEntity(b);
							killEntity(e);

							enemiesLeft--;
							bulletsOnScreen--;
							shotByPlayer--;

							if(enemiesLeft == 0)
							{
								endGame();
							}

							score+=10;
							updateScoreDisplay();

							if(enemiesLeft % 5 == 0)
							{
								spawnPowerupAt(e->x,e->y);
							}

							break;
						}
					}
					
				}
			}
			else
			{
				if(collideEntities(b,&player))
				{
					
					killEntity(&player);
					killEntity(b);
					bulletsOnScreen--;
					player.x = 152;
					player.y = 192;	
					
					for(j = 0 ; j < MAX_ENEMIES; j++)
					{
						e = &enemies[j];
						if(e->health > 0)
						{
							killEntity(e);
							enemiesLeft = 0;
						}
					}
					endGame();
									
				}
			}
		}
	}
}



int main()
{

	JOY_init();
	JOY_setEventHandler( &myJoyHandler );

	showText(msg_start);

	VDP_loadTileSet(background.tileset,1,DMA);
	PAL_setPalette(PAL1,background.palette->data,DMA);
	PAL_setPalette(PAL2,background.palette->data,DMA);


	SPR_init();

	//Добавляем игрока
	player.x = 152;
	player.y = 192;
	player.health = 1;
	player.sprite = SPR_addSprite(&ship,player.x,player.y,TILE_ATTR(PAL1,0,FALSE,FALSE));
	SPR_update();

	powerup.sprite = SPR_addSprite(&spr_powerup, powerup.x, powerup.y, TILE_ATTR(PAL1,0,FALSE,FALSE));
	killEntity(&powerup);

	/*Создаем все спрайты пуль*/
	Entity* b = bullets;
	for(i = 0 ; i< MAX_BULLETS;i++)
	{
		
		b->x = 0;
		b->y = -10;
		b->w =8;
		b->h = 8;
		b->sprite = SPR_addSprite(&bullet,bullets[0].x,bullets[0].y,TILE_ATTR(PAL1,0,FALSE,FALSE));		
		sprintf(b->name, "Bu%d",i);
		b++;
	}

	//Создаём спрайты всех врагов
	//enemiesSpawn();
	PAL_setColor(34,RGB24_TO_VDPCOLOR(0x0078f8));
	
	for( i=0; i < 1280; i++)
	{
		thex = i % 40;
		they = i / 40;
		val = (random() %  (10-1+1))+1;
		if(val > 3) val = 1;
		VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,0,0,val), thex, they );
	}
	
	int offset = 0;
	VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);

	XGM_setPCM(SFX_LASER, sfx_laser, sizeof(sfx_laser));
	/*Функция XGM_setPCM объявляет образец PCM звуковому драйверу. 
	Без этого шага мы не смогли бы воспроизвести наш звук, так как 
	наш драйвер даже не знал бы об этом. Первый аргумент — индекс звука 
	(в нашем случае 64), второй — ресурс, который мы хотим использовать; в нашем 
	случае мы назвали звук sfx_laser в файле resources.res. Последним аргументом 
	является размер выборки в байтах. К счастью, C предоставляет нам оператор sizeof(), 
	который возвращает именно то, что нам нужно.*/

    while(1)
    {
		if(game_on == TRUE)
		{
			VDP_setVerticalScroll(BG_B,offset-=2);
			if(offset<=-256) offset = 0;

		
			updateScoreDisplay();
			positionBullets();
			positionPlayer();
			positionEnemies();
			positionPowerup();
			handlerCollisions();

			if(powerupTimer > 0)
			{
				powerupTimer--;
				if(powerupTimer == 0)
				{
					deactivatePowerup();
				}
			}
			
			SPR_update();
		}
		SYS_disableInts();
        SYS_doVBlankProcess();
		
	}
	return(0);
}
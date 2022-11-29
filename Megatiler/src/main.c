#include <genesis.h>
#include <resources.h> 	


#define SPAWN_TILE 4
#define TILESIZE 8
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define SOLID_TILE 1
#define ANIM_DOWN 0
#define ANIM_UP 1
#define ANIM_SIDE 2
#define COIN_TILE 6
#define MAX_COINS 3
#define SFX_COIN 64
#define SFX_UNLOCK 65
#define EXIT_TILE 5
#define LEVEL_NUM 3
#define LEVEL_NUM 3

typedef u8 map[MAP_HEIGHT][MAP_WIDTH];

u8 coinsCollected = 0;
u8* currentLevel;
static u8 currentLevelIndex = 0;
map* levelList[3];
map level1 = 
{
	{0, 0, 0, 0, 0, 0, 0, 6},
	{0, 4, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 6, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 6, 0, 5}
};
map level2 = 
{
    {0, 0, 0, 6, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 4, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 6, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 6, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};
map level3 = 
{
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 6, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 6, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 6, 1, 1, 1, 1, 0, 0},
    {0, 4, 0, 0, 0, 0, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};
/*ВНИМАНИЕ: обратите внимание, что порядок координат обратный. В системе координат мы 
обычно сначала указываем значение x, а затем значение y. Однако значение a в 
массиве [a][b] на самом деле является значением y, поскольку оно указывает на то, 
какой подмассив нам нужен; и в нашем фрагменте массива выше это строка, которая нам нужна.
Итак, чтобы получить доступ к самому верхнему 1 значению в массиве, вам нужно будет 
получить доступ к level1[2][4] (третья строка, пятое значение). Это легко испортить, 
так что имейте это в виду!*/
char hud_string[10] = "";
int score = 0;
char label_score[6] = "SCORE\0";
char str_score[4] = "0";
char msg_start[22] = "PRESS START TO BEGIN!\0";
char msg_reset[37] = "GAME OVER! PRESS START TO PLAY AGAIN.";

bool game_on = FALSE;
bool exitUnlocked = FALSE;



typedef enum {up, down, left, right, none} moveDirection;

typedef struct
{
	u8 x;
	u8 y;
}Point;

Point exitLocation = { 0 , 0 };


typedef struct 
{
	Point pos;
	u8 w;
	u8 h;
	Sprite *sprite;
	u8 health;
}Coin;

Coin coins[MAX_COINS];

typedef struct 
{
	Point pos;
	Point tilePos;
	int w;
	int h;
	int health;
	bool moving;
	moveDirection dir;
	Sprite *sprite;
	char name[6];
}Entity;


Entity player = {{0, 0}, {0, 0}, 8, 8, 0, FALSE, none, NULL, "PLAYER"};

int getTileAt(u8 X, u8 Y)
{
	return *(currentLevel + (Y * MAP_WIDTH + X));
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


void updateScoreDisplay()
{
	sprintf(hud_string,"%d",coinsCollected);                          	
	VDP_clearText(8,0,10); 	
	VDP_drawText(hud_string,8,0);
}


void startGame(){
	score = 0;
	updateScoreDisplay();
	
	VDP_clearTextArea(0,10,40,10); //Очищает весь текст на экране

	game_on = TRUE;
}


void movePlayer( moveDirection Direction)
{
	switch (Direction)
	{
		case up:
		{
			if(player.tilePos.y > 0 && getTileAt(player.tilePos.x,player.tilePos.y-1) != SOLID_TILE)
			{
				player.tilePos.y -= 1;
				player.moving = TRUE;
				player.dir = Direction;
				SPR_setAnim(player.sprite,ANIM_UP);
			}
			
		}break;
			
		case down:
		{
			if(player.tilePos.y < MAP_HEIGHT - 1 && getTileAt(player.tilePos.x,player.tilePos.y+1) != SOLID_TILE)
			{
				player.tilePos.y += 1;
				player.moving = TRUE;
				player.dir = Direction;
				SPR_setAnim(player.sprite, ANIM_DOWN);
			}
		}break;
			
		case left:
		{
			if(player.tilePos.x > 0 && getTileAt(player.tilePos.x-1, player.tilePos.y) != SOLID_TILE)
			{
        		player.tilePos.x -= 1;
				player.moving = TRUE;
    			player.dir = Direction;
				SPR_setAnim(player.sprite, ANIM_SIDE);
				SPR_setHFlip(player.sprite, TRUE);
			}
		}break;
			

		case right:
		{
			 if(player.tilePos.x < MAP_WIDTH - 1 && getTileAt(player.tilePos.x+1, player.tilePos.y) != SOLID_TILE)
			{
        		player.tilePos.x += 1;
				player.moving = TRUE;
    			player.dir = Direction;
				SPR_setAnim(player.sprite, ANIM_SIDE);
				SPR_setHFlip(player.sprite,FALSE);
			}
		}break;

		default:
			break;
	}
	
	if(player.moving == FALSE)
	{
		if (exitUnlocked == TRUE && player.tilePos.x == exitLocation.x && player.tilePos.y == exitLocation.y)
		{
			 currentLevelIndex++;
			if(currentLevelIndex >= LEVEL_NUM)
			{
				currentLevelIndex = 0;
			}
    loadLevel();
		}
	}
	
}

void unlockExit()
{
    exitUnlocked = TRUE;
    VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 3), exitLocation.x, exitLocation.y);
    XGM_startPlayPCM(SFX_UNLOCK, 1, SOUND_PCM_CH2);
}

void clearLevel()
{
    VDP_clearPlane(BG_B, TRUE);
    VDP_clearSprites();
    coinsCollected = 0;
    updateScoreDisplay();
    exitUnlocked = FALSE;  
}

void loadLevel()
{
  clearLevel();
currentLevel = levelList[currentLevelIndex];

  //Загрузить первый уровень
  u8 x =0;
  u8 y = 0;
  u8 t = 0;
  u8 coinNum = 0;
  Coin *c = coins;

  u8 i = 0;
  u8 total = MAP_HEIGHT * MAP_WIDTH;
  SPR_init();
  for(i = 0; i < total; i++)
  {

		t = *(currentLevel + i);
		if(t == SPAWN_TILE)
		{
			//Спавн игрока
			player.tilePos.x = x;
			player.tilePos.y = y;

			player.pos.x = player.tilePos.x * TILESIZE;
			player.pos.y = player.tilePos.y * TILESIZE;

			player.sprite = SPR_addSprite(&spr_player, player.pos.x, player.pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));			
			VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), x, y);
			PAL_setPalette(PAL1, floortiles.palette->data, DMA);
			PAL_setPalette(PAL2, spr_player.palette->data, DMA);
		}
		else if(t == COIN_TILE)
		{
			if(coinNum < MAX_COINS)
			{
				c = &coins[coinNum];
				c-> pos.x = x * TILESIZE;
				c-> pos.y = y * TILESIZE;
				c->w = 8;
				c->h = 8;
				c->health =1;
				c->sprite = SPR_addSprite(&coin, c->pos.x, c->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));				coinNum++;
			}
			VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), x, y);
		}
		else if (t == EXIT_TILE)
		{
			exitLocation.x = x;
			exitLocation.y = y;
			VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), x, y);
		}
		else 
		{
			VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE,  t+1), x, y);
		}

		x++;
		if (x >= MAP_WIDTH)
		{
			y++;
			x = 0;
		}
	
  }
}


void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_UP)
        {
            movePlayer(up);
        }
        else if (state & BUTTON_DOWN)
        {
            movePlayer(down);
        }
        else if (state & BUTTON_LEFT)
        {
            movePlayer(left);
        }
        else if (state & BUTTON_RIGHT)
        {
            movePlayer(right);
        }
    }
}


int main()
{

	XGM_setPCM(SFX_COIN, sfx_coin, sizeof(sfx_coin));
	XGM_setPCM(SFX_UNLOCK, sfx_unlock, sizeof(sfx_unlock));

	
	
	JOY_init(); 							
	JOY_setEventHandler( &myJoyHandler);	


    SPR_init();

	VDP_loadTileSet(floortiles.tileset, 1, DMA);
	PAL_setPalette(PAL1, floortiles.palette->data,DMA);

	levelList[0] = level1;
	levelList[1] = level2;
	levelList[2] = level3;
	loadLevel();

	

	Coin* coinToCheck;
	updateScoreDisplay();
    while(1)
    {

		
		if(game_on == TRUE)
		{
			
		}
		if(player.moving == TRUE)
		{
			switch (player.dir)
			{
				case up:
				player.pos.y -= 1;				
					break;
				case down:
					player.pos.y += 1;					
					break;
				case left:
					player.pos.x -= 1;
					break;
				case right:
					player.pos.x += 1;

					break;
				default:
				break;
			}
			
    	}
		if (player.pos.x % TILESIZE == 0 && player.pos.y % TILESIZE == 0)
		{
			player.moving = FALSE;
		}
		SPR_setPosition(player.sprite, player.pos.x, player.pos.y);
    	
		u8 i = 0;
		//Проверка монет
		for( i = 0; i <MAX_COINS; i++)
		{
			coinToCheck = &coins[i];
			if ((player.pos.x < coinToCheck->pos.x + coinToCheck->w && player.pos.x + 
			player.w > coinToCheck->pos.x && player.pos.y <   coinToCheck->pos.y 
			+ coinToCheck->h && player.pos.y + player.h > coinToCheck->pos.y) == TRUE)
			{
				if (coinToCheck->health > 0)
				{
					coinToCheck->health = 0;
					coinsCollected++;
					XGM_startPlayPCM(SFX_COIN, 1, SOUND_PCM_CH2);
					updateScoreDisplay();
					SPR_setVisibility(coinToCheck->sprite, HIDDEN);
				}
				if(coinsCollected == MAX_COINS)
				{

    				unlockExit();
				}
			}
		}

		SPR_update();
        SYS_doVBlankProcess();

	}
	return(0);
    
}


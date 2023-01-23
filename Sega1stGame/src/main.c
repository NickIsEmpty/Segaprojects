#include <genesis.h>
#include <resources.h> 	
#include <string.h>		

#define UPLEFTIDLE 0
#define UPIDLE 1
#define LEFTIDLE 2 
#define DOWNLEFTIDLE 3
#define DOWNIDLE 4

#define UPWALK 5
#define UPLEFTWALK 6
#define LEFTWALK 7
#define DOWNLEFTWALK 8
#define DOWNWALK 9

#define RIGHTEDGE 262
#define LEFTEDGE 20
#define TOPEDGE 30
#define BOTTOMEDGE 210

#define SOLID_TILE 1


#define MAP_HEIGHT 28
#define MAP_WIDTH 40
#define MAX_BULLETS 10

typedef u8 map[MAP_HEIGHT][MAP_WIDTH];

map level1 = {   	
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}              			
};


void loadLevel(){
    u8 x = 0;
    u8 y = 0;
    u8 t = 0;

    for(y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            t = level1[y][x];
            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, t+1), x, y);
        }
    }
}

typedef struct
{
    u8 x;
    u8 y;
} Point;

typedef enum {up,upleft,upright,down,downleft,downright,left,right,none} moveDirection;

typedef struct
{
    Point pos;
    Point vel;
    int w;
    int h;
    int health;
    bool moving;
    moveDirection dir;
    Sprite *sprite;
    char name[6];
} Entity;

Entity player = {{65,65},{0,0}, 8, 8, 0, FALSE, none, NULL, "PLAYER"};
Entity enemy = {{0,0}, {0,0}, 8, 8, 0, FALSE, none, NULL , "ENEMY"};
//Entity  bullet ={{0,0}, {0,0}, 4, 4, 0, FALSE, none, NULL, "BULLET"};
Entity bullet [MAX_BULLETS];


int i = 0;

void killEntity(Entity* e)
{
	if(e->health == 0)
	SPR_setVisibility(e->sprite,HIDDEN);
}

void reviveEntity(Entity* e, int HP)
{
	e->health = HP;
	SPR_setVisibility(e->sprite,VISIBLE);
}



int getTileAt(u8 X, u8 Y)
{
    return *(&level1[Y][X]);
}

void shootBullet(Entity Shooter)
{
    u16 i = 0;
    Entity *b;

    for( i = 0; i < MAX_BULLETS; i++)
    {
        b = &bullet[i];

        switch(player.dir)
        {
            case up:
            b->pos.x = Shooter.pos.x + 16;
            b->pos.y = Shooter.pos.y;
            b->vel.y = -3;
            b->vel.x = 0;
            SPR_setVFlip(b->sprite, FALSE);
            break;

            case down:
            b->vel.y = 3;
            b->vel.x = 0;
            b->pos.x = Shooter.pos.x + 6;
            b->pos.y = Shooter.pos.y + 24;
            SPR_setVFlip(b->sprite, TRUE);
            break;

            case right:
            b->pos.x = Shooter.pos.x + 24;
            b->pos.y = Shooter.pos.y + 16;
            b->vel.y = 0;
            b->vel.x = 3;
            break;

            case left:
            b->pos.x = Shooter.pos.x;
            b->pos.y = Shooter.pos.y + 16;
            b->vel.y = 0;
            b->vel.x = -3;
            break;

            case upleft:
            break;

            case upright:
            break;

            case downleft:
            break;

            case downright:
            break;
            
            case none:
            break;

        }

        reviveEntity(b, 1); 
        SPR_setPosition(b->sprite,b->pos.x,b->pos.y);
    }
}

void positionBullets()
{
	u16 i = 0;
	Entity *b;

	for(i = 0; i <MAX_BULLETS;i++)
	{
		b = &bullet[i];

        b->pos.x += b->vel.x;
        b->pos.y += b->vel.y;

        if(b->pos.y + b->h < 0)
        {
            killEntity(b);
        }
        else if (b->pos.x > 262 || b->pos.x <= 1 || b->pos.y <= 1 || b->pos.y >= 210 )
        {
            b->health = 0;
            killEntity(b);
        }
        else
        {
            SPR_setPosition(b->sprite, b->pos.x,b->pos.y);
        }
	}
}

void moveingIsFalse()
{
    if(player.moving == FALSE)
    {
        player.vel.x = 0;
        player.vel.y = 0;
    } 
}

bool mapCollisions(s16 x, s16 y)
{
    s16 y_tile = y >> 3;
	s16 x_tile = x >> 3;
	
	u8 player_width = 4;
	u8 player_height = 4;
	
	s16 leftTile = x_tile;
	s16 rightTile = x_tile+player_width;
	s16 topTile = y_tile;
	s16 bottomTile = y_tile+player_height;
	
	for(s16 i=leftTile; i<=rightTile; i++)
	{
		for(s16 j=topTile; j<=bottomTile; j++)
		{
			if(level1[j][i] == 0) 
            {
                if (player.dir == up && j == topTile)
                {
                    player.moving = FALSE;      
                }
                else if( player.dir == down && j == bottomTile)
                {
                    player.moving = FALSE;  
				}
                else if (player.dir == left && i == leftTile)
                {
                    player.moving = FALSE;   
                }
                else if (player.dir == right && i == rightTile)
                {
                    player.moving = FALSE;   
                }
                else if (player.dir == upright && (i == rightTile || j == topTile))
                {
                    player.moving = FALSE;
                }
                else if (player.dir == upleft && (i == leftTile || j == topTile))
                {
                    player.moving = FALSE;
                }
                else if (player.dir == downright && (i == rightTile || j == bottomTile))
                {
                    player.moving = FALSE;
                }
                else if (player.dir == downleft && (i == leftTile || j == bottomTile))
                {
                    player.moving = FALSE;
                }
                return FALSE;
			}  
		}
	}
	return TRUE;
}

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_UP)
        {            
            player.dir = up;
            player.moving = TRUE;
            
            if(state & BUTTON_LEFT )
            {
                player.dir = upleft;
                player.moving = TRUE;
            }
            else if (state & BUTTON_RIGHT )
            {   
                player.dir = upright; 
                player.moving = TRUE;
            } 
        }
        else if (state & BUTTON_DOWN )
        {
            player.dir = down;
            player.moving = TRUE;

            if(state & BUTTON_LEFT )
            {
                
                player.moving = TRUE;
                player.dir = downleft;
            }
            else if(state & BUTTON_RIGHT )
            {
                if(mapCollisions(player.pos.x + 1, player.pos.y ))
                {player.moving = TRUE;
                player.vel.y = 1;
                player.vel.x = 1;}
                player.dir = downright;
                SPR_setAnim(player.sprite, DOWNLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            }
        }
        else if (state & BUTTON_LEFT )
        {   
            player.dir = left;
            player.moving = TRUE;
        }
        else if (state & BUTTON_RIGHT )
        {
            player.dir = right;
            player.moving = TRUE;
        }
        else
        {
            player.moving = FALSE;           
        }   

        
    }
}

void playableZone()
{
    if(player.pos.x + player.w >= RIGHTEDGE ) player.pos.x = RIGHTEDGE - player.w;
    if(player.pos.x <= LEFTEDGE) player.pos.x = LEFTEDGE;
    if(player.pos.y <= TOPEDGE) player.pos.y = TOPEDGE;
    if(player.pos.y + player.h >= BOTTOMEDGE) player.pos.y = BOTTOMEDGE - player.h; 
}

void Animator()
{
    if(player.moving == TRUE)   
    {
        switch (player.dir)
        {
            case up:
            
                if(mapCollisions(player.pos.x, player.pos.y - 1 ) )
                {
                    player.dir = up;
                    player.vel.y = -1;
                    player.vel.x = 0; 
                }           
                SPR_setHFlip(player.sprite, FALSE);
                SPR_setAnim(player.sprite, UPWALK);
            
            break;

            case down:

                if(mapCollisions(player.pos.x, player.pos.y + 1 ))
                {
                    player.dir = down;
                    player.vel.y = 1;
                    player.vel.x = 0;
                }
                SPR_setHFlip(player.sprite, FALSE);
                SPR_setAnim(player.sprite, DOWNWALK);
            
            break;

            case left:

                if(mapCollisions(player.pos.x - 1, player.pos.y ))
                {
                    player.dir = left; 
                    player.vel.y = 0;
                    player.vel.x = -1;
                } 
                SPR_setAnim(player.sprite, LEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            
            break;

            case right:

                if(mapCollisions(player.pos.x + 1, player.pos.y))
                { 
                    player.dir = right;
                    player.vel.y = 0;
                    player.vel.x = 1;
                }  
                SPR_setAnim(player.sprite, LEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            
            break;

            case upleft:
            
                if(mapCollisions(player.pos.x - 1, player.pos.y - 1 ))
                {
                    player.dir = upleft;
                    player.vel.y = -1;
                    player.vel.x = -1;
                }
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);

            break;

            case upright:

                if(mapCollisions(player.pos.x + 1, player.pos.y - 1 ))
                {
                    player.dir = upright;
                    player.vel.y = -1;
                    player.vel.x = 1;
                }
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);

            break;

            case downleft:

                if(mapCollisions(player.pos.x - 1, player.pos.y + 1 ))
                {   
                    player.dir = downleft;
                    player.vel.y = 1;
                    player.vel.x = -1;
                }
                SPR_setAnim(player.sprite, DOWNLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);

            break;

            case downright:

                if(mapCollisions(player.pos.x + 1, player.pos.y + 1 ))
                {
                    player.dir = downright;
                    player.vel.y = 1;
                    player.vel.x = 1;  
                }
                SPR_setAnim(player.sprite, DOWNLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);

            break;

            default:
                break;
        }
    }
    else if(player.moving == FALSE)
    {
        switch(player.dir)
        {
            case up:
            SPR_setAnim(player.sprite, UPIDLE); 
            SPR_setHFlip(player.sprite, FALSE); 
            break;

            case upleft:
            SPR_setAnim(player.sprite, UPLEFTIDLE);
            SPR_setHFlip(player.sprite, FALSE); 
            break;

            case upright:
            SPR_setAnim(player.sprite, UPLEFTIDLE);
            SPR_setHFlip(player.sprite, TRUE);
            break;

            case down:
            SPR_setAnim(player.sprite, DOWNIDLE); 
            SPR_setHFlip(player.sprite, FALSE); 
            break;

            case downleft:
            SPR_setAnim(player.sprite, DOWNLEFTIDLE); 
            SPR_setHFlip(player.sprite, FALSE);
            break;

            case downright:
            SPR_setAnim(player.sprite, DOWNLEFTIDLE); 
            SPR_setHFlip(player.sprite, TRUE);
            break;

            case left:
            
            SPR_setAnim(player.sprite, LEFTIDLE);
            SPR_setHFlip(player.sprite, FALSE);  
            break;
                    
            case right:
            SPR_setAnim(player.sprite, LEFTIDLE); 
            SPR_setHFlip(player.sprite, TRUE);
            break;
                    
            default:
            break;
        }
    }          
}


void moveSpeed()
{   
    
        player.pos.x +=player.vel.x;
	    player.pos.y += player.vel.y;
        SPR_setPosition(player.sprite,player.pos.x,player.pos.y);

}

int main()
{
    JOY_init();
    JOY_setEventHandler(myJoyHandler);

    VDP_loadTileSet(LVL.tileset, 1, DMA);
    PAL_setPalette(PAL1, LVL.palette->data,DMA);

    loadLevel();
    
    VDP_drawImage(BG_A, &LVL, 0, 0);
    
    SPR_init();

    Entity* b = bullet;
	for(i = 0 ; i< MAX_BULLETS;i++)
	{
		b->pos.x = 0;
		b->pos.y = -10;
		b->w =8;
		b->h = 8;
		b->sprite = SPR_addSprite(&Bullet,bullet[0].pos.x,bullet[0].pos.y,TILE_ATTR(PAL1,0,FALSE,FALSE));		
		sprintf(b->name, "Bu%d",i);
		b++;
	}
    

    player.sprite = SPR_addSprite(&Soldier, player.pos.x, player.pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
    PAL_setPalette(PAL2, Soldier.palette->data, DMA);

    SPR_update();
    

    while(1)
    {
      Animator();

       
      moveingIsFalse();
      moveSpeed();
      positionBullets();
      SPR_update();
      SYS_doVBlankProcess();
	}
	return(0);
    
}


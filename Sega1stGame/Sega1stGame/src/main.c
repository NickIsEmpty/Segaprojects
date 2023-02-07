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

#define XENOM_UP 0
#define XENOM_UP_RIGHT 1
#define XENOM_RIGHT 2
#define XENOM_DOWN_RIGHT 3
#define XENOM_DOWN 4
#define XENOM_DEATH 5

#define RIGHTEDGE 262
#define LEFTEDGE 20
#define TOPEDGE 30
#define BOTTOMEDGE 210

#define MAP_HEIGHT 28
#define MAP_WIDTH 40

#define MAX_BULLETS 11
#define MAX_ENEMIES 3

typedef u8 map[MAP_HEIGHT][MAP_WIDTH];

map level1 = 
{   	
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
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
        }
    }
}

typedef struct
{
    u8 x;
    u8 y;
} Point;

typedef enum {up,upleft,upright,down,downleft,downright,left,right,death,none} moveDirection;
typedef enum {Up, Down, Left, Right, upLeft, upRight, downLeft, downRight,None} idleDirection;

typedef struct
{
    Point pos;
    Point vel;
    int w;
    int h;
    int health;
    bool moving;
    bool isShooting;
    moveDirection dir;
    idleDirection idle;
    Sprite *sprite;
    char name[6];
} Entity;

Entity player = {{205,65},{0,0}, 32, 32, 100, FALSE,FALSE, up, None, NULL, "PLAYER"};
Entity xenom [MAX_ENEMIES];
Entity bullet [MAX_BULLETS];

int i = 0;
int ticks;
int delay;

int collideEntities(Entity* a, Entity* b)
{
    return (a->pos.x <= b->pos.x + b->w && a->pos.x + a->w >= b->pos.x && a->pos.y <= b->pos.y + b->h && a->pos.y + a->h >= b->pos.y);
}

void killEntity(Entity* e)
{
    e->health = 0;
	SPR_setVisibility(e->sprite,HIDDEN);
}

void reviveEntity(Entity* e, int HP)
{
	e->health = HP;
	SPR_setVisibility(e->sprite,VISIBLE);
}

bool checkCollisions(s16 x, s16 y, u8 width , u8 height, Entity* e )
{
    s16 y_tile = y >> 3;
	s16 x_tile = x >> 3;
	
	u8 player_width = width;
	u8 player_height = height;
	
	s16 leftTile = x_tile;
	s16 rightTile = x_tile + player_width;
	s16 topTile = y_tile;
	s16 bottomTile = y_tile + player_height;
	
	for(s16 i=leftTile; i <= rightTile; i++)
	{
		for(s16 j=topTile; j<=bottomTile; j++)
		{
			if(level1[j][i] == 0) 
            {
                if (e->dir == up && j == topTile)
                {
                    e->moving = FALSE;      
                }
                else if( e->dir == down && j == bottomTile)
                {
                    e->moving = FALSE;  
				}
                else if (e->dir == left && i == leftTile)
                {
                    e->moving = FALSE;   
                }
                else if (e->dir == right && i == rightTile)
                {
                    e->moving = FALSE;   
                }
                else if (e->dir == upright && (i == rightTile || j == topTile))
                {
                    e->moving = FALSE;
                }
                else if (e->dir == upleft && (i == leftTile || j == topTile))
                {
                    e->moving = FALSE;
                }
                else if (e->dir == downright && (i == rightTile || j == bottomTile))
                {
                    e->moving = FALSE;
                }
                else if (e->dir == downleft && (i == leftTile || j == bottomTile))
                {
                    e->moving = FALSE;
                }
                return FALSE;
			}  
		}
	}
	return TRUE;
}

void shootBullet(Entity Shooter)
{
    u16 i = 0;
    Entity *b;

    for( i = 0; i < MAX_BULLETS; i++)
    {
        b = &bullet[i];
        if(b->health == 0 && Shooter.health > 0)
        {
            
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
                b->pos.x = Shooter.pos.x;
                b->pos.y = Shooter.pos.y;
                b->vel.y = -3;
                b->vel.x = -3;
                SPR_setVFlip(b->sprite, TRUE);
                break;

                case upright:
                b->pos.x = Shooter.pos.x + 32;
                b->pos.y = Shooter.pos.y;
                b->vel.y = -3;
                b->vel.x = 3;
                SPR_setVFlip(b->sprite, FALSE);
                break;

                case downleft:
                b->pos.x = Shooter.pos.x ;
                b->pos.y = Shooter.pos.y + 32;
                b->vel.y = 3;
                b->vel.x = -3;
                SPR_setVFlip(b->sprite, TRUE);
                break;

                case downright:
                b->pos.x = Shooter.pos.x + 32;
                b->pos.y = Shooter.pos.y + 32;
                b->vel.y = 3;
                b->vel.x = 3;
                SPR_setVFlip(b->sprite, FALSE);
                break;
                
                case none:
                break;
            }
            reviveEntity(b, 1); 
            SPR_setPosition(b->sprite,b->pos.x,b->pos.y);
            break;
        }
    }
}

void positionBullets()
{
	u16 i = 0;
	Entity *b;
    Entity *e;
    int j = 0;

	for(i = 0; i < MAX_BULLETS; i++)
	{
		b = &bullet[i];

        b->pos.x += b->vel.x;
        b->pos.y += b->vel.y;

        for (j = 0; j < MAX_ENEMIES; j++)
        {
            e = &xenom[j];
            if(!checkCollisions(b->pos.x, b->pos.y, 1, 1, b) || (collideEntities(b,e) && e->health > 0))
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
}

void moveingIsFalse()
{
    if(player.moving == FALSE)
    {
        player.vel.x = 0;
        player.vel.y = 0;
    } 
}

void plrShooting(int fireRate)
{
    if(ticks % fireRate == 1)
    {
        if(player.isShooting == TRUE)
        {
            shootBullet(player);
            ticks = 1;
        }
        else if (player.isShooting == FALSE)
        {
        
        }   
    }  
}

void Animator()
{ 
        switch (player.dir)
        {
            case up:
            
            if(player.moving == TRUE)
            {
                if(checkCollisions(player.pos.x, player.pos.y - 1, 4, 4, &player))
                {  
                    player.vel.y = -1;
                    player.vel.x = 0; 
                }           
                SPR_setHFlip(player.sprite, FALSE);
                SPR_setAnim(player.sprite, UPWALK);
            } 
            break;

            case down:

               if(player.moving == TRUE) 
               {
                    if(checkCollisions(player.pos.x, player.pos.y + 1, 4, 4, &player))
                    {   
                        player.vel.y = 1;
                        player.vel.x = 0;
                    }
                    SPR_setHFlip(player.sprite, FALSE);
                    SPR_setAnim(player.sprite, DOWNWALK);
               }
            break;

            case left:

                if(player.moving == TRUE)
                {
                    if(checkCollisions(player.pos.x - 1, player.pos.y, 4, 4, &player))
                    {
                        player.vel.y = 0;
                        player.vel.x = -1;
                    } 
                    SPR_setAnim(player.sprite, LEFTWALK);
                    SPR_setHFlip(player.sprite, FALSE);
                }
            break;

            case right:

                if(player.moving == TRUE)
                {
                    if(checkCollisions(player.pos.x + 1, player.pos.y, 4, 4, &player))
                    {    
                        player.vel.y = 0;
                        player.vel.x = 1;
                    }  
                    SPR_setAnim(player.sprite, LEFTWALK);
                    SPR_setHFlip(player.sprite, TRUE);
                }
            break;

            case upleft:
            
            if(player.moving == TRUE)
            {    
                if(checkCollisions(player.pos.x - 1, player.pos.y - 1, 4, 4, &player))
                {
                    player.vel.y = -1;
                    player.vel.x = -1;
                }
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            }
            break;

            case upright:

            if (player.moving == TRUE)
            {    
                if(checkCollisions(player.pos.x + 1, player.pos.y - 1, 4, 4, &player))
                {
                    player.vel.y = -1;
                    player.vel.x = 1;
                }
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            }
            break;

            case downleft:

            if(player.moving == TRUE)
            {    
                if(checkCollisions(player.pos.x - 1, player.pos.y + 1, 4, 4, &player))
                {   
                    player.vel.y = 1;
                    player.vel.x = -1;
                }
                SPR_setAnim(player.sprite, DOWNLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            }
            break;

            case downright:

            if( player.moving == TRUE)
            {    
                if(checkCollisions(player.pos.x + 1, player.pos.y + 1, 4, 4, &player))
                {
                    player.vel.y = 1;
                    player.vel.x = 1;  
                }
                SPR_setAnim(player.sprite, DOWNLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            }
            break;

            default:
                break;
        }

    if(player.moving == FALSE)
    {  
        switch (player.idle)
        {
            case Up:
            SPR_setAnim(player.sprite, UPIDLE); 
            SPR_setHFlip(player.sprite, FALSE);
            break;

            case Down:
            SPR_setAnim(player.sprite, DOWNIDLE); 
            SPR_setHFlip(player.sprite, FALSE);
            break;

            case Left:
            SPR_setAnim(player.sprite, LEFTIDLE); 
            SPR_setHFlip(player.sprite, FALSE);
            break;

            case Right:
            SPR_setAnim(player.sprite, LEFTIDLE); 
            SPR_setHFlip(player.sprite, TRUE);
            break;

            case upLeft:
            SPR_setAnim(player.sprite, UPLEFTIDLE);
            SPR_setHFlip(player.sprite, FALSE); 
            break;

            case upRight:
            SPR_setAnim(player.sprite, UPLEFTIDLE);
            SPR_setHFlip(player.sprite, TRUE);
            break;
            
            case downLeft:
            SPR_setAnim(player.sprite, DOWNLEFTIDLE); 
            SPR_setHFlip(player.sprite, FALSE);
            break;
            
            case downRight:
            SPR_setAnim(player.sprite, DOWNLEFTIDLE); 
            SPR_setHFlip(player.sprite, TRUE);
            break; 
            
            case None:
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

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_UP)
        {     
            player.moving = TRUE;
            
            
            if(state & BUTTON_LEFT )
            {
                player.idle = upLeft;
                player.dir = upleft;
                player.moving = TRUE;  
            }
            else if (state & BUTTON_RIGHT )
            {   
                player.idle = upRight; 
                player.dir = upright;
                player.moving = TRUE;  
            } 
            else
            {
                player.idle = up;
                player.dir = up;
            }
        }
        else if (state & BUTTON_DOWN )
        {   
            
            player.moving = TRUE;

            if(state & BUTTON_LEFT )
            {
                player.idle = downLeft;
                player.dir = downleft;
                player.moving = TRUE;
            }
            else if(state & BUTTON_RIGHT )
            {
                player.idle = downRight;
                player.dir = downright;
                player.moving = TRUE;
            }
            else
            {
                player.dir = down;
                player.idle = Down;
            }
        }
        else if (state & BUTTON_LEFT )
        {   
            player.dir = left;
            player.idle = Left;
            player.moving = TRUE;
        }
        else if (state & BUTTON_RIGHT )
        {
            player.dir = right;
            player.idle = Right;
            player.moving = TRUE;
        }
        else
        {
            player.moving = FALSE;
        }  

    
        if (state & BUTTON_A)
        {
            player.isShooting = TRUE;      
        }
        else
        {
            player.isShooting = FALSE;
        }
    
          
    }
}

void enemySpawner(Entity * e)
{
	for(i = 0; i < MAX_ENEMIES; i++)
	{
		e = &xenom[i];
		e->pos.x = 45 + i*32;
		e->pos.y = 65;
		e->w = 32;
		e->h = 32;
		e->health = 1;

		e->sprite = SPR_addSprite(&Xenom,e->pos.x,e->pos.y,TILE_ATTR(PAL3,0,FALSE,FALSE));
        PAL_setPalette(PAL3, Xenom.palette->data, DMA);
		sprintf(e->name, "En%d",i);
		e++;
	}
}

void enemyAI(Entity *e)
{
    for( i = 0; i < MAX_ENEMIES; i++)
    {
        e = &xenom[i];
        if(e->pos.x + e->w < player.pos.x)
        {
            if(e->health > 0 &&  checkCollisions(e->pos.x +1 , e->pos.y , 4, 4, e))
            e->dir = right;      
        }
        else if (e->pos.x > player.pos.x + player.w)
        {
            if(e->health > 0 &&  checkCollisions(e->pos.x - 1 , e->pos.y , 4, 4, e))
            e->dir = left;
        }
        else if(e->pos.y + e->h < player.pos.y)
        {
            if(e->health > 0 &&  checkCollisions(e->pos.x , e->pos.y + 1, 4, 4, e))
            e->dir = down;
        }
        else if (e->pos.y > player.pos.y + player.h)
        {
            if(e->health > 0 &&  checkCollisions(e->pos.x , e->pos.y - 1, 4, 4, e))
            e->dir = up;
        }

        if(e->pos.x + e->w < player.pos.x  && e->pos.y + e->h < player.pos.y)
        {
            if(e->health > 0 &&  checkCollisions(e->pos.x + 1 , e->pos.y + 1, 4, 4, e))
            e->dir = downright;
        }
        else if(e->pos.x > player.pos.x + player.w && e->pos.y + e->h < player.pos.y)
        {
            if(e->health > 0 &&  checkCollisions(e->pos.x - 1, e->pos.y + 1, 4, 4, e))
            e->dir = downleft;
        }
        else if(e->pos.x + e->w < player.pos.x && e->pos.y > player.pos.y + player.h)
        {
            if(e->health > 0 &&  checkCollisions(e->pos.x + 1 , e->pos.y - 1, 4, 4, e))
            e->dir = upright;
        }
        else if(e->pos.x > player.pos.x + player.w && e->pos.y > player.pos.y + player.h)
        {
            if(e->health > 0 &&  checkCollisions(e->pos.x - 1  , e->pos.y - 1, 4, 4, e))
            e->dir = upleft;
        }
        
        
        if(e->moving == FALSE)
        {
            e->vel.x = 0;
            e->vel.y = 0;
        }

        if(collideEntities(e, &player))
        {
            e->vel.x = 0;
            e->vel.y = 0;
        }
    }

}

void enemyState(Entity* e)
{
    for( i = 0; i <= MAX_ENEMIES; i++)
    {
        e = &xenom[i];
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;

        switch (e->dir)
        {
            e = &xenom[i];
            case up:
            
                if(e->health > 0 && checkCollisions(e->pos.x , e->pos.y - 1, 4, 4, e))
                {
                    e->moving = TRUE;
                    e->vel.y = -1;
                    e->vel.x = 0; 
                    SPR_setAnim(e->sprite, XENOM_UP);
                }
                else if (e->health > 0 && checkCollisions(e->pos.x + 1 , e->pos.y , 4, 4, e) && e->pos.x < player.pos.x)
                {
                    e->dir = right;
                }
                else if (e->health > 0 && checkCollisions(e->pos.x + 1 , e->pos.y , 4, 4, e) && e->pos.x > player.pos.x)
                {
                    e->dir = left;
                }

            break;

            case down:

                if(e->health > 0 && checkCollisions(e->pos.x , e->pos.y + 1, 4, 4, e))
                {
                    e->moving = TRUE;
                    e->vel.y = 1;
                    e->vel.x = 0;
                    SPR_setAnim(e->sprite, XENOM_DOWN); 
                }
                else if (e->health > 0 && checkCollisions(e->pos.x + 1 , e->pos.y , 4, 4, e) && e->pos.x < player.pos.x)
                {
                    e->dir = right;
                }
                else if (e->health > 0 && checkCollisions(e->pos.x + 1 , e->pos.y , 4, 4, e) && e->pos.x > player.pos.x)
                {
                    e->dir = left;
                }

            break;

            case left:

                if(e->health > 0 && checkCollisions(e->pos.x - 1 , e->pos.y, 4, 4, e))
                {
                    e->moving = TRUE;
                    e->vel.y = 0;
                    e->vel.x = -1;
                    SPR_setHFlip(e->sprite, TRUE);
                    SPR_setAnim(e->sprite, XENOM_RIGHT);
                }
                else if (e->health > 0 && checkCollisions(e->pos.x  , e->pos.y - 1 , 4, 4, e) && e->pos.y > player.pos.y)
                {
                    e->dir = up;
                }
                else if (e->health > 0 && checkCollisions(e->pos.x  , e->pos.y + 1 , 4, 4, e) && e->pos.y < player.pos.y)
                {
                    e->dir = down;;
                }    
            
            break;

            case right:

                if(e->health > 0 && checkCollisions(e->pos.x  + 1, e->pos.y, 4, 4, e))
                {
                    e->moving = TRUE;
                    e->vel.y = 0;
                    e->vel.x = 1;
                    SPR_setHFlip(e->sprite, FALSE); 
                    SPR_setAnim(e->sprite, XENOM_RIGHT); 
                } 
                else if (e->health > 0 && checkCollisions(e->pos.x  , e->pos.y - 1 , 4, 4, e) && e->pos.y > player.pos.y)
                {
                    e->dir = up;
                }
                else if (e->health > 0 && checkCollisions(e->pos.x  , e->pos.y + 1 , 4, 4, e) && e->pos.y < player.pos.y)
                {
                    e->dir = down;;
                }  

            break;

            case upleft:

                if(e->health > 0 && checkCollisions(e->pos.x - 1 , e->pos.y - 1, 4, 4, e))
                {
                    e->moving = TRUE;
                    e->vel.y = -1;
                    e->vel.x = -1;
                    SPR_setHFlip(e->sprite, TRUE);
                    SPR_setAnim(e->sprite, XENOM_UP_RIGHT);
                }
                else
                {
                    e->dir = left;
                }

                break;

                case upright:

                if(e->health > 0 && checkCollisions(e->pos.x + 1 , e->pos.y - 1, 4, 4, e))
                {   
                    e->moving = TRUE;
                    e->vel.y = -1;
                    e->vel.x = 1;
                    SPR_setHFlip(e->sprite, FALSE);
                    SPR_setAnim(e->sprite, XENOM_UP_RIGHT);
                }
                else 
                {
                    e->dir = right;
                } 

            break;

            case downleft:

                if(e->health > 0 && checkCollisions(e->pos.x - 1 , e->pos.y + 1, 4, 4, e))
                {
                    e->moving = TRUE;
                    e->vel.y = 1;
                    e->vel.x = -1;
                    SPR_setHFlip(e->sprite, TRUE);
                    SPR_setAnim(e->sprite, XENOM_DOWN_RIGHT);
                }
                else
                {
                    e->dir = left;
                }
            
            break;

            case downright:

                if(e->health > 0 && checkCollisions(e->pos.x + 1 , e->pos.y + 1, 4, 4, e))
                {
                    e->moving = TRUE;
                    e->vel.y = 1;
                    e->vel.x = 1;
                    SPR_setHFlip(e->sprite, FALSE);
                    SPR_setAnim(e->sprite, XENOM_DOWN_RIGHT);
                }

            break;

            case none:
            break;

            case death:

                e->vel.x = 0;
                e->vel.y = 0;
                e->health = 0;  
                delay++;

                SPR_setAnim(e->sprite,XENOM_DEATH);
                if(delay % 29 == 0)
                {
                    killEntity(e);
                    delay = 0;
                }

            break;

            default:
            break;
        }
        SPR_setPosition(e->sprite, e->pos.x, e->pos.y);
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
		b = &bullet[i];	
		if(b->health > 0)
		{
				for(j = 0 ; j < MAX_ENEMIES; j++)
				{
					e = &xenom[j];
					if(e->health > 0)
					{
						if( collideEntities(b,e))
						{
							//killEntity(b);
                            e->dir = death;
                            //killEntity(e);
                            
                            break;
							
						}
					}
					
				}
			}
			
		}   
	}


int main()
{
    JOY_init();
    JOY_setEventHandler(myJoyHandler);

    VDP_loadTileSet(LVL.tileset, 1, DMA);
    PAL_setPalette(PAL0, LVL.palette->data,DMA);
    
    loadLevel();  
    VDP_drawImage(BG_A, &LVL, 0, 0);
    
    SPR_init();

    enemySpawner(xenom);

    Entity* b = bullet;
	for(i = 0 ; i< MAX_BULLETS;i++)
	{
		b->pos.x = 0;
		b->pos.y = 0;
		b->w =8;
		b->h = 8;
        b->health = 1;
		b->sprite = SPR_addSprite(&Bullet,bullet[i].pos.x,bullet[i].pos.y,TILE_ATTR(PAL1,0,FALSE,FALSE));
        PAL_setPalette(PAL1, Bullet.palette->data, DMA);	
		sprintf(b->name, "Bu%d",i);
		b++;
	}

    player.sprite = SPR_addSprite(&Soldier, player.pos.x, player.pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
    PAL_setPalette(PAL2, Soldier.palette->data, DMA);

    
    SPR_update();
    
    while(1)
    {
      if(delay == 60)
      {
        delay = 0;
      }
      ticks++;
      if(ticks == 60)
      {
        ticks = 0;
      }

      enemyState(xenom);
      
      Animator();
	  
      plrShooting(15);

      enemyAI(xenom);
      handlerCollisions(&bullet,&xenom);

      moveingIsFalse();
      positionBullets();
      moveSpeed();
      SPR_update();
      SYS_doVBlankProcess();
	}
	return(0);
    
}


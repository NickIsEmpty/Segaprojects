#include <genesis.h>
#include <resources.h> 	
#include <string.h>		

#define WALKRIGHT 0
#define CROUCH 1
#define JUMP 2
#define MAX_OBSTACLES 3
#define MAX_POINTS 3
#define MAX_POINT_TREE 3

bool gameON = FALSE;

int ground = 0;

typedef struct{u16 x;u16 y;} Point;
typedef enum
{jump, crouch, walk, death} moveDirection;

typedef struct
{
    Point pos;
    Point vel;
    int w;
    int h;
    int health;
    int dirIntX;
    int dirIntY;
    moveDirection dir;
    Sprite *sprite;
    bool onGround;
    int animInd;
} Entity;

typedef struct
{
    Point pos;
    Point vel;
    int w;
    int h;
    int dirIntX;
    int dirIntY;
    Sprite *sprite;
} Obstacle;

Point cursorPos;

Entity player = {{10, 90}, {0, 0}, 50, 75, 100, 0, 0, walk, NULL, TRUE,0};
Entity manhole[MAX_OBSTACLES];
Entity hugoPoint[MAX_POINTS];
Entity pointTree[MAX_POINT_TREE];

int i = 0;
int j = 0;
int score = 0;

char labelScore[7] = "SCORE:\0";
char strScore[4] = "0";

Image Lvl1Bg2;

void showText(char s[])						
{											 
	VDP_drawText(s, 20 - strlen(s)/2 ,15);	
}											

void updateInterface()
{
	VDP_clearText(7,2,3); 	
	sprintf(strScore,"%d",score); 
    VDP_drawText(labelScore,1,2);
	VDP_drawText(strScore,7,2);
}

void killEntity(Entity *e)
{
    e->health = 0;
    SPR_setVisibility(e->sprite,HIDDEN);
    SPR_releaseSprite(e->sprite);
}

int collideEntities(Entity *a, Entity *b)
{
    return (a->pos.x <= b->pos.x + b->w && a->pos.x + a->w >= b->pos.x && a->pos.y <= b->pos.y + b->h && a->pos.y + a->h >= b->pos.y);
}

void RefreshMainMenu()
{
    switch (gameON)
    {
        case FALSE:
            cursorPos.x = 8;
            VDP_drawText(">",cursorPos.x,cursorPos.y);
            VDP_drawText("START",10,10);
            VDP_drawText("EXIT",10,11);
            VDP_drawText("Press Start to select!!",10,25);
            break;

        case TRUE:
            VDP_clearTextArea(0,0,40,28);
            cursorPos.y = 10;
            break;
        
        default:
            break;
    } 
}

void spawnPlayer()
{
    SPR_init();
    player.sprite = SPR_addSprite(&Hugo1, player.pos.x, player.pos.y, TILE_ATTR(PAL1, 0,FALSE, FALSE));
    PAL_setPalette(PAL1,Hugo1.palette->data,DMA);
    SPR_update();
}

void ObstaclesSpawner(Entity *e)
{
    for (i = 0; i < MAX_OBSTACLES; i++)
    {
        e = &manhole[i];
        e->pos.x = 320 + i*150;
        e->w = 48;
        e->h = 16;
        e->pos.y = 170 - e->h/2;
        e->health = 1;
        e->dirIntX = -1;
        e->dirIntY = 0;
        e->dir = walk;
        e->sprite = SPR_addSprite(&Obstacle1, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
        PAL_setPalette(PAL2, Obstacle1.palette->data, DMA);
        e++;
    }
}

void hugoPoints(Entity *e, Entity *b)
{
    for (i = 0; i < MAX_POINTS; i++)
    {
        e = &hugoPoint[i];
        e->pos.x = 320 + i*100;
        e->w = 32;
        e->h = 48;
        e->pos.y = 40;
        e->health = 1;
        e->dirIntX = -1;
        e->dirIntY = 0;
        e->dir = walk;
        e->sprite = SPR_addSprite(&HugoPoint1, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
        PAL_setPalette(PAL2, HugoPoint1.palette->data, DMA);
        e++;
        
    }
    for (j = 0; j < MAX_POINTS; j++)
    {
        b = &pointTree[j];
        b->pos.x = 320 + j*100;
        b->w = 40;
        b->h = 40;
        b->pos.y = 0;
        b->health = 1;
        b->dirIntX = 0;
        b->dirIntY = 0;
        b->dir = walk;
        b->sprite = SPR_addSprite(&PointTree, b->pos.x, b->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
        PAL_setPalette(PAL2, PointTree.palette->data, DMA);
        b++;
    }
}

void StartGame()
{
    // PAL_setPalette(PAL0,Lvl1BG2.palette->data,DMA);
    // VDP_drawImageEx(BG_B,&Lvl1BG2,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,TILE_USER_INDEX),0 ,0,FALSE,TRUE);
    spawnPlayer();
    ObstaclesSpawner(manhole);
    hugoPoints(hugoPoint, pointTree);
    gameON = TRUE;
    ground = 90;
    
}

void playerAnimator()
{
    player.vel.x = 1;
    player.vel.y = 1;

    player.pos.x += player.vel.x * player.dirIntX;
    player.pos.y += player.vel.y * player.dirIntY;

    switch(player.dir)
    {
        case walk:
        SPR_setAnim(player.sprite, WALKRIGHT);
        break;

        case crouch:
        SPR_setAnim(player.sprite, CROUCH);
        break;

        case jump:
        player.sprite->timer = 0;

        if(player.onGround == FALSE && player.dirIntY == 0)
        {
            player.dirIntY = -1;
            SPR_setAnimAndFrame(player.sprite,JUMP, 0);
        }
        else if (player.pos.y == ground - 50 && player.onGround == FALSE)
        {
            player.dirIntY = 1;
            SPR_setAnimAndFrame(player.sprite,JUMP, 1);
        }
        break;
    }

    if(player.dirIntY == 1 && player.pos.y == ground)
    {
        player.onGround = TRUE;
        player.dir = walk;
        
    }

    if(player.onGround == TRUE)
    {
        player.dirIntY = 0;
    }

    SPR_setPosition(player.sprite, player.pos.x, player.pos.y);
    
}

void movePoints(Entity *e)
{
    for(i = 0; i < MAX_POINTS; i++)
    {
        e = &hugoPoint[i];
        e->vel.x = 2;
        e->dirIntX = -1;
        e->pos.x += e->vel.x * e->dirIntX; 

        if(e->pos.x <= 0)
        {
            killEntity(e);
            e->vel.x = 2;
            e->dirIntX = 0;
        }

        if(collideEntities(&player,e) && e->health > 0)
        {
            killEntity(e);
            score += 10;
        }
        SPR_setPosition(e->sprite,e->pos.x,e->pos.y);
    }
}

void moveObstacle(Entity *e, Entity *b)
{
   
    
    for(i = 0; i < MAX_OBSTACLES; i++)
    {

        e = &manhole[i];
        e->vel.x = 2;
        e->dirIntX = -1;
        e->pos.x += e->vel.x * e->dirIntX;
        SPR_setPosition(e->sprite,e->pos.x,e->pos.y);
        if(e->pos.x <= 0)
        {
            killEntity(e);
            e->vel.x = 2;
            e->dirIntX = 0;
        }

        if(collideEntities(&player,e))
        {
            killEntity(e);
        }

        

    } 
    for (j = 0; j < MAX_POINTS; j++)
    {
        b = &pointTree[j];
        b->vel.x = 2;
        b->dirIntX = -1;
        b->pos.x += b->vel.x * b->dirIntX;
        SPR_setPosition(b->sprite,b->pos.x,b->pos.y);
        if(b->pos.x <= 0)
        {
            killEntity(b);
            b->vel.x = 2;
            b->dirIntX = 0;
        }

        if(collideEntities(&player,b))
        {
            killEntity(b);
        }
    }

        

}


void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
    
        if(gameON == FALSE)
        {
        
            if(state & BUTTON_START)
            {
                switch (cursorPos.y)
                {
                    case 10:
                        RefreshMainMenu();
                        //loadLevel();
                        gameON = TRUE;
                        StartGame();
                        VDP_clearPlane(BG_A,FALSE);
                        break;
                    case 11:
                    
                        break;

                    default:
                        break;
                }  
            }
            else if(state & BUTTON_UP && cursorPos.y > 10)
            {
                VDP_clearText(8,cursorPos.y,1);
                cursorPos.y--;
                RefreshMainMenu();
            }
            else if(state & BUTTON_DOWN && cursorPos.y < 11)
            {
                VDP_clearText(8,cursorPos.y,1);
                cursorPos.y++;
                RefreshMainMenu();
            }
        }
        else if (gameON == TRUE)
        {
            if((state & BUTTON_UP) && player.onGround == TRUE)
            {
                player.onGround = FALSE;
                player.dir = jump;
            }
            else if((state & BUTTON_DOWN) && player.onGround == TRUE)
            {
                player.dir = crouch;
            }
            else if (player.onGround == TRUE)
            {
                player.dir = walk;
            }

        }
    }   

}

int main()
{
    JOY_init();
    JOY_setEventHandler(myJoyHandler);
    
    SPR_setFrameChangeCallback(player.sprite,playerAnimator);
	cursorPos.y = 10;
    RefreshMainMenu();
    while(1)
    {

        if(gameON == TRUE)
        {
            playerAnimator();
            moveObstacle(manhole, pointTree);
            movePoints(hugoPoint);
            updateInterface();
        }
        SPR_update();
        VDP_showFPS(TRUE);
        SYS_doVBlankProcess();
	}
	return(0);
    
}


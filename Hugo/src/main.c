#include <genesis.h>
#include <resources.h> 	
#include<string.h>	

#define WALKRIGHT 0
#define CROUCH 1
#define JUMP 2
#define MAX_OBSTACLES 1
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
Entity mAnhole[MAX_OBSTACLES];
Entity hugoPoint[MAX_POINTS];

Obstacle manhole = {{240,90},{2,0},56,16,-1,0,NULL};
Obstacle rock = {{240,90},{2,0},48,48,-1,0,NULL};
Obstacle trap = {{240,90},{2,0},48,24,-1,0,NULL};
Obstacle pointTree = {{240,0},{2,0},40,40,-1,0,NULL};
Obstacle pointTree2 = {{320,0},{2,0},40,80,-1,0,NULL};

Obstacle maNhole[5];


Obstacle obstacleArray[5];
Obstacle obstacles[MAX_OBSTACLES];


int i = 0;
int j = 0;
int score = 0;
int tick = 0;
int obstaclesOnScreen = 0;

char labelScore[7] = "SCORE:\0";
char strScore[4] = "0";
char strFrame[4] = "0";

u16 ind = TILE_USER_INDEX;


void spawnObstacles()
{
    int randObstacle = 0;
    Obstacle* e;
    int x  = 0; 
    if(obstaclesOnScreen <= 0)
    {
        for( i = 0; i< MAX_OBSTACLES; i++)
        {
            randObstacle = random()% 5;
            obstacles[i] = obstacleArray[randObstacle];
            e = &obstacles[i];
            e->pos.y = ground + x;
            e->pos.x = 320;
            e->vel.x = 1;
            e->vel.y = 1;
            e->dirIntX = -1;
            e->dirIntY = 0;

            switch (randObstacle)
            {
                case 0:
                    e->w = 56;
                    e->h = 48;
                    x = 165 - ground - e->h;
                    e->pos.y = ground + x;
                    e->sprite = SPR_addSprite(&Manhole, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, Manhole.palette->data, DMA);

                    break;
                case 1:
                    e->w = 48;
                    e->h = 48;
                    x = 165 - ground - e->h;
                    e->pos.y = ground + x;
                    e->sprite = SPR_addSprite(&Rock, e->pos.x, e->pos.y , TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, Rock.palette->data, DMA);
                    SPR_setAnim(e->sprite,0);
                    break;
                case 2:
                    e->w = 16;
                    e->h = 16;
                    x = 165 - ground - e->h;
                    e->pos.y = ground + x;
                    e->sprite = SPR_addSprite(&Trap, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, Trap.palette->data, DMA);
                    break;

                case 3:
                    e->w = 40;
                    e->h = 40;
                    e->pos.y = 0;
                    e->sprite = SPR_addSprite(&PointTree, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, PointTree.palette->data, DMA);
                    break;

                case 4:
                    e->w = 40;
                    e->h = 80;
                    e->pos.y = 0;
                    e->sprite = SPR_addSprite(&PointTree2, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, PointTree2.palette->data, DMA);
                    break;
                
                default:
                randObstacle = random()% 5;
                    break;
            }   
            obstaclesOnScreen++;  
        }
            
            
    }
}

void moveObstacles()
{
    Obstacle* e;
    int current = 0;
    for(int i = 0 ; i < MAX_OBSTACLES; i++)
    {
       
        e = &obstacles[i];
        e->pos.x += e->vel.x * e->dirIntX;
        SPR_setPosition(e->sprite,e->pos.x,e->pos.y);
        
        if(e->pos.x <= 0)
        {
            SPR_setVisibility(e->sprite, HIDDEN);
            SPR_releaseSprite(e->sprite);
            obstaclesOnScreen--;
        }
        
        if(obstaclesOnScreen <= 0)
        {
            obstaclesOnScreen = 0;
        }
    }

}

void showText(char s[])						
{											 
	VDP_drawText(s, 20 - strlen(s)/2 ,15);	
}											

void updateInterface()
{
	VDP_clearText(30,25,3); 	
	sprintf(strScore,"%d",score); 
	VDP_drawText(strScore,30,25);

    VDP_clearText(20,25,5); 	
    sprintf(strFrame,"%d",tick); 
	VDP_drawText(strFrame,20,25);
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
    player.pos.y = ground;
    SPR_init();
    PAL_setPalette(PAL3,Hugo1.palette->data,DMA);
    player.sprite = SPR_addSprite(&Hugo1, player.pos.x, player.pos.y, TILE_ATTR(PAL3, 0,FALSE, FALSE));
    SPR_update();
}


void StartGame()
{
    PAL_setPalette(PAL0,Lvl1BG2.palette->data,DMA);
    VDP_drawImageEx(BG_B,&Lvl1BG2,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0 ,0,FALSE,TRUE);
    ind+= Lvl1BG2.tileset->numTile;
    
    PAL_setPalette(PAL1,Lvl1BG1.palette->data,DMA);
    VDP_drawImageEx(BG_A,&Lvl1BG1,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),0 ,0,FALSE,TRUE);
    ind+= Lvl1BG1.tileset->numTile;

    gameON = TRUE;
    ground = 90;
    spawnPlayer();
    //ObstaclesSpawner(manhole);
    //hugoPoints(hugoPoint, pointTree);
    
    
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
                        VDP_clearPlane(BG_A,FALSE);
                        StartGame();
                        updateInterface();
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
    obstacleArray[0] = manhole;
    obstacleArray[1] = rock;
    obstacleArray[2] = trap;
    obstacleArray[3] = pointTree;
    obstacleArray[4] = pointTree2;

    while(1)
    {
        if(gameON == TRUE)
        {
            tick++;
            playerAnimator();
            spawnObstacles();
            moveObstacles();
            //moveObstacle(manhole, pointTree);
            //movePoints(hugoPoint);
            updateInterface();
        }
        SPR_update();
        VDP_showFPS(TRUE);
        SYS_doVBlankProcess();
	}
	return(0);
    
}



#include <genesis.h>
#include <resources.h> 	
#include<string.h>	

#define WALKRIGHT 0
#define CROUCH 1
#define JUMP 2

#define MAX_OBSTACLES 6
typedef enum 
{up ,down,left,right}moveDirection;

typedef struct 
{
    u16 x;
    u16 y;
} Point;

typedef struct 
{
    Point pos;
    Point vel;
    Point dir;
    int w;
    int h;
    moveDirection state;
    int health;
    bool onGround;
    int pixelHeight;
    Sprite* sprite;

}Entity;

typedef struct 
{
    Point pos;
    Point vel;
    Point dir;
    int w;
    int h;
    int health;
    bool canKill;
    int pixelHeight;
    int animFrames;
    Sprite* sprite;

}Obstacle;

typedef struct 
{
    Point pos;
    Sprite* sprite;

}UI;


Obstacle manhole = {{150,165},{1,1},{-1,0},0,0,1,TRUE,48,7,NULL};
Obstacle rock = {{150,165},{1,1},{-1,0},0,0,1,TRUE,48,6,NULL};
Obstacle trap = {{150,165},{1,1},{-1,0},0,0,1,TRUE,16,1,NULL};
Obstacle pointTree = {{150,0},{1,1},{-1,0},0,0,1,FALSE,0,1,NULL};
Obstacle pointTree2 = {{150,0},{1,1},{-1,0},0,0,1,FALSE,160,1,NULL};
Obstacle stickTree = {{240,90},{1,0},{-1,0},96,160,1,TRUE,160,6,NULL};

Obstacle obstacleArray[MAX_OBSTACLES];
Obstacle obstacles[MAX_OBSTACLES];


Entity player = {{0,0},{1,1},{0,0},80,80,right,3,TRUE,70,NULL};

bool gameON = FALSE;

int ground = 165;
int levelIndex = 1;
int ind = TILE_USER_INDEX;
int currentObstacle;
int obstaclesOnScreen = 0;
int i = 0;
int score = 0;
int ticks = 0;
int animTicks = 0;
int currentFrame = 0;

const int scrollSpeed = 1;

char labelScore[7] = "SCORE:\0";
char strScore[4] = "0";
char healthText[2];

s16 scrollValues_A[22] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
s16 scrollValues_B[22] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

UI healths;

void updateInterface()
{
	VDP_clearText(30,25,3); 	
	sprintf(strScore,"%d",score); 
	VDP_drawText(strScore,30,25);

    
    if(player.health < 0)
    {
        player.health = 0;
    }
  
    VDP_clearText(6,25,2); 	
    sprintf(healthText,"x%d",player.health);
    VDP_drawText(healthText,13,25);
        
}

int collideEntities(Entity *a, Obstacle *b)
{
    //return (a->pos.x <= b->pos.x + b->w && a->pos.x + a->w >= b->pos.x && a->pos.y <= b->pos.y + b->h && a->pos.y + a->h >= b->pos.y);
    return (a->pos.x <= b->pos.x + b->w && a->pos.x + a->w >= b->pos.x && a->pos.y + a->pixelHeight - a->h <= b->pos.y + b->h && a->pos.y + a->pixelHeight >= b->pos.y);
}


void PlayAnimByFrame(Sprite *sprite, Obstacle obstacle, int frameTime)
{
    animTicks = 0;
    currentFrame = 0;
    animTicks++;
    for(int  i= 0; i < obstacle.animFrames;i++)
    {
        if(animTicks %frameTime == 1)
        {
            SPR_setAnimAndFrame(obstacle.sprite,0,currentFrame);
            currentFrame++;
        }

    }
    if(currentFrame >= obstacle.animFrames)
    {
        currentFrame = 0;
    }
}

void spawnObstaces()
{
    int randomObstacle;
    int x;
    Obstacle *e;
    
    if( obstaclesOnScreen <= 0)
    {
        for( int i = 0; i < MAX_OBSTACLES; i++)
        {
            randomObstacle = random()% MAX_OBSTACLES;
            obstacles[i] = obstacleArray[randomObstacle];
            e = &obstacles[i];
            e->pos.y = ground + x;
            e->pos.x = 320;
            e->vel.x = 2;
            e->vel.y = 1;
            e->dir.x = -1;
            e->dir.y = 0;

            switch (randomObstacle)
            {
                case 0:
                    e->w = 56;
                    e->h = 48;
                    x = 165 - ground - e->h;
                    e->pos.y = ground + x;
                    e->canKill = obstacleArray[randomObstacle].canKill;
                    e->sprite = SPR_addSprite(&Manhole, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, Manhole.palette->data, DMA);

                    break;
                case 1:
                    e->w = 48;
                    e->h = 48;
                    x = 165 - ground - e->h;
                    e->pos.y = ground + x;
                    e->canKill = obstacleArray[randomObstacle].canKill;
                    e->sprite = SPR_addSprite(&Rock, e->pos.x, e->pos.y , TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, Rock.palette->data, DMA);
                    SPR_setAnim(e->sprite,0);
                    break;
                case 2:
                    e->w = 16;
                    e->h = 16;
                    x = 165 - ground - e->h;
                    e->pos.y = ground + x;
                    e->canKill = obstacleArray[randomObstacle].canKill;
                    e->sprite = SPR_addSprite(&Trap, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, Trap.palette->data, DMA);
                    break;
                case 3:
                    e->w = 0;
                    e->h = 0;
                    e->health = 0;
                    x = 0;
                    e->pos.y = 0;
                    e->canKill = obstacleArray[randomObstacle].canKill;
                    e->sprite = SPR_addSprite(&PointTree, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, PointTree.palette->data, DMA);
                    break;
                case 4:
                    e->w = 40;
                    e->h = 84;
                    x = 165 - ground - e->h;
                    e->pos.y = 0;
                    e->canKill = obstacleArray[randomObstacle].canKill;
                    e->sprite = SPR_addSprite(&PointTree2, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, PointTree2.palette->data, DMA);
                    break;
                case 5:
                    e->w = 40;
                    e->h = 86;
                    x = 165 - ground - e->h;
                    e->pos.y = 0;
                    e->sprite = SPR_addSprite(&StickTree, e->pos.x, e->pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
                    PAL_setPalette(PAL2, StickTree.palette->data, DMA);
                break;
                default:
                randomObstacle = random()% MAX_OBSTACLES;
                    break;
            }   
            obstaclesOnScreen++;
        }
    }
}


void LevelScroll(VDPPlane plane, int scrollFromTile, int scrollByTiles,int sameSpeedTillTile, int startSpeed, int increaseSpeedByValue)
{
    VDP_setScrollingMode(HSCROLL_TILE,VSCROLL_PLANE);
    

    for(i = 0; i < 22; i++)
    {
        switch(plane)
        {
            case BG_A:
            VDP_setHorizontalScrollTile(plane,scrollFromTile,scrollValues_A,scrollByTiles,CPU);
                if(i <= sameSpeedTillTile)
                {
                    scrollValues_A[i] -= startSpeed;
                } 
                else 
                {
                    scrollValues_A[i] -= (startSpeed + increaseSpeedByValue);
                }
                //if(scrollValues[i] <= -256) scrollValues[i] = 0;
            break;

            case BG_B:
            VDP_setHorizontalScrollTile(plane,scrollFromTile,scrollValues_B,scrollByTiles,CPU);
                if(i <= sameSpeedTillTile)
                {
                    scrollValues_B[i] -= startSpeed;
                } 
                else 
                {
                    scrollValues_B[i] -= (startSpeed + increaseSpeedByValue);
                }
                if(scrollValues_B[i] <= -320) scrollValues_B[i] = 0;
            break;
        }
        
    }
}

void moveObstacles()
{
    Obstacle *e;
         
    e = &obstacles[currentObstacle];
    e->pos.x += e->vel.x * e->dir.x;

    if(e->pos.x <= 0)
    {
        SPR_setVisibility(e->sprite, HIDDEN);
        SPR_releaseSprite(e->sprite);
        currentObstacle++;
        obstaclesOnScreen--;
    }

    if(obstaclesOnScreen <= 0)
    {
        obstaclesOnScreen = 0;
        currentObstacle = 0;
        spawnObstaces();
    }

    if(collideEntities(&player,e) && e->health > 0 )
    {
        switch(e->canKill)
        {
            case TRUE:
                player.health--;
                e->health = 0;
                //SPR_setVisibility(e->sprite,HIDDEN);
                PlayAnimByFrame(e->sprite,*e,30);
            break;
                

            case FALSE:
                score+=10;
                e->health = 0;
                SPR_setVisibility(e->sprite,HIDDEN);
            break;
        }
    }
    SPR_setPosition(e->sprite,e->pos.x,e->pos.y);  
}

void levelBackgrounds()
{
    VDP_clearPlane(BG_A,FALSE);
    VDP_clearPlane(BG_B,FALSE);
    healths.sprite = SPR_addSprite(&Health, 65, 175, TILE_ATTR(PAL3, 0,FALSE, FALSE));
    PAL_setPalette(PAL3,Health.palette->data,DMA);
    switch (levelIndex)
    {
        case 1:
            

            PAL_setPalette(PAL0,Lvl1BG2.palette->data,DMA);
            VDP_drawImageEx(BG_B,&Lvl1BG2,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0 ,0,FALSE,TRUE);
            ind+= Lvl1BG2.tileset->numTile;
        
            PAL_setPalette(PAL1,Lvl1BG1.palette->data,DMA);
            VDP_drawImageEx(BG_A,&Lvl1BG1,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),0 ,0,FALSE,TRUE);
            ind+= Lvl1BG1.tileset->numTile;
            
            break;
        case 2:
        
            
            break;
        case 3:
            
            break;
    
    }
}

void SpawnPlayer()
{
    player.pos.y = ground - player.h;
    player.health = 3;
    player.pixelHeight = 80;
    SPR_init();
    PAL_setPalette(PAL3,Hugo1.palette->data,DMA);
    player.sprite = SPR_addSprite(&Hugo1, player.pos.x, player.pos.y, TILE_ATTR(PAL3, 0,FALSE, FALSE));
}

void PlayerAnimations()
{
    player.vel.x = 1;
    player.vel.y = 1;

    player.pos.x += player.vel.x * player.dir.x;
    player.pos.y += player.vel.y * player.dir.y;

    switch(player.state)
    {
        case up:
            player.h = 80;
            player.sprite->timer = 0;
            if(player.onGround == FALSE && player.dir.y == 0)
            {
                player.dir.y = -1;
                SPR_setAnimAndFrame(player.sprite,JUMP, 0);
            }
            else if (player.pos.y + player.h == ground - 60 && player.onGround == FALSE)
            {
                player.dir.y = 1;
                SPR_setAnimAndFrame(player.sprite,JUMP, 1);
            }

        break;
        case down:
            player.h = 69;
            SPR_setAnim(player.sprite,CROUCH);
        break;
        case left:
            player.h = 80;
            player.vel.y = 0;
        break;
        case right:
            player.h = 80;
            player.vel.y = 0;
            SPR_setAnim(player.sprite,WALKRIGHT);
        break;

        default:
        break;
    }

    if(player.dir.y == 1 && player.pos.y + player.h == ground)
    {
        player.onGround = TRUE;
        player.state = right;
        
    }

    if(player.onGround == TRUE)
    {
        player.dir.y = 0;
    }

    SPR_setPosition(player.sprite,player.pos.x,player.pos.y);
}

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
    
        if(gameON == FALSE)
        {
        
            // if(state & BUTTON_START)
            // {
            //     switch (cursorPos.y)
            //     {
            //         case 10:
            //             RefreshMainMenu();
            //             //loadLevel();
            //             gameON = TRUE;
            //             VDP_clearPlane(BG_A,FALSE);
            //             StartGame();
            //             break;
            //         case 11:
                    
            //             break;

            //         default:
            //             break;
            //     }  
            // }
            // else if(state & BUTTON_UP && cursorPos.y > 10)
            // {
            //     VDP_clearText(8,cursorPos.y,1);
            //     cursorPos.y--;
            //     RefreshMainMenu();
            // }
            // else if(state & BUTTON_DOWN && cursorPos.y < 11)
            // {
            //     VDP_clearText(8,cursorPos.y,1);
            //     cursorPos.y++;
            //     RefreshMainMenu();
            // }
        }
        else if (gameON == TRUE)
        {
            if((state & BUTTON_UP) && player.onGround == TRUE)
            {
                player.onGround = FALSE;
                player.state = up;
            }
            else if((state & BUTTON_DOWN) && player.onGround == TRUE)
            {
                player.state = down;
            }
            else if (player.onGround == TRUE)
            {
                player.state = right;
            }

        }
    }   

}

int main()
{
    JOY_init();
    JOY_setEventHandler(myJoyHandler);


    obstacleArray[0] = manhole;
    obstacleArray[1] = rock;
    obstacleArray[2] = trap;
    obstacleArray[3] = pointTree;
    obstacleArray[4] = pointTree2;
    obstacleArray[5] = stickTree;

	//cursorPos.y = 10;
    //RefreshMainMenu();
    gameON = TRUE;

    SpawnPlayer();
    ground = 165;
    levelBackgrounds();
    spawnObstaces();
    while(1)
    {
        
        LevelScroll(BG_A,0,22,17,1,1);
        LevelScroll(BG_B,0,22,22,1,1);
        
        // if(player.pos.y + player.h < ground)
        // {
        //     player.onGround = FALSE;
        // }
        
        // if(player.pos.y + player.h == ground + 10)
        // {
        //     player.onGround = TRUE;
        //     player.dir.y = 0;
        // }

        // if(player.onGround == FALSE)
        // {
        //     player.dir.y = -1;
        // }
        moveObstacles();

        if(obstaclesOnScreen <= 0)
        {
            obstaclesOnScreen = 0;
            spawnObstaces();
        }
        updateInterface();
        PlayerAnimations();
        SPR_update();
        VDP_showFPS(TRUE);
        SYS_doVBlankProcess();
	}
	return(0);
    
}



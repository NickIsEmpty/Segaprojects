#include <genesis.h>
#include <resources.h> 	
#include <string.h>		

#define UPWALK 0
#define UPLEFTWALK 1
#define LEFTWALK 2
#define DOWNLEFTWALK 3
#define DOWNWALK 4

#define RIGHTEDGE 262
#define LEFTEDGE 20
#define TOPEDGE 30
#define BOTTOMEDGE 210

int playerSpeedx,playerSpeedy, playerValuex,playerValuey;
int x = 0, y = 0;


typedef struct
{
    u8 x;
    u8 y;
} Point;

typedef enum {up,upleft,upright,down,downleft,downright,left,right,none} moveDirection;

typedef struct
{
    Point pos;
    Point tilePos;
    Point vel;
    int w;
    int h;
    int health;
    bool moving;
    moveDirection dir;
    Sprite *sprite;
    char name[6];
} Entity;

Entity player = {{0, 0}, {0, 0},{0,0}, 8, 8, 0, FALSE, none, NULL, "PLAYER"};

Point playerValue, playerSpeed;

void movePlayer(moveDirection Direction)
{
    if (player.moving == FALSE)
    {

        switch (Direction)
        {
            case up:
                player.tilePos.y -= 1;
                player.moving = TRUE;
                player.dir = Direction;
                SPR_setAnim(player.sprite, UPWALK);
            break;

            /*case upleft:
                player.tilePos.y -= 1;
                player.tilePos.x -= 1;
                player.moving = TRUE;
                player.dir = Direction;
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            break;

            case upright:
                player.tilePos.y -= 1;
                player.tilePos.x += 1;
                player.moving = TRUE;
                player.dir = Direction;
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            break;*/

            case down:
                player.tilePos.y += 1;
                player.moving = TRUE;
                player.dir = Direction;
                SPR_setAnim(player.sprite, DOWNWALK);
            break;

             /*case downleft:
                player.tilePos.y += 1;
                player.moving = TRUE;
                player.dir = Direction;
                SPR_setAnim(player.sprite, DOWNWALK);
                SPR_setHFlip(player.sprite, FALSE);
                
            break;

            case downright:
                player.tilePos.y += 1;
                player.moving = TRUE;
                player.dir = Direction;
                SPR_setAnim(player.sprite, DOWNWALK);
                SPR_setHFlip(player.sprite, TRUE);
                
            break;*/

            case right:
                player.tilePos.x += 1;
                player.moving = TRUE;
                player.dir = Direction;
                SPR_setAnim(player.sprite, LEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            break;

            case left:
                player.tilePos.x -= 1;
                player.moving = TRUE;
                player.dir = Direction;
                SPR_setAnim(player.sprite, LEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            break;
            
            case none:
                player.vel.y = 0;
                player.vel.x = 0;
                player.moving = FALSE;
                player.dir = Direction;
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
            player.vel.y = -1;
            player.vel.x = 0;
            player.moving = TRUE;
            player.dir = up;
            SPR_setAnim(player.sprite, UPWALK);
                

            if(state & BUTTON_LEFT )
            {
                player.vel.y = -1;
                player.vel.x = -1;
                player.moving = TRUE;
                player.dir = upleft;
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            }
             if (state & BUTTON_RIGHT )
            {
                player.vel.y = -1;
                player.vel.x = 1;
                player.moving = TRUE;
                player.dir = upright;
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE); 
            } 
        }
        else if (state & BUTTON_DOWN )
        {
            player.vel.y = 1;
            player.vel.x = 0;
            player.moving = TRUE;
            player.dir = down;
            SPR_setAnim(player.sprite, DOWNWALK);

            if(state & BUTTON_LEFT )
            {
                player.vel.y = 1;
                player.vel.x = -1;
                player.moving = TRUE;
                player.dir = downleft;
                SPR_setAnim(player.sprite, DOWNLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            }
            else if(state & BUTTON_RIGHT )
            {
                player.vel.y = 1;
                player.vel.x = 1;
                player.moving = TRUE;
                player.dir = downright;
                SPR_setAnim(player.sprite, DOWNLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            }
        }
        else if (state & BUTTON_LEFT )
        {
            player.vel.y = 0;
            player.vel.x = -1;
            player.moving = TRUE;
            player.dir = left;
            SPR_setAnim(player.sprite, LEFTWALK);
            SPR_setHFlip(player.sprite, FALSE);
        }
        else if (state & BUTTON_RIGHT )
        {
            player.vel.y = 0;
            player.vel.x = 1;
            player.moving = TRUE;
            player.dir = right;
            SPR_setAnim(player.sprite, LEFTWALK);
            SPR_setHFlip(player.sprite, TRUE);
        }
        else
        {
            player.moving = FALSE;
            movePlayer(none);
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

int main()
{
    JOY_init();
    JOY_setEventHandler(myJoyHandler);
    VDP_setPlaneSize(40, 24, CPU);
    //u16 ind = TILE_USER_INDEX;
    
    
    PAL_setPalette(PAL0, LVL.palette->data, DMA);
    //VDP_drawImageEx(BG_B, &LVL, TILE_ATTR_FULL(PAL0, FALSE,FALSE,FALSE, ind),0, 0, FALSE, TRUE );
    VDP_drawImage(BG_B, &LVL,0,0);
    
    
	
     player.tilePos.x = x;
     player.tilePos.y = y;
     

    SPR_init();
    player.sprite = SPR_addSprite(&SoldWalk, player.pos.x, player.pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
    PAL_setPalette(PAL2, SoldWalk.palette->data, DMA);
    SPR_update();
    

    while(1)
    {
        
        if(player.moving == TRUE)
        {
            
            
            // switch(player.dir)
            // {
            //     case up:
            //     SPR_setAnim(player.sprite, UPWALK);
            //     break;

            //     case upleft:
                
            //     break;

            //     case upright:
                
            //     SPR_setAnim(player.sprite, UPLEFTWALK);
            //     SPR_setHFlip(player.sprite, TRUE);
            //     break;

            //     case down:
                
            //     break;

            //     case downleft:
                
            //     break;

            //     case downright:
                
            //     break;

            //     case left:
               
            //     break;
                
            //     case right:
                
            //     break;
            //     default:
            //     break;
            // }
        }

        playableZone();
        moveSpeed();
        SPR_update();
        SYS_doVBlankProcess();
	}
	return(0);
    
}


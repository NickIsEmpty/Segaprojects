#include <genesis.h>
#include <resources.h> 	
#include <string.h>		

#define UPWALK 0
#define UPLEFTWALK 1
#define LEFTWALK 2
#define LEFTBOTTWALK 3
#define DOWNWALK 4

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
    
        if (state & BUTTON_UP )
        {   
            //movePlayer(up);
            player.vel.y = -1;
            player.moving = TRUE;
                player.dir = up;
                SPR_setAnim(player.sprite, UPWALK);
        }
        else if (state & BUTTON_UP & BUTTON_LEFT )
        {
                player.vel.y = -1;
                player.vel.x = -1;
                player.moving = TRUE;
                player.dir = upleft;
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
        }
        else if (changed & BUTTON_UP & BUTTON_RIGHT )
        {
                player.vel.y = -1;
                player.vel.x = 1;
                player.moving = TRUE;
                player.dir = upright;
                SPR_setAnim(player.sprite, DOWNWALK);
                SPR_setHFlip(player.sprite, TRUE);
        }
        else if (state & BUTTON_DOWN )
        {
            //movePlayer(down);
                player.vel.y = 1;
               player.moving = TRUE;
                player.dir = down;
                SPR_setAnim(player.sprite, DOWNWALK);
        }
        else if (changed & BUTTON_DOWN & BUTTON_LEFT )
        {
                player.vel.y = 1;
                player.vel.x = -1;
                player.moving = TRUE;
                player.dir = downleft;
                SPR_setAnim(player.sprite, DOWNWALK);
                SPR_setHFlip(player.sprite, FALSE);
        }
        else if (state & BUTTON_DOWN & BUTTON_RIGHT )
        {
            player.vel.y = 1;
                player.vel.x = 1;
                player.moving = TRUE;
                player.dir = downright;
                SPR_setAnim(player.sprite, DOWNWALK);
                SPR_setHFlip(player.sprite, TRUE);
        }
        else if (state & BUTTON_LEFT )
        {
            //movePlayer(left);
                player.vel.x = -1;
                player.moving = TRUE;
                player.dir = left;
                SPR_setAnim(player.sprite, LEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
        }
        else if (state & BUTTON_RIGHT )
        {
           // movePlayer(right);
           
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

int main()
{
    JOY_init();
    JOY_setEventHandler(myJoyHandler);

    VDP_setPlaneSize(40, 24, CPU);
	
     player.tilePos.x = x;
     player.tilePos.y = y;
     

    SPR_init();
    player.sprite = SPR_addSprite(&SoldIdle, player.pos.x, player.pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
    PAL_setPalette(PAL2, SoldIdle.palette->data, DMA);
    SPR_update();
    

    while(1)
    {
        
        if(player.moving == TRUE)
        {
            
            
           /* switch(player.dir)
            {
                case up:
                player.pos.y -= 1;
                break;

                case upleft:
                player.pos.y -= 1;
                player.pos.x -= 1;
                break;

                case upright:
                player.pos.y -= 1;
                player.pos.x += 1;
                break;

                case down:
                player.pos.y += 1;
                break;

                case downleft:
                player.pos.y += 1;
                player.pos.x -= 1;
                break;

                case downright:
                player.pos.y += 1;
                player.pos.x += 1;
                break;

                case left:
                player.pos.x -= 1;
                break;
                
                case right:
                player.pos.x += 1;
                break;
                default:
                break;
            }*/
        }

        moveSpeed();
        SPR_update();
        SYS_doVBlankProcess();
	}
	return(0);
    
}


	#include <genesis.h>
	#include <resources.h> 	
	#include <string.h>		

    #define ANIM_RUN 0
    #define ANIM_JUMP 1

    Sprite* player;
    const int player_x = 32;
    int player_y = 112;

    Sprite* obstacle;
    int obstacle_x = 320;
    int obstacle_vel_x = 0;

    int score = 0;
    char score_lable[7] = "SCORE\0";
    char score_str[3] = "\0";
    bool score_added = FALSE;

    int player_x_value = 1;
	const int scrollSpeed = 2;

    char msg_start[22] = " PRESS START TO BEGIN!";
    char msg_reset[22] = " PRESS START TO RETRY!";

    bool game_on = FALSE;

    

    fix16 player_vel_y = FIX16(0);
    fix16 Player_y = FIX16(112);
    

    int player_height = 16;
    const int floor_height = 128;
    fix16 gravity = FIX16(0.2);
    bool jumping = FALSE;

    void showText(char s[])
    {
        VDP_drawText(s,20 - strlen(s)/2 ,10);
    }

    void clearText()
    {
        VDP_clearText(0,10,32);
    }

void updateScoreDisplay()
    {
        sprintf(score_str,"%d", score);
        VDP_clearText(1,2,3);
        VDP_drawText(score_str,1, 2);
    }

    void startGame()
    {
        if(game_on == FALSE)
        {
            game_on = TRUE;
            clearText();
            obstacle_x = 320;

            VDP_drawText(score_lable, 1,1);
            score = 0;
            updateScoreDisplay();
            
        }
    }

    void endGame()
    {
        if(game_on == TRUE)
        {
            showText(msg_reset);
            game_on = FALSE;
        }
    }

    void myJoyHandler(u16 joy, u16 changed, u16 state)
    {
        if(state & BUTTON_START)
        {
            if(game_on == FALSE)
            {
                startGame();
            }
        }

        if(state & BUTTON_C)
        {
            if(jumping == FALSE)
            {
                jumping = TRUE;
                player_vel_y = FIX16(-4);
                SPR_setAnim(player,ANIM_JUMP);
            }
        }
    }

    int main()
    {
		PAL_setColor(0,RGB24_TO_VDPCOLOR(0x6dc2ca));
		
        VDP_setPlanSize(32,32);

        VDP_loadTileSet(floor.tileset,1,DMA);
        VDP_loadTileSet(wall.tileset,2,DMA);
        VDP_loadTileSet(light.tileset,3,DMA);

        PAL_setPalette(PAL1, light.palette->data, DMA);

        PAL_setPalette(PAL2, runner.palette -> data,DMA);

		VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),0,16,32,1); //Пол 
        VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1,0,FALSE,TRUE,2),0,17,32,2); //Стена

        VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),0,19,32,1); //Пол на переднем плане
        VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1,0,FALSE,TRUE,2),0,20,32,8); //Стена на переднем плане

        VDP_fillTileMapRectInc(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,3),15,13,2,3); //Фонари


        SPR_init();
        player = SPR_addSprite(&runner,player_x,player_y,TILE_ATTR(PAL2,0,FALSE,FALSE));
        obstacle = SPR_addSprite(&rock, obstacle_x,128, TILE_ATTR(PAL2,0,FALSE,FALSE));
        SPR_update();
        SPR_setAnim(player,ANIM_RUN);

        JOY_init();
        JOY_setEventHandler( &myJoyHandler );

        showText(msg_start);

        
        
        s16 scrollValues[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
        int i = 0;
        while(1)
        {
			
			if(game_on == TRUE)
			{
                SPR_update();
                VDP_setScrollingMode(HSCROLL_TILE,VSCROLL_PLANE);
				VDP_setHorizontalScrollTile(BG_B,13,scrollValues,15,CPU);

                for(i=0; i<15; i++)
                {
                    if(i <= 5)
                    {
                        scrollValues[i] -= scrollSpeed;
                    } 
                    else 
                    {
                        scrollValues[i] -= (scrollSpeed+1);
                    }
                    if(scrollValues[i] <= -256) scrollValues[i] = 0;
                }

                //Добавление силы прыжка
                Player_y = fix16Add(Player_y,player_vel_y);

                if(jumping == TRUE) 
                {
                    player_vel_y = fix16Add(player_vel_y, gravity);
                }

                //Добавление гравитации
                if(jumping == TRUE && fix16ToInt(Player_y)+player_height >= (floor_height))
                {
                    jumping = FALSE;
                    player_vel_y = FIX16(0);
                    Player_y = intToFix16(floor_height-player_height);
                    SPR_setAnim(player, ANIM_RUN);
                    score_added = FALSE;
                }
                //Движение препятствий
                obstacle_vel_x = -scrollSpeed;
                obstacle_x = obstacle_x + obstacle_vel_x;

                if(obstacle_x < -8)
                {
                    obstacle_x = 320;
                }
                
                //Обработка столкновений
                if(player_x < obstacle_x + 8 && player_x + 8 > obstacle_x)
                {
                    if(jumping == FALSE)
                    {
                        endGame();
                    }

                    else
                    {
                        if(score_added == FALSE)
                        {
                            score++;
                            updateScoreDisplay();
                            score_added = TRUE;
                        }
                        
                    }
                }

                SPR_setPosition(obstacle, obstacle_x,120);
                SPR_setPosition(player, player_x,fix16ToInt(Player_y));
			}
            
            SYS_doVBlankProcess();
        }
        return (0);
    }


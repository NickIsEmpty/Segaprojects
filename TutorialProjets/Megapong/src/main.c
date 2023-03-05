#include <genesis.h>
#include <resources.h> 	//Позволяет нам использовать спрайты и тайлы , инициалищированные в файле resources.res
#include <string.h>		//Это дает нам доступ к некоторому коду, упрощающему работу со строками.

Sprite* ball; 			//Инициализация спрайта  код ля его дальнейшего использования как объекта
Sprite* player;			//Инициализация спрайта  код ля его дальнейшего использования как объекта

int player_pos_x = 144;
const int player_pos_y = 200;
int player_vel_x = 0;
const int player_width = 32;
const int player_height = 8;

int ball_pos_x = 100;
int ball_pos_y = 100;
int ball_vel_x = 1;
int ball_vel_y = 1;
int ball_width = 8;
int ball_height = 8;

const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 320;
const int TOP_EDGE = 0;
const int BOTTOM_EDGE = 224;

int score = 0;
char label_score[6] = "SCORE\0";
char str_score[4] = "0";

bool game_on = FALSE;
char msg_start[22] = "PRESS START TO BEGIN!\0";
char msg_reset[37] = "GAME OVER! PRESS START TO PLAY AGAIN.";

int flashing = FALSE; //Будет отслеживать, мигает ли шар в данный момент или нет
int frames = 0;		  //Поможет нам подсчитать прошедшие кадры, чтобы мы могли контролировать, как быстро и как долго будет мигать мяч
int ball_color = 0;	  //Будет хранить основной цвет мяча




int sign(int x) 
{
    return (x > 0) - (x < 0);
}

void showText(char s[])						
{											//Эта функция принимает строку (то есть char[]), 
	VDP_drawText(s, 20 - strlen(s)/2 ,15);	//а затем рисует эту строку в центре экрана,
}											//используя VDP_drawText и силу математики.
											
void endGame()
{
	showText(msg_reset);
	game_on = FALSE;
}

void updateScoreDisplay()
{
	sprintf(str_score,"%d",score); /*Берет целочисленное значение score и помещает его в переменную str_score. 
	                            	Проще говоря, он преобразует int в char[], чтобы мы могли использовать его для нашего HUD.*/

	VDP_clearText(1,2,3); 	/*Эта функция принимает 3 параметра: координату x (в тайлах), координату y (в тайлах) и длину (также в тайлах), которую мы хотим очистить. 
							  Если бы мы не очистили текст, все символы остались бы на экране до тех пор, пока они не будут заменены — если они когда-либо будут заменены.*/
	VDP_drawText(str_score,1,2);
}

void startGame(){
	score = 0;
	updateScoreDisplay();
	
	ball_pos_x = 0;
	ball_pos_y = 0;

	ball_vel_x = 1;
	ball_vel_y = 1;
	
	VDP_clearTextArea(0,10,40,10); //Очищает весь текст на экране

	game_on = TRUE;
}

void moveBall()
{
	//Проверяет горизантальные рамки
	if(ball_pos_x < LEFT_EDGE)
	{
		ball_pos_x = LEFT_EDGE;
		ball_vel_x = -ball_vel_x;
	} 
    else if(ball_pos_x + ball_width > RIGHT_EDGE)
	{
		ball_pos_x = RIGHT_EDGE - ball_width;
		ball_vel_x = -ball_vel_x;
	}

	//Проеряет вертикальные рамки
	if(ball_pos_y < TOP_EDGE)
	{
		ball_pos_y = TOP_EDGE;
		ball_vel_y = -ball_vel_y;
	} 
    else if(ball_pos_y + ball_height > BOTTOM_EDGE)
	{
		endGame();
	}

	//Позиция шарика
	ball_pos_x += ball_vel_x;
	ball_pos_y += ball_vel_y;

	/*Проверяет наличие столкновения с панелью игрока*/
	if(ball_pos_x < player_pos_x + player_width && ball_pos_x + ball_width > player_pos_x)
	{
		if(ball_pos_y < player_pos_y + player_height && ball_pos_y + ball_height >= player_pos_y)
		{
		//При соприкасновении отражает вектор движения мяча
			ball_pos_y = player_pos_y - ball_height - 1;
			ball_vel_y = -ball_vel_y;	

			score++;
			updateScoreDisplay();
			flashing = TRUE;

			if(score %1 == 0)
			{
				ball_vel_x+= sign(ball_vel_x);
				ball_vel_y+=sign(ball_vel_y);;
			}
		}
	}

	SPR_setPosition(ball,ball_pos_x,ball_pos_y);
}

void myJoyHandler( u16 joy, u16 changed, u16 state)
{

	/* Придает игроку силу движения при нажатии на левую или правую кнопку 
	   и  проверяет если конпка не нажата, то движение не происходит*/

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
			player_vel_x = 3;
		}

		else if( state & BUTTON_LEFT)
		{
			player_vel_x = -3;
		}

		else if( (changed & BUTTON_RIGHT)| (changed & BUTTON_LEFT))
		{
			player_vel_x = 0;
		}
	}

	
}

void positionPlayer()
{
	player_pos_x += player_vel_x; //Придает силу дыижения игрока 

	if(player_pos_x <LEFT_EDGE) player_pos_x = LEFT_EDGE; 									// Проверяет, вышел ли игрок за пределы левого края и не дает ему пересечь экран
	if(player_pos_x + player_width > RIGHT_EDGE) player_pos_x= RIGHT_EDGE - player_width; 	// Проверяет, вышел ли игрок за пределы правого края и не дает ему пересечь экран

	SPR_setPosition(player, player_pos_x, player_pos_y);
}



int main()
{

	VDP_setTextPlane(BG_A);
	VDP_drawText(label_score,1,1);
	updateScoreDisplay();
	
	JOY_init(); 							//Инициализирует joypad контроллер в SGDK. Без этого шага нвозможно будетосуществлять какой-либо ввод
	JOY_setEventHandler( &myJoyHandler);	//Устанавливает нашу определенную функцию в качестве обратного вызова для ввода с джойстика.

	//u16 ind = TILE_USER_INDEX;
	//PAL_setPalette(PAL0, bg1.palette->data,DMA);
	//VDP_drawImageEx(BG_B, &bg1, TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE, ind), 0, 0, FALSE, TRUE);

    SPR_init();
    ball = SPR_addSprite(&imgball,100,100,TILE_ATTR(PAL1,0, FALSE, FALSE));
    player = SPR_addSprite(&paddle, player_pos_x, player_pos_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));

    ball_color = PAL_getColor(22);

    VDP_loadTileSet(bgtile.tileset,1,DMA);
    PAL_setPalette(PAL1, bgtile.palette -> data, DMA);
    VDP_fillTileMapRect(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),0,0,40,30);

	VDP_setTextPlane(BG_A);
	VDP_drawText(label_score,1,1);	
	showText(msg_start);


    while(1)
    {
		
		if(game_on == TRUE)
		{
			moveBall();
			positionPlayer();

			if( flashing == TRUE )
			{
				frames++;
				if( frames % 4 == 0 )
				{
						
					PAL_setColor(22,ball_color);
				} 
				else if( frames % 2 == 0)
				{
					PAL_setColor(22,RGB24_TO_VDPCOLOR(0xffffff));
				}

				if(frames > 30)
				{
					flashing = FALSE;
					frames = 0;
					PAL_setColor(22,ball_color);
				}	
			}
		}
    	

		SPR_update();
        SYS_doVBlankProcess();

	}
	return(0);
    
}


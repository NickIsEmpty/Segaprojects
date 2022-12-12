#include <genesis.h>
#include <resources.h> 	
#include <string.h>		

#define PASS_X 16
#define PASS_Y 4
#define PASS_LENGTH 3


char passString[PASS_LENGTH+1] = "";

u16 currentIndex = 0;
Sprite *cursor;

typedef struct 
{
	u16 x;
	u16 y;
	char label[2];
}Option;

#define NUM_LETTERS 3

Option options[NUM_LETTERS] = 
{
	{16, 8, "A"},
    {16, 9, "B"},
    {16, 10, "C"},
};



void updateCursorPosition()
{
    SPR_setPosition(cursor, options[currentIndex].x*8-12, options[currentIndex].y*8);
}

void moveUp()
{
    if(currentIndex > 0)
	{
        currentIndex--;
        updateCursorPosition();
    }
}

void moveDown()
{
    if(currentIndex < NUM_LETTERS-1)
	{
        currentIndex++;
        updateCursorPosition();
    }
}

void updatePassString()
{
    //Update the passString
    VDP_drawText(passString,PASS_X,PASS_Y);
}

void checkPassword()
{
	if(strcmp(passString,"BAC") == 0)
	{
		VDP_drawText("LEVEL 2", PASS_X, 16);
	}
	else if(strcmp(passString, "AAC") == 0)
	{
		VDP_drawText("LEVEL 3", PASS_X, 16);
	}
	else
	{
		VDP_drawText("WRONG", PASS_X,16);

		//Если пароль неправильный , очистить строку прохода и вернуть заполнители
		passString[0] = '\0';
        VDP_drawText("---",PASS_X,PASS_Y);
        updatePassString();
	}
}

void select(){
    //Если все символы были введены, то проверяем пароль
    if(strlen(passString) == PASS_LENGTH)
    {
        checkPassword();
    }
    else
    {
        //Переносим буквы в passString
        strcat(passString,options[currentIndex].label);
        updatePassString();
    }
}


void joyEventHandler(u16 joy, u16 changed, u16 state)
{
    if (changed & state & BUTTON_UP)
    {
        moveUp();
    }
    else if(changed & state & BUTTON_DOWN){
        moveDown();
    }

	if(changed & state & BUTTON_C)
	{
		select();
	}
}




int main()
{
	JOY_init();
	JOY_setEventHandler(&joyEventHandler);

	SPR_init();
	cursor = SPR_addSprite(&gfx_cursor, 0, 0, 0);

	VDP_drawText("---",PASS_X,PASS_Y);

	u16 i = 0;
	for(i = 0; i < NUM_LETTERS; i++)
	{
		Option o = options[i];
		VDP_drawText(o.label, o.x, o.y);
	}

    while(1)
    {
		SPR_update();
        SYS_doVBlankProcess();

	}
	return(0);
    
}


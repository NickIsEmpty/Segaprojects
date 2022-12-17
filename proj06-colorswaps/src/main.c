#include <genesis.h>
#include <resources.h> 	
#include <string.h>		

u16 color_gray = -1;
u16 color_blue = -1;
u16 color_default = -1;

void swapToColor(u16 Col)
{
    PAL_setColor(18, Col);
}
void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1)
    {
        if(state & BUTTON_A)
        {
            swapToColor(color_gray);	
        }
        else if(state & BUTTON_B)
        {
            swapToColor(color_blue);
        }
        else if(state & BUTTON_C)
        {
            //swapToColor(color_default);
            PAL_setPalette(PAL1, runner.palette->data,DMA);
        }
    }
}


int main()
{

	JOY_init();
    JOY_setEventHandler(&myJoyHandler);

    color_gray = RGB24_TO_VDPCOLOR(0x808080);
    color_blue = RGB24_TO_VDPCOLOR(0x0000ff);
    //color_default = PAL_getPaletteColor(18,);
    
    PAL_setPalette(PAL1, runner.palette->data,DMA);

    SPR_init();
    for(int i = 0; i < 10; i++)
    {
        SPR_addSprite(&runner, 64+(i*16), 64,TILE_ATTR(PAL1,0,FALSE,FALSE));
    }
    SPR_update();

    while(1)
    {
        SPR_update();
        SYS_doVBlankProcess();

	}
	return(0);
    
}


#include <genesis.h>
#include <resources.h> 	
#include <string.h>		


bool paused = FALSE;

u16 colors[6] = {
    RGB24_TO_VDPCOLOR(0xFF0000),
    RGB24_TO_VDPCOLOR(0xFFFF00),
    RGB24_TO_VDPCOLOR(0x00FF00),
    RGB24_TO_VDPCOLOR(0x00FFFF),
    RGB24_TO_VDPCOLOR(0x0000FF),
    RGB24_TO_VDPCOLOR(0xFF00FF)
};

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if(changed & state & BUTTON_START)
    {
        if(paused == FALSE)
        {
            XGM_pausePlay();
            paused = TRUE;
        }
        else
        {
            XGM_resumePlay();
            paused = FALSE;
        }
    }
}


int main()
{
    JOY_init();
    JOY_setEventHandler(&myJoyHandler);

    XGM_setLoopNumber(-1);
    XGM_startPlay(track1);

    VDP_drawText("Welcome to Disco Zone!", 9, 13);

    u8 currentColor = 0;
    u8 ticker = 0;
	

    while(1)
    {
        if(paused == FALSE)
        {
            ticker++;
            if (ticker == 60)
            {
                ticker = 0;
                if (currentColor < 5)
                {
                    currentColor++;
                }
                else
                {
                    currentColor = 0;
                }
            
                PAL_setColor(15, colors[currentColor]);
            }
        }
		
        SYS_doVBlankProcess();

	}
	return(0);
    
}


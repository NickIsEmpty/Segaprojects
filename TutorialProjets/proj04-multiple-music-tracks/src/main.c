#include <genesis.h>
#include <resources.h> 	
#include <string.h>		

u8 current_track = 0;



int main()
{
    XGM_setLoopNumber(0);
    XGM_startPlay(&track1);
    current_track = 1;
	

    while(1)
    {
       if(current_track == 1 && XGM_getElapsed() == 490)
        {
            
            XGM_setLoopNumber(-1);
            XGM_startPlay(&track2);
            current_track = 2;
        }
		
        SYS_doVBlankProcess();

	}
	return(0);
    
}


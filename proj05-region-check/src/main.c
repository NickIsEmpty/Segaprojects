#include <genesis.h>
#include <resources.h> 	
#include <string.h>		


//u8 vers = *(u8 *)0xA10001; //Это сохранит шестнадцатеричное значение со всей информацией, которая нам нужна в версиях.
u8 *vers = (u8*)0xA10001;


char out[12] = "";

void CheckRegion()
{
    VDP_clearTextArea(2,5,17,2);
    sprintf(out,"HEX VALUE: %X ", *vers );
    VDP_drawText(out,2 ,4);

        if(*vers & (1 << 7))
        {
            VDP_drawText("REGION: NOT JAPAN",2,5);  
        } 
        else
        {
            VDP_drawText("REGION: JAPAN",2,5);  
        }

        if(*vers & (1 << 6))
        {  
           
            VDP_drawText("VIDEO: PAL",2,6);   
            
        } 
        else
        {
            VDP_drawText("VIDEO: NTSC",2,6); 
        }
}

int main()
{

    while(1)
    {
        CheckRegion();  
        SYS_doVBlankProcess();
	}
	return(0);
    
}


#include <genesis.h>
#include <resources.h> 	
#include <string.h>		







int main()
{

	VDP_setPlaneSize(32,128,TRUE);
	VDP_setTextPlane(BG_A);

	PAL_setColor(0,RGB24_TO_VDPCOLOR(0xA20000)); //Меняет цвет фона на красный
	VDP_loadTileSet(background.tileset,1,DMA); //Загружает тайлсет
	PAL_setPalette(PAL1,background.palette ->data,DMA);

	VDP_setTileMapEx(BG_B, background.tilemap, TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),0,12,0,0,32,18,DMA);
	/*The xp and yp properties define where on the target plane the graphic will be 
	drawn; we want it at tile-position 0,12. The x and y position specify the first 
	tile of the graphic that we want drawn; in our case, this is simply the very first 
	one (0,0) as we want to draw the whole image, but these properties can be useful 
	if you only want to draw parts of a bigger image. Finally, the w and h properties 
	define the width and height of the graphic to be drawn, respectively.*/

	s16 textPosX = 9;
	s16 textPosY = 30;


	VDP_drawText("THIS CITY WAS ONCE A", textPosX,textPosY);
	VDP_drawText("MOST EXCELLENT", textPosX,textPosY+1);
	VDP_drawText("PLACE... UNTIL ONE", textPosX,textPosY+2);
	VDP_drawText("DAY, A POWERFUL BUNCH", textPosX,textPosY+3);
	VDP_drawText("OF BAD DUDES", textPosX,textPosY+4);
	VDP_drawText("TOOK OVER.", textPosX,textPosY+5);
	VDP_drawText("THESE HEINOUS DUDES", textPosX,textPosY+10);
	VDP_drawText("SOON HAD CONTROL OF THE", textPosX,textPosY+11);
	VDP_drawText("GOVERNMENT AND EVEN", textPosX,textPosY+12);
	VDP_drawText("THE POLICE FORCE. THE", textPosX,textPosY+13);
	VDP_drawText("CITY HAS BECOME A", textPosX,textPosY+14);
	VDP_drawText("TYPICAL SETTING FOR", textPosX,textPosY+15);
	VDP_drawText("A BEAT 'EM UP.", textPosX,textPosY+16);
	VDP_drawText("BOGUS.", textPosX,textPosY+17);
	
	VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);
	fix16 offsetX = FIX16(0);
	fix16 offsetY = FIX16(0);

    while(1)
    {
	 offsetY = fix16Add(offsetY,FIX16(0.2));
	 offsetX = fix16Sub(offsetX,FIX16(0.3));

	 VDP_setHorizontalScroll(BG_B,fix16ToInt(offsetX));
	 VDP_setVerticalScroll(BG_A,fix16ToInt(offsetY));

	 /*First, we modify our offsets, then we apply them to the planes to get them 
	 scrolling. Our text plane (BG_A) will scroll upwards by 0.2 pixels each frame, 
	 while our city will scroll to the left by 0.3 pixels each frame. You can adjust 
	 these values as you see fit. Just note how we have to convert the offset values 
	 to type int before we pass them into the scrolling functions!*/

     SYS_doVBlankProcess();
	}
	return(0);
    
}


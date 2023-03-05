#include <genesis.h>
#include <resources.h> 	
#include <string.h>	


s16 offset_mask[6] = {0,5,10,15,20,25};
s16 offsetMaskLine[224]; 
s16 x_offset = 0; //Хранит смещение слоя по оси x.
s16 i = 0;

bool tileScroll = FALSE, planeScroll = FALSE;

int ScrollState = 0;



		

void TileScroll()
{
    	
	VDP_setScrollingMode(HSCROLL_TILE , VSCROLL_2TILE);
    VDP_setVerticalScrollTile(BG_A, 3, offset_mask, 6, CPU);
        for(i = 0; i < 6; i++) offset_mask[i] = offset_mask[i]+i;
        VDP_waitVSync();
       
}

void PlaneScroll()
{

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);//Здесь, мы устанавливаем режим скролла
    //VDP_setScrollingMode(горизонтальный_скролл, вертикальный_скролл)
    
    
    
       /*Смещение увеличивается каждый кадр на 10 пикселей. Что-бы смещение не 
        увеличивалось до бесконечности, я ограничил числом 256 (размер слоя по оси x).*/
		x_offset += 10;
		if(x_offset > 256) 
        {
			x_offset -= 256;
		}
		VDP_setHorizontalScroll(BG_A, x_offset);//установили слой для скролла (BG_A) и смещение x_offset.
        VDP_waitVSync();     
}

void LineScroll()
{
	
	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
	VDP_setHorizontalScrollLine(BG_A, 0, offsetMaskLine, 224, CPU);

	for(int a=0; a< 224; a++)
      offsetMaskLine[a] += random() % 10;  
   
	VDP_waitVSync();   
}

void ResetScroll()
{
    x_offset = 0; 
    i = 0; 
        
    VDP_setScrollingMode(FALSE,FALSE);
    VDP_setHorizontalScroll(BG_A, x_offset);  
      
    for(int a=0; a< 224; a++)
    {
       offsetMaskLine[a] = 0; 
       
    }  
    VDP_setHorizontalScrollLine(BG_A, 0, offsetMaskLine, 244, CPU); 
}



void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if(state & BUTTON_A & changed)
    {
        ResetScroll();
        ScrollState = 1;
    }
    else if (state & BUTTON_B & changed)
    {
        ResetScroll();
        ScrollState = 2;
    }
    else if (state & BUTTON_C)
    {
        ResetScroll();
        ScrollState = 3;
    }
    else if ( state & BUTTON_START & changed)
    {  
        
        ScrollState = 0;   
    }
    
}

void switchScroll()
{
    switch (ScrollState)
        {
            case 0:
                ResetScroll();
            break;

            case 1: 
                TileScroll();
            break;

            case 2: 
                PlaneScroll();
            break;

            case 3: 
                LineScroll();
            break;
        default:
        break;
       }
}

int main()
{
	JOY_init();
    JOY_setEventHandler(&myJoyHandler);

    VDP_setPlaneSize(32,32, TRUE);//указывает размер слоя в тайлах
    //VDP_setPlaneSize(ширина_в_тайлах,высота_в_тайлах, оптимизация_VRAM);(1 тайл = 8×8 px).

    VDP_drawImage(BG_A, &img2, 0, 0);

    while(1)
    {
		
       switchScroll();

        SYS_doVBlankProcess();
        
    }
   
   
    return (0);
}



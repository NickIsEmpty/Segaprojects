#include <genesis.h>
#include <resources.h> 	
#include <string.h>		

u16 cur_line = 0; //текущая линия
f16 v_offset = 0; //смещение плейна
f16 v_scroll_step = FIX16(3); //шаг увеличения смещения v_offset

void HIntHandler()
{
    VDP_setVerticalScroll(BG_A, cur_line+fix16ToInt(v_offset));
    v_scroll_step += FIX16(0.02); //Меняем шаг, тем самым, скорость движения плейна - увеличивается
    v_offset -= v_scroll_step;
}

void VIntHandler()
{
    cur_line += 1; //двигаем текущую линию, каждый кадр
    v_scroll_step = FIX16(3.0); //Сбрасывам шаг, с которым двигается плейн.
    v_offset = 0; 
 }


int main()
{
	VDP_drawImage(BG_A, &img, 0, 0);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    PAL_setPaletteColors(0, palette_black, 64);
    
    


    SYS_disableInts();
    {
        VDP_setHIntCounter(0);
        VDP_setHInterrupt(1);
        SYS_setHIntCallback(HIntHandler);
        SYS_setVIntCallback(VIntHandler);
        
        
    }
    SYS_enableInts();
    
    PAL_fadeIn(0, 15, img.palette->data, 32, FALSE);


    while (1)
    {
        SYS_doVBlankProcess();
    }
}

/*SYS_disableInts — отключаем прерывания, если этого не сделать, подпортятся вызовы VDP.
VDP_setHIntCounter — указываем, спустя сколько линий, вызывается прерывание, 0 значит, каждую линию, 4 значит, каждую 5-тую линию.
VDP_setHInterrupt — включаем горизонтальные (HBLANK) прерывания.
SYS_setHIntCallback — указываем функцию, которая будет вызываться, во время HBLANK прерывания.
SYS_setVIntCallback — определяем функцию, что вызывается, во время VBLANK прерывания.
SYS_enableInts — Прерывания настроены, можно включать.*/
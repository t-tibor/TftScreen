#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#include <TftScreen.h>
#include <TftScreen_prj.h>

void g_TFT_Init_vd(void)
{
	g_TFTSCREEN_InitPins_vd();
	_delay_ms(200);	
	g_TFTSCREEN_Write_vd(gd_ILI9488_CMD_SLEEPOUT_u8, 0, NULL);
	_delay_ms(200);
}

void g_TFT_GetId_vd(void)
{	

}



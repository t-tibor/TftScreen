#ifndef __TFT_PORT_H__
#define __TFT_PORT_H__

extern void g_TFTSCREEN_InitPins_vd(void);

extern void g_TFTSCREEN_Write_vd(const uint8_t f_Command_u8, const int f_DataCnt_i, const uint8_t* f_Data_pu8);

extern void g_TFTSCREEN_Read_vd(const uint8_t f_Command_u8, const int f_DataCnt_i, uint8_t* f_Data_pu8);

#endif
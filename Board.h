#ifndef __BOARD_H__
#define __BOARD_H__

extern void m_InitLed_vd(void);
extern void m_SetLed_vd(void);
extern void m_ClearLed_vd(void);

extern void m_InitUart_vd(void);
extern void m_UartWriteByte_vd(const uint8_t f_Byte_u8);
extern void m_UartWriteBytes_vd(const int f_BufferLength_i, const uint8_t* f_Buffer_u8);
extern void m_UartWriteString_vd(const char* f_Str_pc);

#endif //__BOARD_H__
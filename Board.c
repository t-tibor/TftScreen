#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#define md_LED_DDR_u8		(DDRB)
#define md_LED_DDR_PIN_u8	(DDB5)
#define md_LED_PORT_u8 		(PORTB)
#define md_LED_PIN_u8		(PORTB5)


void m_InitLed_vd(void)
{
	md_LED_DDR_u8 |= _BV(md_LED_DDR_PIN_u8);
}

void m_SetLed_vd(void)
{
	md_LED_PORT_u8 |= _BV(md_LED_PIN_u8);
}

void m_ClearLed_vd(void)
{
	md_LED_PORT_u8 &= ~_BV(md_LED_PIN_u8);
}

void m_InitUart_vd(void)
{
	const uint32_t l_UartBaudRate_u = 9600;
	const uint16_t l_Divider_u16 = (uint16_t)( ((uint32_t)F_CPU / (uint32_t)l_UartBaudRate_u / 16) - 1);

	// Initialize the Baud Rate Register
	UBRR0H = (uint8_t)(l_Divider_u16 >> 8);
	UBRR0L = (uint8_t)(l_Divider_u16 & 0x00FF);
	// Enable transmitter
	UCSR0B = (1<<TXEN0);
	// Set frame format (no parity, 8 data bits)
	UCSR0C = (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
}


void m_UartWriteByte_vd(const uint8_t f_Byte_u8)
{
	// Wait for previous transfer to finish
	while( 0 == (UCSR0A & (1<<UDRE0)) )
	{
		;
	}

	UDR0 = f_Byte_u8;
}

void m_UartWriteBytes_vd(const int f_BufferLength_i, const uint8_t* f_Buffer_u8)
{
	int l_i;

	for(l_i=0; l_i < f_BufferLength_i; l_i++)
	{
		m_UartWriteByte_vd(f_Buffer_u8[l_i]);
	}
}

void m_UartWriteString_vd(const char* f_Str_pc)
{
	uint8_t l_Byte_u8;

	while('\0' != *f_Str_pc)
	{
		l_Byte_u8 = (uint8_t)(*f_Str_pc);
		m_UartWriteByte_vd(l_Byte_u8);
		f_Str_pc++;
	}
}

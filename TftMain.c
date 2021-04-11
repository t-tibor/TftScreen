#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#define md_LED_DDR_u8		DDRB
#define md_LED_DDR_PIN_u8	DDB5
#define md_LED_PORT_u8 		PORTB
#define md_LED_PIN_u8		PORTB5
#define md_WAIT_TIME_u32	((uint32_t)3000)

static inline void m_InitLed_vd(void)
{
	md_LED_DDR_u8 |= _BV(md_LED_DDR_PIN_u8);
}

static inline void m_SetLed_vd(void)
{
	md_LED_PORT_u8 |= _BV(md_LED_PIN_u8);
}

static inline void m_ClearLed_vd(void)
{
	md_LED_PORT_u8 &= ~_BV(md_LED_PIN_u8);
}

int main(void)
{
	m_InitLed_vd();

	while(true)
	{
		m_SetLed_vd();
		_delay_ms( (double)md_WAIT_TIME_u32);
		m_ClearLed_vd();
		_delay_ms( (double)md_WAIT_TIME_u32 );
	}

	return 0;
}
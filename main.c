#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <util/delay.h>

#include <Board.h>

#define md_WAIT_TIME_u32	((uint32_t)3000)


int main(void)
{
	m_InitLed_vd();
	m_InitUart_vd();

	while(true)
	{
		m_SetLed_vd();
		_delay_ms( (double)md_WAIT_TIME_u32);
		m_ClearLed_vd();
		_delay_ms( (double)md_WAIT_TIME_u32 );

		m_UartWriteString_vd("Hello World!\r\n");
	}

	return 0;
}
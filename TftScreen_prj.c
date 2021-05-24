#include <avr/io.h>
#include <util/delay.h>

#include <TftScreen_prj.h>


// Pin mapping on the arduino uno board
/*
LCD_D0  -   Pin8    -   PB0
LCD_D1  -   Pin9    -   PB1

                        PD0 -   RX
                        PD1 -   Tx
LCD_D2  -   Pin2    -   PD2
LCD_D3  -   Pin3    -   PD3
LCD_D4  -   Pin4    -   PD4
LCD_D5  -   Pin5    -   PD5
LCD_D6  -   Pin6    -   PD6
LCD_D7  -   Pin7    -   PD7

LCD_RST -   A4      -   PC4
LCD_CS  -   A3      -   PC3
LCD_RS  -   A2      -   PC2
LCD_WR  -   A1      -   PC1
LCD_RD  -   A0      -   PC0
*/

#define md_TFTSCREEN_DATA_LOW_PORT_u8       (PORTB)
#define md_TFTSCREEN_DATA_HIGH_PORT_u8      (PORTD)
#define md_TFTSCREEN_DATA_LOW_PIN_u8        (PINB)
#define md_TFTSCREEN_DATA_HIGH_PIN_u8       (PIND)
#define md_TFTSCREEN_DATA_LOW_DDR_u8        (DDRB)
#define md_TFTSCREEN_DATA_HIGH_DDR_u8       (DDRD)
#define md_TFTSCREEN_DATA_LOW_MASK_bf8      ((uint8_t)0x03)
#define md_TFTSCREEN_DATA_HIGH_MASK_bf8     ((uint8_t)0xFC)

#define md_TFTSCREEN_CNTRL_PORT_pu8         (PORTC)
#define md_TFTSCREEN_CNTRL_DDR_pu8          (DDRC)

#define md_TFTSCREEN_RST_PIN_u8             (PORTC4)
#define md_TFTSCREEN_RST_MASK_u8            ((uint8_t)_BV(md_TFTSCREEN_RST_PIN_u8))

#define md_TFTSCREEN_CSX_PIN_u8             (PORTC3)
#define md_TFTSCREEN_CSX_MASK_u8            ((uint8_t)_BV(md_TFTSCREEN_CSX_PIN_u8))

#define md_TFTSCREEN_RS_PIN_u8              (PORTC2)
#define md_TFTSCREEN_RS_MASK_u8             ((uint8_t)_BV(md_TFTSCREEN_RS_PIN_u8))

#define md_TFTSCREEN_WR_PIN_u8              (PORTC1)
#define md_TFTSCREEN_WR_MASK_u8             ((uint8_t)_BV(md_TFTSCREEN_WR_PIN_u8))

#define md_TFTSCREEN_RD_PIN_u8              (PORTC0)
#define md_TFTSCREEN_RD_MASK_u8             ((uint8_t)_BV(md_TFTSCREEN_RD_PIN_u8))


#define md_TFTSCREEN_SET_DATA_DIR_OUT_mac()     do                                                                                      \
                                                {                                                                                       \
                                                    md_TFTSCREEN_DATA_LOW_DDR_u8    |= md_TFTSCREEN_DATA_LOW_MASK_bf8;                  \
                                                    md_TFTSCREEN_DATA_HIGH_DDR_u8   |= md_TFTSCREEN_DATA_HIGH_MASK_bf8;                 \
                                                }while(0)

#define md_TFTSCREEN_SET_DATA_DIR_IN_mac()      do                                                                                      \
                                                {                                                                                       \
                                                    md_TFTSCREEN_DATA_LOW_DDR_u8    &= ~(md_TFTSCREEN_DATA_LOW_MASK_bf8);               \
                                                    md_TFTSCREEN_DATA_HIGH_DDR_u8   &= ~(md_TFTSCREEN_DATA_HIGH_MASK_bf8);              \
                                                }while(0)                                                                                       
        

#define md_TFTSCREEN_SET_DATA_mac(f_data_u8)    do                                                                                      \
                                                {                                                                                       \
                                                    md_TFTSCREEN_DATA_HIGH_PORT_u8  =    (f_data_u8) & md_TFTSCREEN_DATA_HIGH_MASK_bf8; \
                                                    md_TFTSCREEN_DATA_LOW_PORT_u8   =    (f_data_u8) & md_TFTSCREEN_DATA_LOW_MASK_bf8;  \
                                                }while(0)    

#define md_TFTSCREEN_GET_DATA_mac(f_data_u8)    do{                                                                                     \
                                                    (f_data_u8) =   (md_TFTSCREEN_DATA_HIGH_PIN_u8 & md_TFTSCREEN_DATA_HIGH_MASK_bf8) | \
                                                                    (md_TFTSCREEN_DATA_LOW_PIN_u8  & md_TFTSCREEN_DATA_LOW_MASK_bf8);   \
                                                }while(0)

#define md_TFTSCREEN_SET_CSX_LOW_mac()          do{md_TFTSCREEN_CNTRL_PORT_pu8 &= (uint8_t)(~md_TFTSCREEN_CSX_MASK_u8);}while(0)                                                                                                          
#define md_TFTSCREEN_SET_CSX_HIGH_mac()         do{md_TFTSCREEN_CNTRL_PORT_pu8 |= (uint8_t)md_TFTSCREEN_CSX_MASK_u8;}while(0)

#define md_TFTSCREEN_SET_RS_CMD_mac()           do{ md_TFTSCREEN_CNTRL_PORT_pu8 &= (~md_TFTSCREEN_RS_MASK_u8); }while(0)

#define md_TFTSCREEN_SET_RS_DATA_mac()          do{ md_TFTSCREEN_CNTRL_PORT_pu8 |= md_TFTSCREEN_RS_MASK_u8; }while(0)

#define md_TFTSCREEN_PULSE_WR_mac()             do                                                                                      \
                                                {                                                                                       \
                                                    md_TFTSCREEN_CNTRL_PORT_pu8 &= (~md_TFTSCREEN_WR_MASK_u8);                          \
                                                    md_TFTSCREEN_CNTRL_PORT_pu8 |= md_TFTSCREEN_WR_MASK_u8;                             \
                                                }while(0)


#define md_TFTSCREEN_SET_RD_LOW_mac()           do{ md_TFTSCREEN_CNTRL_PORT_pu8 &= (~md_TFTSCREEN_RD_MASK_u8); }while(0)

#define md_TFTSCREEN_SET_RD_HIGH_mac()          do{ md_TFTSCREEN_CNTRL_PORT_pu8 |= md_TFTSCREEN_RD_MASK_u8;    }while(0)

#define md_TFTSCREEN_PULSE_RD_mac()             do                                                                                      \
                                                {                                                                                       \
                                                    md_TFTSCREEN_CNTRL_PORT_pu8 &= (~md_TFTSCREEN_RD_MASK_u8);                          \
                                                    md_TFTSCREEN_CNTRL_PORT_pu8 |= md_TFTSCREEN_RD_MASK_u8;                             \
                                                }while(0)                                                    


void g_TFTSCREEN_InitPins_vd(void)
{
    // Configure control pins as output.
    md_TFTSCREEN_CNTRL_DDR_pu8 |=   md_TFTSCREEN_RST_MASK_u8 | md_TFTSCREEN_CSX_MASK_u8 |
                                    md_TFTSCREEN_RS_MASK_u8 | md_TFTSCREEN_WR_MASK_u8 | md_TFTSCREEN_RD_MASK_u8;

    // Configure data pins as input
    md_TFTSCREEN_SET_DATA_DIR_IN_mac();
}


void g_TFTSCREEN_Write_vd(const uint8_t f_Command_u8, const int f_DataCnt_i, const uint8_t* f_Data_pu8)
{
    int l_i;

    // CS->0
    md_TFTSCREEN_SET_CSX_LOW_mac();
    // RS->0
    md_TFTSCREEN_SET_RS_CMD_mac();
    // Data dir out
    md_TFTSCREEN_SET_DATA_DIR_OUT_mac();
    // Data out
    md_TFTSCREEN_SET_DATA_mac(f_Command_u8);
    // WRX->0; WRX->1
    md_TFTSCREEN_PULSE_WR_mac();
    // RS->1
    md_TFTSCREEN_SET_RS_DATA_mac();

    // write all the data
    for(l_i=0; l_i<f_DataCnt_i; l_i++)
    {
        // data out
        md_TFTSCREEN_SET_DATA_mac(f_Data_pu8[l_i]);
        md_TFTSCREEN_PULSE_WR_mac();
    }

    // Data in
    md_TFTSCREEN_SET_DATA_DIR_IN_mac();
    // CS->1
    md_TFTSCREEN_SET_CSX_HIGH_mac();
}


void g_TFTSCREEN_Read_vd(const uint8_t f_Command_u8, const int f_DataCnt_i, uint8_t* f_Data_pu8)
{
    int l_i;

    // CS->0
    md_TFTSCREEN_SET_CSX_LOW_mac();
    // RS->0
    md_TFTSCREEN_SET_RS_CMD_mac();
    // Data dir out
    md_TFTSCREEN_SET_DATA_DIR_OUT_mac();
    // Data out
    md_TFTSCREEN_SET_DATA_mac(f_Command_u8);
    // WRX->0
    md_TFTSCREEN_PULSE_WR_mac();
    // RS->1
    md_TFTSCREEN_SET_RS_DATA_mac();
    // Data in
    md_TFTSCREEN_SET_DATA_DIR_IN_mac();

    // in case we want to get data back do a dummy cycle
    if( 0 < f_DataCnt_i )
    {
        md_TFTSCREEN_PULSE_RD_mac();
    }

    // write all the data
    for(l_i=0; l_i<f_DataCnt_i; l_i++)
    {
        md_TFTSCREEN_SET_RD_LOW_mac();
        md_TFTSCREEN_GET_DATA_mac(f_Data_pu8[l_i]);
        md_TFTSCREEN_SET_RD_HIGH_mac();
    }
    
    // CS->1
    md_TFTSCREEN_CNTRL_PORT_pu8 |= md_TFTSCREEN_CSX_MASK_u8;
}
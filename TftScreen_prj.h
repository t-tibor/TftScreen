#ifndef __TFT_PORT_H__
#define __TFT_PORT_H__

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

#define gd_TFTSCREEN_DATA_LOW_PORT_u8       (PORTB)
#define gd_TFTSCREEN_DATA_LOW_MASK_bf8      ((uint8_t)0x03)
#define gd_TFTSCREEN_DATA_HIGH_PORT_u8      (PORTD)
#define gd_TFTSCREEN_DATA_HIGH_MASK_bf8     ((uint8_t)0xFC)

#define gd_TFTSCREEN_RST_PORT_pu8           (PORTA)
#define gd_TFTSCREEN_RST_PIN_u8             (PORTA4)
#define gd_TFTSCREEN_RST_MASK_u8            ((uint8_t)_BV(gd_TFTSCREEN_RST_PIN_u8))

#define gd_TFTSCREEN_CSX_PORT_u8            (PORTA)
#define gd_TFTSCREEN_CSX_PIN_u8             (PORTA3)
#define gd_TFTSCREEN_CSX_MASK_u8            ((uint8_t)_BV(gd_TFTSCREEN_CSX_PIN_u8))

#define gd_TFTSCREEN_RS_PORT_u8             (PORTA)
#define gd_TFTSCREEN_RS_PIN_u8              (PORTA2)
#define gd_TFTSCREEN_RS_MASK_u8             ((uint8_t)_BV(gd_TFTSCREEN_RS_PIN_u8))

#define gd_TFTSCREEN_WR_PORT_u8             (PORTA)
#define gd_TFTSCREEN_WR_PIN_u8              (PORTA1)
#define gd_TFTSCREEN_WR_MASK_u8             ((uint8_t)_BV(gd_TFTSCREEN_WR_PIN_u8))

#define gd_TFTSCREEN_RD_PORT_u8             (PORTA)
#define gd_TFTSCREEN_RD_PIN_u8              (PORTA0)
#define gd_TFTSCREEN_RD_MASK_u8             ((uint8_t)_BV(gd_TFTSCREEN_RD_PIN_u8))


#define TFTSCREEN_SET_CSX_HIGH_mac()            do{ gd_TFTSCREEN_CSX_PORT_u8 |=  gd_TFTSCREEN_CSX_MASK_u8; }while(0)  
#define TFTSCREEN_SET_CSX_HIGH_mac()            do{ gd_TFTSCREEN_CSX_PORT_u8 &=  (uint8_t)(~gd_TFTSCREEN_CSX_MASK_u8); }while(0)  

#define gd_TFTSCREEN_SET_DATA_mac(f_data_u8)    do                                                                              \
                                                {                                                                               \
                                                    gd_TFTSCREEN_DATA_HIGH_PORT_u8  =    (f_data_u8) & gd_TFTSCREEN_DATA_HIGH_MASK_bf8;   \
                                                    gd_TFTSCREEN_DATA_LOW_PORT_u8   =    (f_data_u8) & gd_TFTSCREEN_DATA_LOW_MASK_bf8);   \
                                                }while(0)                                                                       






#endif
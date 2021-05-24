#ifndef __TFTSCREEN_H__
#define __TFTSCREEN_H__

// Commands
#define gd_ILI9488_CMD_NOP_u8                   ((uint8_t)0x00)
#define gd_ILI9488_CMD_SOFTRESET_u8             ((uint8_t)0x01)
#define gd_ILI9488_CMD_READDISPLAY_u8           ((uint8_t)0x04)
#define gd_ILI9488_CMD_READSTATUS_u8            ((uint8_t)0x09)
#define gd_ILI9488_CMD_READPOWERMODE_u8         ((uint8_t)0x0A)
#define gd_ILI9488_CMD_READMADCTL_u8            ((uint8_t)0x0B)
#define gd_ILI9488_CMD_READPXFORMAT_u8          ((uint8_t)0x0C)
#define gd_ILI9488_CMD_READIMGMODE_u8           ((uint8_t)0x0D)
#define gd_ILI9488_CMD_READSIGMODE_u8           ((uint8_t)0x0E)
#define gd_ILI9488_CMD_READDIAGRES_u8           ((uint8_t)0x0F)
#define gd_ILI9488_CMD_SLEEPIN_u8               ((uint8_t)0x10)
#define gd_ILI9488_CMD_SLEEPOUT_u8              ((uint8_t)0x11)
#define gd_ILI9488_CMD_PARTIALON_u8             ((uint8_t)0x12)
#define gd_ILI9488_CMD_NORMALMODEON_u8          ((uint8_t)0x13)
#define gd_ILI9488_CMD_DISPINVOFF_u8            ((uint8_t)0x20)
#define gd_ILI9488_CMD_DISPINVON_u8             ((uint8_t)0x21)
#define gd_ILI9488_CMD_ALLPIXELOFF_u8           ((uint8_t)0x22)   
#define gd_ILI9488_CMD_ALLPIXELON_u8            ((uint8_t)0x23)
#define gd_ILI9488_CMD_DISPLAYOFF_u8            ((uint8_t)0x28)
#define gd_ILI9488_CMD_DISPLAYON_u8             ((uint8_t)0x29)
#define gd_ILI9488_CMD_COLADDRSET_u8            ((uint8_t)0x2A)
#define gd_ILI9488_CMD_PAGEADDRSET_u8           ((uint8_t)0x2B)
#define gd_ILI9488_CMD_MEMWRITE_u8              ((uint8_t)0x2C)
#define gd_ILI9488_CMD_MEMREAD_u8               ((uint8_t)0x2E)
#define gd_ILI9488_CMD_PARTIALAREA_u8           ((uint8_t)0x30)
#define gd_ILI9488_CMD_VERTSCROLLDEF_u8         ((uint8_t)0x33)
#define gd_ILI9488_CMD_TEAREFFECTOFF_u8         ((uint8_t)0x34)
#define gd_ILI9488_CMD_TEAREFFECTON_u8          ((uint8_t)0x35)
#define gd_ILI9488_CMD_MEMACCCNTR_u8            ((uint8_t)0x36)
#define gd_ILI9488_CMD_VERTSCROLLSTARTADDR_u8   ((uint8_t)0x37)
#define gd_ILI9488_CMD_IDLEMODEOFF_u8           ((uint8_t)0x38)
#define gd_ILI9488_CMD_IDLEMODEON_u8            ((uint8_t)0x39)
#define gd_ILI9488_CMD_IFACEPIXELFORMAT_u8      ((uint8_t)0x3A)
#define gd_ILI9488_CMD_MEMWRITECONT_u8          ((uint8_t)0x3C)
#define gd_ILI9488_CMD_MEMREADCONT_u8           ((uint8_t)0x3E)
#define gd_ILI9488_CMD_WRTEARSCANLINE_u8        ((uint8_t)0x44)
#define gd_ILI9488_CMD_RDTEARSCANLINE_u8        ((uint8_t)0x45)
#define gd_ILI9488_CMD_WRDISPBRIGHTNESS_u8      ((uint8_t)0x51)
#define gd_ILI9488_CMD_RDDISPBRIGHTNESS_u8      ((uint8_t)0x52)
#define gd_ILI9488_CMD_WRCTRLDISPVALUE_u8       ((uint8_t)0x53)
#define gd_ILI9488_CMD_RDCTRLDISPVALUE_u8       ((uint8_t)0x54)

#define gd_ILI9488_CMD_RDID1_u8                 ((uint8_t)0xDA)
#define gd_ILI9488_CMD_RDID2_u8                 ((uint8_t)0xDB)
#define gd_ILI9488_CMD_RDID3_u8                 ((uint8_t)0xDC)


// Extended commands
#define gd_ILI9488_CMD_IFMODECTRL_u8            ((uint8_t)0xB0)
#define gd_ILI9488_CMD_DISPINVCTRL_u8           ((uint8_t)0xB4)
#define gd_ILI9488_CMD_DISPFUNCCTRL_u8          ((uint8_t)0xB6)
#define gd_ILI9488_CMD_ENTRYMODESET_u8          ((uint8_t)0xB7)
#define gd_ILI9488_CMD_POWERCTRL1_u8            ((uint8_t)0xC0)
#define gd_ILI9488_CMD_POWERCTRL2_u8            ((uint8_t)0xC1)
#define gd_ILI9488_CMD_POWERCTRL3_u8            ((uint8_t)0xC2)
#define gd_ILI9488_CMD_POWERCTRL4_u8            ((uint8_t)0xC3)
#define gd_ILI9488_CMD_POWERCTRL5_u8            ((uint8_t)0xC4)
#define gd_ILI9488_CMD_VCOMCTRL1_u8             ((uint8_t)0xC5)
#define gd_ILI9488_CMD_RDID4_u8                 ((uint8_t)0xD3)








#endif //__TFTSCREEN_H__
#ifndef LCD_H
#define LCD_H
#include <xc.h>
#include "i2c.h"
#define _XTAL_FREQ 16000000
#define e1 I2C_SendByteByADDR(portlcd|=0x04,0x4E)
#define e0 I2C_SendByteByADDR(portlcd&=~0x04,0x4E)
#define rs1 I2C_SendByteByADDR(portlcd|=0x01,0x4E)
#define rs0 I2C_SendByteByADDR(portlcd&=~0x01,0x4E)
#define setled I2C_SendByteByADDR(portlcd|=0x08,0x4E)
#define setwrite I2C_SendByteByADDR(portlcd&=~0x02,0x4E)
//--------------------------------------------------------------
void LCD_PORT_init();
void LCD_Init();
void LCD_String(char* st);
void LCD_SetPos(unsigned char x, unsigned char y);
void sendbyte(unsigned char c, unsigned char mode);
void LCD_Clear(void);
//--------------------------------------------------------------
#endif /* LCD_H */
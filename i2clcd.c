#include "i2clcd.h"
//--------------------------------------------------------------
unsigned char portlcd = 0;
//--------------------------------------------------------------
void sendhalfbyte(unsigned char c)
{
  c<<=4;
  e1;
  __delay_us(1);
  I2C_SendByteByADDR ((portlcd&0x0F)|c,0b01001110);
  e0;
  __delay_us(50);
}
//--------------------------------------------------------------
void sendbyte(unsigned char c, unsigned char mode)
{
  unsigned char hc=0;
  PORTB=c;
  if(mode==0) rs0;
  else rs1;
  hc=c>>4;
  sendhalfbyte(hc);sendhalfbyte(c);
}
//--------------------------------------------------------------
void LCD_Init()
{
  __delay_ms(50);
  PORTC &= ~0x70;
  PORTB &= ~0xF0;
  __delay_ms(100);
  sendhalfbyte(0x03);
  __delay_us(4500);
  sendhalfbyte(0x03);
  __delay_us(4500);
  sendhalfbyte(0x03);
  __delay_us(200);
  sendhalfbyte(0x02);
  __delay_ms(1);
  sendbyte(0x28, 0);//mode 4 bit, 2 lines (from our large display is 4 lines, font 5x8
  sendbyte(0x28, 0);//mode 4 bit, 2 lines (from our large display is 4 lines, font 5x8
  sendbyte(0x0C,0);//Display ON, Cursor OFF, blink OFF
  __delay_ms(1);
  sendbyte(0x01,0);// Clear Display
  __delay_ms(2);
  sendbyte(0x06,0);// direction left to right
  __delay_ms(1);
  sendbyte(0x02,0);//Cursor reset
  sendbyte(0X80,0);//SET POS LINE 0
  __delay_ms(2);
  setled;
  setwrite;
}
//--------------------------------------------------------------
void LCD_Clear(void)
{
  sendbyte(0x01, 0);
  __delay_us(1500);
}
//--------------------------------------------------------------
void LCD_SetPos(unsigned char x, unsigned char y)
{
  switch(y)
  {
    case 0:
      sendbyte((unsigned char)(x|0x80),0);
      break;
    case 1:
      sendbyte((unsigned char)((0x40+x)|0x80),0);
      break;
  }
}
//--------------------------------------------------------------
void LCD_String(char* st)
{
  unsigned char i=0;
  while(st[i]!=0)
  {
    sendbyte(st[i],1);
    i++;
  }
}
//--------------------------------------------------------------

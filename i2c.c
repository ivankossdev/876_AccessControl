#include "i2c.h"
void InitI2C(void)
{
    TRISC = 0x18; //RC3, RC4 input
    SSPADD =0x27; 
    SSPSTAT = 0x80;
    SSPCON = 0x38;
}
void I2C_Idle()
{
  while(READ_WRITE);
  ZERO=0;
  while(ZERO)
  {
    SSPCON2&0x1f;
  }
}

void I2C_IntWait(void)
{
  while(!SSPIF);
  SSPIF=0;
}

void I2C_StartCondition(void)
{
  I2C_Idle();
  SEN=1;
  I2C_IntWait();
}

void I2C_StopCondition(void)
{
  PEN = 1;
  I2C_IntWait();
}

I2C_Write_Byte(unsigned char Byte)
{
  SSPBUF = Byte;
  I2C_IntWait();
}

void I2C_SendByteByADDR(unsigned char c,unsigned char addr)
{
  I2C_StartCondition();
  I2C_Write_Byte(addr);
  I2C_Write_Byte(c);
  I2C_StopCondition();
}

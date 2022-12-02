#ifndef I2C_H
#define	I2C_H
#include <xc.h>
#define SDA RC4 // i2c data
#define SCK RC3 // i2c clock
#define SDA_DIR TRISC4 // Data pin direction
#define SCK_DIR TRISC3 // Clock pin direction

void set(void);
void InitI2C(void);
void I2C_Idle();
void I2C_SendByteByADDR(unsigned char c,unsigned char addr);

#endif	/* I2C_H */


#include <xc.h>
#include "setting.h"
#include "i2clcd.h"

char code[64];
unsigned char flag = 1;
unsigned char busy = 1;

void main(void) {
    InitI2C();
    LCD_Init();
    TRISB |= 0x03;
    PORTB |= 0xFC;
    unsigned int i = 0;
    LCD_String((char*) "Ready");
    while (1) {
        do {
            if (PORTBbits.RB0 == 0) {
                code[i] = '1';
                i++;
                __delay_us(800);
            } 
            else if (PORTBbits.RB1 == 0) {
                flag = 1;
                code[i] = '0';
                i++;
                __delay_us(800);
            }
            if (i > 16) {
                i = 0;
                flag = 2;
            }
        } while (flag == 1);
        if (flag == 2) {
            LCD_Clear();
            LCD_String((char*) code);
            flag = 0;
            __delay_ms(5000);
            
            LCD_Clear();
            LCD_String((char*) "OK");
        }
    }

}
//            LCD_SetPos(2, 1);
//            sendbyte('1', 1);
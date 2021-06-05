#ifndef __iic1602_H__
#define __iic1602_H__
/**********delay***********/
void delay_ms(unsigned int ms);
void delay_10us(unsigned int i);
/**********I2C init***********/
void I2cStart(void);
void I2cStop(void);
unsigned char I2cSendByte(unsigned char dat);
/**********i2c 1602**********/
void LCD_Init(void);
void write_cmd(unsigned char cmd);
void write_data(unsigned char DData);
void LCD_Write_Char(unsigned char X, unsigned char Y, unsigned char DData);
void LCD_Write_String(unsigned char X, unsigned char Y, unsigned char* Arry);

#endif

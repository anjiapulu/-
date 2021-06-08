#ifndef S1602_H
#define S1602_H


#define ADR_1602 0x4e    //器件地址  ADR:0x4e


void LCD_Clear(void);         //清屏函数
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s);  //字符串写入函数
void LCD_Init(void);                                                      //初始化函数
void LCD_Write_Char(unsigned char X, unsigned char Y, unsigned char DData);

#endif









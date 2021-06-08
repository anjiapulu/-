/*----------------------------------------
1.该模块为I2C 1602显示模块
2.模块依赖I2C通信模块，通过调用模块函数实现
3.I2C通信引脚为SDA:P2_2;
			   SCL:P2_0;
4.修改通信引脚请到I2C模块修改
-----------------------------------------*/
#include "s1602.h"
#include "i2c.h"
#include "delay.h"

unsigned char LCD_data = 0x08;

/*-----------------------------------------
			使能
-------------------------------------------*/
void Enable_LCD_write()
{
    LCD_data|=(1<<(3-1));//E=1;
    ISendByte(ADR_1602,LCD_data);  
  	DelayUs2x(2);
    LCD_data&=~(1<<(3-1));//E=0;
    ISendByte(ADR_1602,LCD_data);
}
/*------------------------------------------------
              写入命令函数
------------------------------------------------*/
 void LCD_Write_Com(unsigned char command) 
 { 
	DelayUs2x(16);
    LCD_data&=~(1<<(1-1));//RS=0;
    LCD_data&=~(1<<(2-1));//RW=0;
    //LCD_data&=~(1<<(4-1));
    ISendByte(ADR_1602,LCD_data);

    LCD_data&=0X0f; //清高四位
    LCD_data|=command & 0xf0; //写高四位
    ISendByte(ADR_1602,LCD_data);
    Enable_LCD_write();

    command=command<<4; //低四位移到高四位
    LCD_data&=0x0f; //清高四位
    LCD_data|=command&0xf0; //写低四位
    ISendByte(ADR_1602,LCD_data);
    Enable_LCD_write();
 }
/*------------------------------------------------
              写入数据函数
------------------------------------------------*/
 void LCD_Write_Data(unsigned char value) 
 { 
    DelayUs2x(16);;
    LCD_data|=(1<<(1-1));//RS=1;
    LCD_data&=~(1<<(2-1));//RW=0;
    ISendByte(ADR_1602,LCD_data);

    LCD_data&=0X0f; //清高四位
    LCD_data|=value&0xf0; //写高四位
    ISendByte(ADR_1602,LCD_data);
    Enable_LCD_write();         

    value=value<<4; //低四位移到高四位
    LCD_data&=0x0f; //清高四位
    LCD_data|=value&0xf0; //写低四位
    ISendByte(ADR_1602,LCD_data);
    Enable_LCD_write();
 }
/*------------------------------------------------
                清屏函数
------------------------------------------------*/
/* void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 DelayMs(2);
 }*/
/*------------------------------------------------
              写入字符串函数
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 { 
 if (y == 0) 
    {     
     LCD_Write_Com(0x80 + x);     //表示第一行
    }
 else 
    {      
    LCD_Write_Com(0xC0 + x);      //表示第二行
    }        
 while (*s) 
    {     
 LCD_Write_Data( *s);     
 s ++;     
    }
 }
 void LCD_Write_Char(unsigned char X, unsigned char Y, unsigned char DData)
{
	Y &= 0x1;
	X &= 0xF;
	if (Y)
		X |= 0x40;
	X |= 0x80;
	LCD_Write_Com(X);
	LCD_Write_Data(DData);
}
/*------------------------------------------------
              初始化函数
------------------------------------------------*/
void LCD_Init(void) 
 {
    LCD_Write_Com(0x02); //归位
    DelayUs2x(40);
    LCD_Write_Com(0x28); //四位数据总线(DB7-DB4),两行显示
    LCD_Write_Com(0x0c); //显示开
    LCD_Write_Com(0x01); //清屏
    DelayMs(10);
 }








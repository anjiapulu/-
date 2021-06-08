/*----------------------------------------
1.��ģ��ΪI2C 1602��ʾģ��
2.ģ������I2Cͨ��ģ�飬ͨ������ģ�麯��ʵ��
3.I2Cͨ������ΪSDA:P2_2;
			   SCL:P2_0;
4.�޸�ͨ�������뵽I2Cģ���޸�
-----------------------------------------*/
#include "s1602.h"
#include "i2c.h"
#include "delay.h"

unsigned char LCD_data = 0x08;

/*-----------------------------------------
			ʹ��
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
              д�������
------------------------------------------------*/
 void LCD_Write_Com(unsigned char command) 
 { 
	DelayUs2x(16);
    LCD_data&=~(1<<(1-1));//RS=0;
    LCD_data&=~(1<<(2-1));//RW=0;
    //LCD_data&=~(1<<(4-1));
    ISendByte(ADR_1602,LCD_data);

    LCD_data&=0X0f; //�����λ
    LCD_data|=command & 0xf0; //д����λ
    ISendByte(ADR_1602,LCD_data);
    Enable_LCD_write();

    command=command<<4; //����λ�Ƶ�����λ
    LCD_data&=0x0f; //�����λ
    LCD_data|=command&0xf0; //д����λ
    ISendByte(ADR_1602,LCD_data);
    Enable_LCD_write();
 }
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
 void LCD_Write_Data(unsigned char value) 
 { 
    DelayUs2x(16);;
    LCD_data|=(1<<(1-1));//RS=1;
    LCD_data&=~(1<<(2-1));//RW=0;
    ISendByte(ADR_1602,LCD_data);

    LCD_data&=0X0f; //�����λ
    LCD_data|=value&0xf0; //д����λ
    ISendByte(ADR_1602,LCD_data);
    Enable_LCD_write();         

    value=value<<4; //����λ�Ƶ�����λ
    LCD_data&=0x0f; //�����λ
    LCD_data|=value&0xf0; //д����λ
    ISendByte(ADR_1602,LCD_data);
    Enable_LCD_write();
 }
/*------------------------------------------------
                ��������
------------------------------------------------*/
/* void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 DelayMs(2);
 }*/
/*------------------------------------------------
              д���ַ�������
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 { 
 if (y == 0) 
    {     
     LCD_Write_Com(0x80 + x);     //��ʾ��һ��
    }
 else 
    {      
    LCD_Write_Com(0xC0 + x);      //��ʾ�ڶ���
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
              ��ʼ������
------------------------------------------------*/
void LCD_Init(void) 
 {
    LCD_Write_Com(0x02); //��λ
    DelayUs2x(40);
    LCD_Write_Com(0x28); //��λ��������(DB7-DB4),������ʾ
    LCD_Write_Com(0x0c); //��ʾ��
    LCD_Write_Com(0x01); //����
    DelayMs(10);
 }








#ifndef S1602_H
#define S1602_H


#define ADR_1602 0x4e    //������ַ  ADR:0x4e


void LCD_Clear(void);         //��������
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s);  //�ַ���д�뺯��
void LCD_Init(void);                                                      //��ʼ������
void LCD_Write_Char(unsigned char X, unsigned char Y, unsigned char DData);

#endif









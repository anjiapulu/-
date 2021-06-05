#ifndef _LCD_12864_H
#define _LCD_12864_H


#define LCD12864_DB P0

sbit LCD12864_RS = P2^2;
sbit LCD12864_RW = P2^3;
sbit LCD12864_E = P2^4;
sbit LCD12864_LED =P2^6;
sbit LCD12864_PSB = P2^5;//1 Ϊ���� 0Ϊ����
sbit LCD12864_REST = P2^7;//�͵�ƽ��Ч

void  Lcd12864_init();
void Lcd12864_writedat(unsigned char dat);
void Lcd12864_writecom(unsigned char com);

void  Lcd12864_writeCGRAM(unsigned char ad,unsigned char *dotdat);//1-4���Զ������16x16
void  Lcd12864_disstring(unsigned char x,unsigned char y,unsigned char *str);//8��,0-3��
void  Lcd12864_disCGRAM(unsigned char x,unsigned char y,unsigned int add);//1-4

void Lcd12864_writepictoDDRAM(unsigned char *pic);//��ʾͼƬ


void Lcd12864_drwdot(unsigned char x,unsigned y,unsigned char color);//����Ӧλ�û���

void drawCollumLine(unsigned char x0,unsigned char y0,unsigned char y1,unsigned char color);//������
void drawRowLine(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char color);//������

void draw_16x16(unsigned char x_s,unsigned char y_s,unsigned char c);//16*16���󷴰���ʾ

#endif
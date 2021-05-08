#include "reg51.h"
#include "delay.h"
#include "string.h"
/*****ÉùÃ÷******/
sbit SCL=P2^0;
sbit SDA=P2^1;
void write_data(unsigned char DData);
/*****¶¨Òå******/
void I2cStart(void)
{
	SDA = 1;
	delay_10us(1);
	SCL = 1;
	delay_10us(1);
	SDA = 0;
	delay_10us(1);
	SCL = 0;
	delay_10us(1);
}

void I2cStop(void)
{
	SDA = 0;
	delay_10us(1);
	SCL = 1;
	delay_10us(1);
	SDA = 1;
	delay_10us(1);
}

unsigned char I2cSendByte(unsigned char dat)
{
	unsigned char a = 0, b = 0;
	for (a = 0; a < 8; a++)
	{
		SDA = dat >> 7;
		dat = dat << 1;
		delay_10us(1);
		SCL = 1;
		delay_10us(1);
		SCL = 0;
		delay_10us(1);
	}
	SDA = 1;
	delay_10us(1);
	SCL = 1;
	while (SDA)
	{
		b++;
		if (b > 200)
		{
			SCL = 0;
			delay_10us(1);
			return 0;
		}
	}
	SCL = 0;
	delay_10us(1);
	return 1;
}



void write_cmd(unsigned char cmd)
{
	I2cStart();
	I2cSendByte(0x7c);
	I2cSendByte(0x80);
	I2cSendByte(cmd);
	I2cStop();
}

void lcd_init(void)
{
	write_cmd(0X38);
	write_cmd(0x0c);
	write_cmd(0x01);
	DelayMs(2);
}

void dispaly(unsigned char X, unsigned char Y, unsigned char DData)
{
	Y &= 0x1;
	X &= 0xF;
	if (Y)
		X |= 0x40;
	X |= 0x80;
	write_cmd(X);
	write_data(DData);
}

void write_data(unsigned char DData)
{
	I2cStart();
	I2cSendByte(0x7c);
	I2cSendByte(DData);
	I2cSendByte(0x40);
	I2cSendByte(DData);
	I2cStop();
}

void dispaly_character(unsigned char X, unsigned char Y, unsigned char* Arry)
{
	unsigned int i;
	unsigned int length1 = strlen(Arry);

	for (i = 0; i < length1; i++)
	{
		dispaly(X, Y, Arry[i]);
		X++;
		if (X > 16)
		{
			Y += 1;
			X = 0;
		}
	}
}


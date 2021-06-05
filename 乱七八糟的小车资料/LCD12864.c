#include <reg51.h>
#include <intrins.h>
#include "LCD12864.h"


void Lcd12864_delay(unsigned int tim)
{
	unsigned int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<tim;j++);
		
	}
}

void Lcd12864_ready()
{
	unsigned char sta;
		
	LCD12864_DB = 0xff;
	LCD12864_RS = 0;
	LCD12864_RW = 1;
	do
	{
		LCD12864_E = 1;
		_nop_();
		sta = LCD12864_DB;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		LCD12864_E = 0;
	}while(sta&0x80);
}

unsigned char Lcd12864_readdat()
{
	unsigned char readat;
	

	
	Lcd12864_ready();
	LCD12864_DB = 0xff;
	LCD12864_RS = 1;
	LCD12864_RW = 1;
	LCD12864_E = 1;
	_nop_();
	readat = LCD12864_DB;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD12864_E = 0;
	
	return readat;
}

void Lcd12864_writecom(unsigned char com)
{
	Lcd12864_ready();
	LCD12864_RS = 0;
	LCD12864_RW = 0;
	LCD12864_DB = com;
	LCD12864_E = 1;
	_nop_();
	LCD12864_E = 0;
}

void Lcd12864_writedat(unsigned char dat)
{
	Lcd12864_ready();
	LCD12864_RS = 1;
	LCD12864_RW = 0;
	LCD12864_DB = dat;
  LCD12864_E = 1;
	_nop_();
	LCD12864_E = 0;
}




void Lcd12864_fullclear()
{
		unsigned int i,j;
	
	Lcd12864_writecom(0x30);
	Lcd12864_writecom(0x34);
	Lcd12864_writecom(0x36);

	
	for(i=0;i<64;i++)
	{
		
	
		
		if(i<=31)
		{
			Lcd12864_writecom(0x80+i);//垂直地址
			Lcd12864_writecom(0x80);//水平地址

		}
		

		
		else 
			{
			Lcd12864_writecom(0x80+i-32);
			Lcd12864_writecom(0x88);
			}
		
		for(j=0;j<16;j++)
		{
		Lcd12864_writedat(0x00);
		}
		
	}

	Lcd12864_writecom(0x30);
}

void Lcd12864_init()
{
	LCD12864_PSB = 1;
	LCD12864_REST = 0;
	Lcd12864_delay(40);
	LCD12864_REST = 1;
	
	Lcd12864_writecom(0x30);
	Lcd12864_writecom(0x0c);
	Lcd12864_writecom(0x01);
	Lcd12864_writecom(0x06);
	
	Lcd12864_fullclear();
	
}

void Lcd12864_setadd(unsigned char x,unsigned char y)
{
	     if(y==0){Lcd12864_writecom(0x80+x);}
	else if(y==1){Lcd12864_writecom(0x90+x);}
	else if(y==2){Lcd12864_writecom(0x88+x);}
	else if(y==3){Lcd12864_writecom(0x98+x);}
}

void Lcd12864_disstring(unsigned char x,unsigned char y,unsigned char *str)
{
	Lcd12864_setadd(x,y);
	
	while(*str!='\0')
	{
		Lcd12864_writedat(*str++);
	}
}

void Lcd12864_disCGRAM(unsigned char x,unsigned char y,unsigned int add)//1-4
{
	Lcd12864_setadd(x,y);
	Lcd12864_writedat(0x00);//必须要先写0x00后才能显示CGRAM内数据
	Lcd12864_writedat(((add-1)<<1));
}

void Lcd12864_writeCGRAM(unsigned char ad,unsigned char *dat)//ad = 1-4
{
	unsigned char i;
	Lcd12864_writecom(0x30);
	Lcd12864_writecom(0x34);//打开扩展指令
	Lcd12864_writecom(0x02);//允许写设定CGRAM地址
  Lcd12864_writecom(0x30);//回到基本指令
	Lcd12864_writecom(0x40+((ad-1)<<4));//CGRAM地址

	for(i=0;i<32;i++)
	{
		
		Lcd12864_writedat(*dat++);

	}
	
}




void Lcd12864_writepictoDDRAM(unsigned char *pic)

{
	unsigned int i,j;
	Lcd12864_writecom(0x30);
	Lcd12864_writecom(0x34);
	Lcd12864_writecom(0x36);

	
	for(i=0;i<64;i++)
	{
		
	
		
		if(i<=31)
		{
			Lcd12864_writecom(0x80+i);//垂直地址
			Lcd12864_writecom(0x80);//水平地址

		}
		

		
		else 
			{
			Lcd12864_writecom(0x80+i-32);
			Lcd12864_writecom(0x88);
			}
		
		for(j=0;j<16;j++)
		{
		Lcd12864_writedat(*pic++);
		}
		
	}

	Lcd12864_writecom(0x30);
}



void Lcd12864_drwdot(unsigned char x,unsigned y,unsigned char color)
{
	
	unsigned char xadd,yadd,xadd_bit;
	unsigned char read_h ;
	unsigned char read_l ;
	
  Lcd12864_writecom(0x34);
	Lcd12864_writecom(0x36);
	
	xadd = x>>4;
	xadd_bit = x & 0x0f;
	
	if(y<32)
	{
		yadd = y;
	}
	
	else
	{
		yadd = y-32;
		xadd += 8;
   }
	
	Lcd12864_writecom(0x80+yadd);
	Lcd12864_writecom(0x80+xadd);
	Lcd12864_readdat();//读一次空
	read_h = Lcd12864_readdat();//DDRAM高字节数据
  read_l = Lcd12864_readdat();//DDRAM低字节数据
	
	Lcd12864_writecom(0x80+yadd);
	Lcd12864_writecom(0x80+xadd);
	
	if(xadd_bit <=7)
	{
		switch (color)
		{
			case 0:read_h &=(~(0x01<<(7-xadd_bit)));break;
			case 1:read_h |= (0x01<<(7-xadd_bit));break;
			case 2:read_h ^= (0x01<<(7-xadd_bit));break;
			default : break;
		}
		
		Lcd12864_writedat(read_h);
		Lcd12864_writedat(read_l);
	}
	
	else
	{
				switch (color)
		{
			case 0:read_l &=(~(0x01<<(15-xadd_bit)));break;//不显示点，将原来位置涂白
			case 1:read_l |= (0x01<<(15-xadd_bit));break;//显示点，将原来位置涂黑
			case 2:read_l ^= (0x01<<(15-xadd_bit));break;//反转，与原来显示相反
			default : break;
		}
		
		Lcd12864_writedat(read_h);
		Lcd12864_writedat(read_l);
	}
		
	
	Lcd12864_writecom(0x30);

	
}


void drawRowLine(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char color)
{
	unsigned char temp;
	if(x0>x1)
	{
	   temp = x1;
	   x1 = x0;
	   x0 = temp;
	}
	do
	{
	   Lcd12864_drwdot(x0, y0, color);
	   x0++;
	}
      while(x1>=x0);
}



void drawCollumLine(unsigned char x0,unsigned char y0,unsigned char y1,unsigned char color)
{
unsigned char temp;
if(y0>y1)
{
 temp=y0;
 y0=y1;
 y1=temp;
}
while (y0<=y1)
{
Lcd12864_drwdot(x0,y0,color);
y0++;
}

}


void draw_16x16(unsigned char x_s,unsigned char y_s,unsigned char c)
	
{
	unsigned char i;
	
	switch(y_s)
	{
		case 0: 
			switch(x_s)
			{
				case 0: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 1: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 2: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 3: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 4: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 5: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 6: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 7: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				default : break;
			}break;
			
		case 1:
			switch(x_s)
			{
				case 0: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 1: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 2: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 3: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 4: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 5: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 6: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 7: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				default : break;
			}break;
			
			case 2:
			switch(x_s)
			{
				case 0: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 1: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 2: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 3: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 4: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 5: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 6: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 7: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				default : break;
			}break;
			
			case 3:
			switch(x_s)
			{
				case 0: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 1: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 2: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 3: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 4: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 5: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 6: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				case 7: for(i=y_s*16;i<(y_s+1)*16;i++)drawRowLine(x_s*16,i,(x_s+1)*16-1,c);break;
				default : break;
			}break;
			
		default : break;
	}
}















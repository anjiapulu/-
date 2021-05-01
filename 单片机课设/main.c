#include "reg51.h"
#include "string.h"
#include "delay.h"
#include "iic1602.h"
#include "MatrixKey.h"
#include "at24c02.h"
unsigned char code redistance[] = " L___ F___ R___ ";
unsigned char code safe[] =     "    safe now    ";
unsigned char code danger[] =   "   danger now   ";
unsigned char code setting[] =  "   input dist   ";
unsigned char code number[]= "0123456789";
char left[]="___",front[]="___",right[]="___";
char KeyNum=10;
int main()
{ int i,j,k,l;
	lcd_init(); /*仿真iic1602显示初始化*/
	dispaly_character(0,0, setting);
	dispaly_character(0,1, redistance);
	if(j==1)
	{
		IRcvStr(0xA0, 2,left  ,3);
		IRcvStr(0xA0, 4,front ,3);
		IRcvStr(0xA0, 6,front ,3);
	}
  while (1)
  {
	KeyNum = MatrixKey();
		if(KeyNum>10) 
	{ 
	 /*方位选择*/
		if(KeyNum==13)
		{	
			char left[]="___";
			dispaly_character(2,1, left);
			for(i=0;i<3;)
			{
        KeyNum = MatrixKey();
			  if(KeyNum<10)
			  {
			  left[i]=number[KeyNum];
				dispaly_character(2,1, left);
				i++;
			  }
			}
		}
		
		if(KeyNum==14)
		{
      char front[]="___";
			dispaly_character(7,1, front);
			for(i=0;i<3;)
			{
        KeyNum = MatrixKey();
			  if(KeyNum<10)
			  {
			  front[i]=number[KeyNum];
				dispaly_character(7,1, front);
				i++;
			  }
			}
		}
		
		if(KeyNum==15)
		{
		  char	right[]="___";
			dispaly_character(12,1, right);
			for(i=0;i<3;)
			{
        KeyNum = MatrixKey();
			  if(KeyNum<10)
			  {
			  right[i]=number[KeyNum];
				dispaly_character(12,1, right);
				i++;
			  }
			}
		}
	
		
		
		
	}
	
	
  }
	return 0;
}

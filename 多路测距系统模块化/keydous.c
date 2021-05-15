#include <reg52.h>
#include "1602.h"
#include "delay.h"
#include "string.h"
#include "MatrixKey.h"
unsigned char code studentid[]="0123456789";
extern int leftnumber, backnumber, rightnumber,i,j;
int KeyNum,k=0;
char  keydous()
{  
	
/*------------------------------------------------
		·äÃùÆ÷¾¯½äÖµÊäÈë
------------------------------------------------*/
	while(k<3)
	{
			if (k == 0)
			{
					LCD_Write_String(0, 1, " L___ B___ R___ ");
			}
			LCD_Write_String(0, 0, "   input dist   ");
			KeyNum = MatrixKey();
			if (KeyNum == 13)
			{
				k++;
				if (k == 1)
				{
					for (i = 2; i < 5;)
					{
						KeyNum = MatrixKey();
						if(i==2)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            leftnumber+=(KeyNum*100);
						}
						}
            if(i==3)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            leftnumber+=(KeyNum*10);
						}
						}
						if(i==4)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            leftnumber+=(KeyNum);
						}
						}
						if (KeyNum < 10)
						{
							
							LCD_Write_Char(i, 1, studentid[KeyNum]);
							i++;
						}
				DelayMs(50);
					}
				}
				if (k == 2)
				{
					for (i = 7; i < 10; )
					{
						KeyNum = MatrixKey();
						if(i==7)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            backnumber+=(KeyNum*100);
						}
						}
            if(i==8)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            backnumber+=(KeyNum*10);
						}
						}
						if(i==9)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            backnumber+=(KeyNum);
						}
						}
						if (KeyNum < 10)
						{
							LCD_Write_Char(i, 1, studentid[KeyNum]);
							i++;
						}
						DelayMs(50);
					}
				}
				if (k == 3)
				{
          k=4;
					for (i = 12; i < 15; )
					{
						KeyNum = MatrixKey();
	          if(i==12)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            rightnumber+=(KeyNum*100);
						}
						}
            if(i==13)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            rightnumber+=(KeyNum*10);
						}
						}
						if(i==14)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            rightnumber+=(KeyNum);
						}
						}
						if (KeyNum < 10)
						{
							LCD_Write_Char(i, 1, studentid[KeyNum]);
							i++;
						}
					 	DelayMs(50);
					}
 
				  LCD_Write_String(0, 0, "                ");
				 }
				
			 }
			
		 }
	return leftnumber, backnumber, rightnumber;
  }
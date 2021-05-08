 #include <reg52.h>
 #include <stdio.h>
 #include <math.h>
 #include "delay.h"
 sbit TRIGL = P1^0 ;
 sbit ECHOL = P1^1 ;
 sbit TRIGF = P1^2 ;
 sbit ECHOF = P1^3 ;
 sbit TRIGR = P1^4 ;
 sbit ECHOR = P1^5 ;
 unsigned char DisTempData[16];
 /*------------------------------------------------
                    ???0???
------------------------------------------------*/
void TIM0init()
{

  TMOD|= 0x01;//???0????1
  TH0=0x00;    
  TL0=0x00; 
  ET0=1;
  EA=1;
}


/*------------------------------------------------
                 ????????
------------------------------------------------*/
void Timer0_isr() interrupt 1
{
 ECHOL=0;
	ECHOF=0;
}

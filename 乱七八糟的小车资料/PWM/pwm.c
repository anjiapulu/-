#include"reg52.h"
typedef unsigned int u16;
typedef unsigned char u8;
void Timer0Init();
u16 timer1;
//u16 count=10;
sbit ENA=P1^5;
sbit IN1=P1^4;
sbit IN2=P1^3;
sbit IN3=P1^2;
sbit IN4=P1^1;
sbit ENB=P1^0;

void pwm1(u16 count)
{
 if(count>=timer1)
	 IN1=1;
   else
   IN1=0;
}
void pwm2(u16 count)
{
 if(count>=timer1)IN2=1;
   else
   IN2=0;
}
void pwm3(u16 count)
{
 if(count>=timer1)IN3=1;
   else
   IN3=0;
}
void pwm4(u16 count)
{
 if(count>=timer1)IN4=1;
   else
   IN4=0;
}


void Forward()
{
 pwm1(50);
 IN2=0;
 ENA=1;
 IN3=0;
 pwm4(50);
 ENB=1;
}
void back()
{
 IN1=0;
 pwm2(50);
 ENA=1;
 pwm3(50);
 IN4=0;
 ENB=1;
}
void turnright()
{
 IN1=0;
 IN2=0;
 ENA=0;
 IN3=0;
 pwm4(50);
 ENB=1;
}
void turnleft()
{
 pwm1(50);
 IN2=0;
 ENA=1;
 IN3=0;
 IN4=0;
 ENB=0;
}
void stop()
{
 IN1=0;
 IN2=0;
 IN3=0;
 IN4=0;
}

void main()
{   
       
   Timer0Init();
   
   while(1)
   {  
     		 pwm1(30);
     } 
}

void Timer0Init()
{
 TMOD|=0X01;
 TH0=0XFF;
 TL0=0X38;
 ET0=1;
 EA=1;
 TR0=1;

}
void Time0() interrupt 1
{
 TH0=0XFF;
 TL0=0X38;
 timer1++;
 if(timer1>100)
 {
  timer1=0;
 }
}
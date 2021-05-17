#include"reg52.h"
#include"QX_A11.h"
#include"delay.h"
typedef unsigned int u16;
void Timer0Init();
u16 timer1;
float S1,S2,S3;
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
 pwm1(5);
 IN2=0;
 Left_moto_pwm=1;
 IN3=0;
 pwm4(5);
 Right_moto_pwm=1;
}
void back()
{
 IN1=0;
 pwm2(7);
 Left_moto_pwm=1;
 pwm3(7);
 IN4=0;
 Right_moto_pwm=1;
}
void turnright()
{
 IN1=0;
 IN2=0;
 Left_moto_pwm=0;
 IN3=0;
 pwm4(5);
 Right_moto_pwm=1;
}
void turnleft()
{
 pwm1(5);
 IN2=0;
 Left_moto_pwm=1;
 IN3=0;
 IN4=0;
 Right_moto_pwm=0;
}
void stop()
{
 IN1=0;
 IN2=0;
 IN3=0;
 IN4=0;
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
void pwm()
{     /*S1ÓÒ±ß  S2×ó±ß  S3ºó±ß*/  
      if((S1<5.5)||(S2<5.5)) 
		  {
		  Forward();		   
      DelayMs(500);
		  }
			if(S1>S2)  
			{
			turnleft();
			DelayMs(500);
			if(S3>8)
			{
			back();
			}
			}
			else
			{
			turnright();
			DelayMs(500);
			if(S3>8)
			{
			back();
			DelayMs(500);
			}
			}
      while(S1<6&&S2<6&&S3<5)
			{
			stop();
			}
			
}
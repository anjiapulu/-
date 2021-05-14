#include <reg52.h>
#include <stdio.h>
#include <math.h>
#include "1602.h"
#include "delay.h"
#include "string.h"
//#include "MatrixKey.h"
#include <QX_A11.h>//QX-A51智能小车配置文件
typedef unsigned int u16;
typedef unsigned int u8;
u8 timer1;


unsigned char DisTempData[7];
//unsigned char code studentid[]="0123456789";
float S, arr[5], temp;
float leftnumber, backnumber, rightnumber;
int i, k=0, j, KeyNum = 10;
/*------------------------------------------------
				   子函数
------------------------------------------------*/
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
void Timer0Init()
{
 TMOD|=0X01;
 TH0=(65536-100)/256;
 TL0=(65536-100)%256;
 ET0=1;
 EA=1;
 TR0=1;
}
void Time0() interrupt 1
{
 TH0=(65536-100)/256;
 TL0=(65536-100)%256;
 timer1++;
 if(timer1>100)
 {
  timer1=0;
 }
}


void TIM1init(void)
{

	TMOD |= 0x10;
	TH1 = 0x00;
	TL1 = 0x00;
	ET1 = 1;
}
void Forward()
{
 pwm1(3);
 IN2=0;
 Left_moto_pwm=1;
 IN3=0;
 pwm4(3);
 Right_moto_pwm=1;
}
void back()
{
 IN1=0;
 pwm2(5);
 Left_moto_pwm=1;
 pwm3(5);
 IN4=0;
 Right_moto_pwm=1;
}
void turnright()
{
 IN1=0;
 IN2=0;
 Left_moto_pwm=0;
 IN3=0;
 pwm4(3);
 Right_moto_pwm=1;
}
void turnleft()
{
 pwm1(3);
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

/*------------------------------------------------
				主函数
------------------------------------------------*/
main()
{
	TIM1init();
	LCD_Init();
	Timer0Init();
	while (1)
	{
/*------------------------------------------------
		蜂鸣器警戒值输入
		while (k <= 3)
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
	
		
//	
------------------------------------------------*/
		/*------------------------------------------------
						右方
		------------------------------------------------*/
		if (1)
		{
			/*one*/
			TRIGR = 1;
			DelayUs2x(10);
			TRIGR = 0;
			while (!ECHOR);
			TR1 = 1;
			while (ECHOR);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;
			arr[0] = S;
			TH1 = 0;
			TL1 = 0;
			/*two*/
			TRIGR = 1;
			DelayUs2x(10);
			TRIGR = 0;
			while (!ECHOR);
			TR1 = 1;
			while (ECHOR);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;
			arr[1] = S;
			TH1 = 0;
			TL1 = 0;
			/*third*/
			TRIGR = 1;
			DelayUs2x(10);
			TRIGR = 0;
			while (!ECHOR);
			TR1 = 1;
			while (ECHOR);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;
			arr[2] = S;
			TH1 = 0;
			TL1 = 0;
			/*four*/
			TRIGR = 1;
			DelayUs2x(10);
			TRIGR = 0;
			while (!ECHOR);
			TR1 = 1;
			while (ECHOR);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;
			arr[3] = S;
			TH1 = 0;
			TL1 = 0;
			/*five*/
			TRIGR = 1;
			DelayUs2x(10);
			TRIGR = 0;
			while (!ECHOR);
			TR1 = 1;
			while (ECHOR);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;
			arr[4] = S;
			TH1 = 0;
			TL1 = 0;
			/*try*/
			for (i = 0; i < 5 - 1; i++)
				for (j = 0; j < 5 - 1 - i; j++)
					if (arr[j] > arr[j + 1])
					{
						temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
					}
			/*try*/
			S = ((arr[1] + arr[2] + arr[3] ) / 3);
//			temp=rightnumber;
//			if (S < temp)
//			{
//				                                          
//			SPK = 0;//防止一直给喇叭通电造成损坏
//			DelayMs(250);
//				
//			}
			
//				SPK = 1;
			rightnumber=S;
      if(rightnumber<5.5||rightnumber>1000)
			{
      turnright();
			DelayMs(50);
			Forward();
			DelayMs(50);
			turnleft();
			back();
			}
			sprintf(DisTempData, "R=%6.2f",S);
			LCD_Write_String(0, 1, DisTempData);
			
		}
		/*------------------------------------------------
					左方
		------------------------------------------------*/
		if (1)
		{
			/*one*/
			TRIGL = 1;
			DelayUs2x(10);
			TRIGL = 0;
			while (!ECHOL);
			TR1 = 1;
			while (ECHOL);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;       //     58    ,  Y =(X *344)/2
			arr[0] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
			TH1 = 0;
			TL1 = 0;
			/*two*/
			TRIGL = 1;
			DelayUs2x(10);
			TRIGL = 0;
			while (!ECHOL);
			TR1 = 1;
			while (ECHOL);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;       //     58    ,  Y =(X *344)/2
			arr[1] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
			TH1 = 0;
			TL1 = 0;
			/*third*/
			TRIGL = 1;
			DelayUs2x(10);
			TRIGL = 0;
			while (!ECHOL);
			TR1 = 1;
			while (ECHOL);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;
			arr[2] = S;
			TH1 = 0;
			TL1 = 0;
			/*four*/
			TRIGL = 1;
			DelayUs2x(10);
			TRIGL = 0;
			while (!ECHOL);
			TR1 = 1;
			while (ECHOL);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;
			arr[3] = S;
			TH1 = 0;
			TL1 = 0;
			/*five*/
			TRIGL = 1;
			DelayUs2x(10);
			TRIGL = 0;
			while (!ECHOL);
			TR1 = 1;
			while (ECHOL);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;
			arr[4] = S;
			TH1 = 0;
			TL1 = 0;

			/*try*/
			for (i = 0; i < 5 - 1; i++)
				for (j = 0; j < 5 - 1 - i; j++)
					if (arr[j] > arr[j + 1])
					{
						temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
					}
			/*try*/
			S = ((arr[1] + arr[2] + arr[3] ) / 3);
			leftnumber=S;
//			if (S < temp)
//			{
//				
//			SPK = 0;//防止一直给喇叭通电造成损坏
//			DelayMs(250);
//				
//			}
//		  SPK = 1;
      if(leftnumber<5.5||leftnumber>1000)
			{
			turnleft();
			Forward();
			turnright();
			back();
			}
			sprintf(DisTempData,"L=%6.2f", S);
			LCD_Write_String(8, 1, DisTempData);

		}
		/*------------------------------------------------
					  后方
		------------------------------------------------*/
		if (1)
			{
			TRIGB = 1;
			DelayUs2x(10);
			TRIGB = 0;
			while (!ECHOB);
			TR1 = 1;
			while (ECHOB);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;       //     58    ,  Y =(X *344)/2
			arr[0] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
			TH1 = 0;
			TL1 = 0;
			/*two*/
			TRIGB = 1;
			DelayUs2x(10);
			TRIGB = 0;
			while (!ECHOB);
			TR1 = 1;
			while (ECHOB);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;       //     58    ,  Y =(X *344)/2
			arr[1] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
			TH1 = 0;
			TL1 = 0;
			/*third*/
			TRIGB = 1;
			DelayUs2x(10);
			TRIGB = 0;
			while (!ECHOB);
			TR1 = 1;
			while (ECHOB);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;       //     58    ,  Y =(X *344)/2
			arr[2] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
			TH1 = 0;
			TL1 = 0;
			/*four*/
			TRIGB = 1;
			DelayUs2x(10);
			TRIGB = 0;
			while (!ECHOB);
			TR1 = 1;
			while (ECHOB);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;       //     58    ,  Y =(X *344)/2
			arr[3] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
			TH1 = 0;
			TL1 = 0;
			/*five*/
			TRIGB = 1;
			DelayUs2x(10);
			TRIGB = 0;
			while (!ECHOB);
			TR1 = 1;
			while (ECHOB);
			TR1 = 0;
			S = TH1 * 256 + TL1;
			S = S / 58;       //     58    ,  Y =(X *344)/2
			arr[4] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
			TH1 = 0;
			TL1 = 0;
			/*try*/
			for (i = 0; i < 5 - 1; i++)
				for (j = 0; j < 5 - 1 - i; j++)
					if (arr[j] > arr[j + 1])
					{
						temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
					}
			/*try*/
			S = ((arr[1] + arr[2] + arr[3] ) / 3);
			backnumber=S;
//			if (S < temp)
//			{
//				
//			SPK = 0;//防止一直给喇叭通电造成损坏
//			DelayMs(250);
//				
//			}
//		  SPK = 1;

     if(rightnumber>6&&leftnumber>6&&(backnumber>4&&backnumber<100))
		 {
		 back();
		 }

     while(rightnumber<6&&leftnumber<6&&backnumber<4)
     {
		 stop();
		 }
		 if(backnumber>1000)
		 {
		 Forward();
		 }
		sprintf(DisTempData, "B=%6.2f", S);
		LCD_Write_String(4, 0, DisTempData);
		}
	}
	
}
  


/*------------------------------------------------
				 中断
------------------------------------------------*/
void Timer0_isr(void) interrupt 2
{
	ECHOL = 0;
	ECHOB = 0;
	ECHOR = 0;
}

 #include <reg52.h>
 #include <stdio.h>
 #include <math.h>
 #include "1602.h"
 #include "delay.h"

 sbit TRIGL = P1^0 ;
 sbit ECHOL = P1^1 ;
 sbit TRIGF = P1^2 ;
 sbit ECHOF = P1^3 ;
 sbit TRIGR = P1^4 ;
 sbit ECHOR = P1^5 ;
 unsigned char DisTempData[16];

/*------------------------------------------------
                    定时器0初始化
------------------------------------------------*/
void TIM0init(void)
{

  TMOD|= 0x01;//定时器0工作方式1
  TH0=0x00;    
  TL0=0x00; 
  ET0=1;
  EA=1;
}
/*------------------------------------------------
                    主函数
------------------------------------------------*/
main()
{
  float S;       //距离变量
  TIM0init();    //初始化定时器0
  LCD_Init();    //初始化LCD
  while(1)
  {
   /*left*/
   TRIGL=1;       //触发信号是高电平脉冲，宽度大于10us
   DelayUs2x(10);
   TRIGL=0;
   while(!ECHOL); //等待高电平
   TR0=1;
   while(ECHOL);  //等待低电平
   TR0=0;
   S=TH0*256+TL0;//取出定时器值高8位和低8位合并
   S=S/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
			     // X秒=（ 2*Y米）/344 -> X秒=0.0058*Y米 -> 厘米=微秒/58 
   TH0=0;
   TL0=0;        //清除定时器0寄存器中的值
   sprintf(DisTempData,"L=%6.2f CM     ",S);//打印输出结果
   LCD_Write_String(0,0,DisTempData);       //在液晶屏上显示
   DelayMs(250);                            //延时决定采样速度
   /*front*/
	 TRIGF=1;       //触发信号是高电平脉冲，宽度大于10us
   DelayUs2x(10);
   TRIGF=0;
   while(!ECHOF); //等待高电平
   TR0=1;
   while(ECHOF);  //等待低电平
   TR0=0;
   S=TH0*256+TL0;//取出定时器值高8位和低8位合并
   S=S/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
			     // X秒=（ 2*Y米）/344 -> X秒=0.0058*Y米 -> 厘米=微秒/58 
   TH0=0;
   TL0=0;        //清除定时器0寄存器中的值
   sprintf(DisTempData,"F=%6.2f CM     ",S);//打印输出结果
   LCD_Write_String(0,1,DisTempData);       //在液晶屏上显示
   DelayMs(2500);   
	 /*RIGHT*/
	 TRIGR=1;       //触发信号是高电平脉冲，宽度大于10us
   DelayUs2x(10);
   TRIGR=0;
   while(!ECHOR); //等待高电平
   TR0=1;
   while(ECHOR);  //等待低电平
   TR0=0;
   S=TH0*256+TL0;//取出定时器值高8位和低8位合并
   S=S/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
			     // X秒=（ 2*Y米）/344 -> X秒=0.0058*Y米 -> 厘米=微秒/58 
   TH0=0;
   TL0=0;        //清除定时器0寄存器中的值
   sprintf(DisTempData,"R=%6.2f CM     ",S);//打印输出结果
   LCD_Write_String(0,1,DisTempData);       //在液晶屏上显示
   DelayMs(2500);   
  }
 }

/*------------------------------------------------
                 定时器中断子程序
------------------------------------------------*/
void Timer0_isr(void) interrupt 1
{
 ECHOL=0;
	ECHOF=0;
	 ECHOR=0;
}

/*********************************************************************************
* 【编写时间】： 2020年12月12日
* 【作    者】： 清翔电子:03
* 【版    本】： 1.0
* 【网    站】： http://www.QXMBOT.com/ 
* 【淘宝店铺】： http://qxmcu.taobao.com/ (直销店)
* 【实验平台】： QX-A11亚克力智能小车  STC89C52
* 【外部晶振】： 11.0592mhz	
* 【主控芯片】： STC89C52
* 【编译环境】： Keil μVisio4
*	版权所有，盗版必究。
*	Copyright(C) QXMBOT
*	All rights reserved
***********************************************************************************
* 【接线说明】：请参考资料内图文说明书
程序免费开源，不提供代码分析
注意事项需要用户参阅“*套餐组装调试指南”	
程序只做参考，根据实际运行效果可能还需要用户自行调试	   			            			    
**********************************************************************************/

/*开发板P32端口不能接杜邦线，否则无法遥控*/

#include <reg52.h> //51头文件
#include <QX_A11.h>//QX-A51智能小车配置文件
#include <stdio.h>
#include <math.h>
#include "1602.h"
#include "delay.h"
#include "distance.h"
#include "MatrixKey.h"
/*====================================
 自定义类型名
====================================*/
typedef unsigned char INT8U;
typedef unsigned char uchar;
typedef unsigned int INT16U;
typedef unsigned int uint;
unsigned char DisTempData[7],nice[1];
float S, arr[5];
int leftnumber=0, backnumber=0, rightnumber=0;
int i, k=0, j=10;
/*====================================
函数：void Delay_Ms(INT16U ms)
参数：ms，毫秒延时形参
描述：12T 51单片机自适应主时钟毫秒级延时函数
====================================*/
void Delay_Ms(unsigned int ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 96000; 
		  while(--i);   //96T per loop
     }while(--ms);
}
/*====================================
 硬件接口位声明
====================================*/
sbit IR  = P3^2;     //定义红外脉冲数据接口	外部中断O输入口
sbit TRIGL = P2 ^ 0;
sbit ECHOL = P2 ^ 1;
sbit TRIGB = P3 ^ 4;
sbit ECHOB = P3 ^ 5;
sbit TRIGR = P3 ^ 6;
sbit ECHOR = P3 ^ 7;
sbit SPK = P2 ^ 2;
uchar IRtime; 		//检测红外高电平持续时间（脉宽）
uchar IRcord[4];    //此数组用于储存分离出来的4个字节的数据（用户码2个字节+键值码2个字节）
uchar IRdata[33];   //此数组用于储存红外的33位数据（第一位为引导码用户码16+键值码16）
bit IRpro_ok, IRok;  //第一个用于红外接收4个字节完毕。IRok用为检测脉宽完毕

void init()	   //初始化定时器0 和外部中断0
{
	TMOD |= 0x02; //定时器0工作方式2，8位自动重装
	TH0 = 0x00;  //高8位装入0那么定时器溢出一次的时间是256个机器周期
	TL0 = 0x00;
	EA = 1;      //总中断
	ET0 = 1;	   //定时器0中断
	TR0 = 1;     //启动定时器0
	IT0 = 1;	   //设置外部中断0为跳沿触发方式，来一个下降沿触发一次
	EX0 = 1;	   //启动外部中断0
}

void time0() interrupt 1   //定义定时器0
{
	IRtime++; 			   //检测脉宽，1次为278us
}

void int0() interrupt 0	  		//定义外部中断0
{
	static uchar i;	 			//	声明静态变量（在跳出函数后在回来执行的时候不会丢失数值）i用于把33次高电平的持续时间存入IRdata
	static bit startflag;		//开始储存脉宽标志位
	if(startflag)	 			//开始接收脉宽检测
	{
		if( (IRtime < 53) && (IRtime >= 32) ) /*判断是否是引导码，底电平9000us+高4500us	
		这个自己可以算我以11.0592来算了NEC协议的引导码低8000-10000+高4000-5000 
		如果已经接收了引导码那么i不会被置0就会开始依次存入脉宽*/
			i = 0;				 //如果是引导码那么执行i=0把他存到IRdata的第一个位
		IRdata[i] = IRtime;  		 //以T0的溢出次数来计算脉宽，把这个时间存到数组里面到后面判断
		IRtime = 0;				 //计数清零，下一个下降沿的时候在存入脉宽
		i++; 					 //计数脉宽存入的次数
		if(i == 33) 				 //如果存入34次 数组的下标是从0开始i等于33表示执行了34次
		{
		 	IRok = 1;				 //那么表示脉宽检测完毕
			i = 0; 				 //把脉宽计数清零准备下次存入
		}
	}
	else		  
	{
		IRtime = 0; 				 //引导码开始进入把脉宽计数清零开始计数
		startflag = 1;			 //开始处理标志位置1
	}
}

void IRcordpro()   				 //提取它的33次脉宽进行数据解码
{
	uchar i, j, k, cord, value;	/*i用于处理4个字节，j用于处理一个字节中每一位，k用于33次脉宽中的哪一位
	cord用于取出脉宽的时间判断是否符合1的脉宽时间*/
	k = 1; 						//从第一位脉宽开始取，丢弃引导码脉宽
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 8; j++)
		{
			cord = IRdata[k];	    //把脉宽存入cord
			if(cord > 5)	 		//如果脉宽大于我11.0592的t0溢出率为约278us*5=1390那么判断为1
			value = value | 0x80;	/*接收的时候是先接收最低位，
			把最低位先放到value的最高位在和0x08按位或一下
			这样不会改变valua的其他位的数值只会让他最高位为1*/
			if(j < 7)
			{
				value = value >> 1;	//value位左移依次接收8位数据。
			}
			k++;				//每执行一次脉宽位加1
		}
		IRcord[i] = value;	   //每处理完一个字节把它放入IRcord数组中。
		value = 0; 			   //清零value方便下次在存入数据
	}
	IRpro_ok = 1;				   //接收完4个字节后IRpro ok置1表示红外解码完成	
}
/*PWM控制使能 小车前进*/
void forward()
{
	left_motor_go; //左电机前进
	right_motor_go; //右电机前进
}

	
/*PWM控制使能 小车后退*/
void backward()
{
	left_motor_back; //左电机后退
	right_motor_back; //右电机后退	
}


/*PWM控制使能 小车左转*/
void left_run()
{
	left_motor_stops; //左电机停止
	right_motor_go; //右电机前进	
}


/*PWM控制使能 小车右转*/
void right_run()
{
	right_motor_stops;//右电机停止
	left_motor_go;    //左电机前进
}


/*小车停止*/
void stop()
{
	right_motor_stops;//右电机停止
	left_motor_stops; //左电机停止	
}

void main()
{
	init();	//执行初始化定时器0和外部中断0
	TIM1init();    //??????0
	LCD_Init();    //???LCD
	Left_moto_pwm = Right_moto_pwm = 1;//使能左右电机
	while(1)	//大循环
	{
		if(IRok)    //判断脉宽是否检测完毕                    
		{   
			IRcordpro();//根据脉宽解码出4个字节的数据
			IRok = 0;	//重新等待脉宽检测
			if(IRpro_ok) //判断是否解码完毕  
			{
		        switch(IRcord[2])
		   		{
				     case 0x18:  stop(); Delay_Ms(200); forward(); 			 //前进
				             break;
				     case 0x52:  stop(); Delay_Ms(200); backward();  			 //后退	 
				             break;
				     case 0x08:  stop(); Delay_Ms(200); left_run(); 			 //左转
				             break;
					 case 0x5A:  stop(); Delay_Ms(200); right_run(); 			 //右转
				             break;
					 case 0x1C:  stop();			     //停止
				             break;
					 default:break;
		   		}
				IRpro_ok = 0;
			}
			if(1)
			{
	while (1)
	{

		/*蜂鸣器警戒值输入*/
		while (k <= 3)
		{
			if (k == 0)
			{
					LCD_Write_String(0, 1, " L___ B___ R___ ");
			}
			LCD_Write_String(0, 0, "   input dist   ");
			j = MatrixKey();
			if (j == 13)
			{
				k++;
				if (k == 1)
				{
					for (i = 2; i < 5;)
					{
						j = MatrixKey();
						if(i==2)
						{
						if(j>0&&j<10)
						{
            leftnumber+=(j*100);
						}
						}
            if(i==3)
						{
						if(j>0&&j<10)
						{
            leftnumber+=(j*10);
						}
						}
						if(i==4)
						{
						if(j>0&&j<10)
						{
            leftnumber+=(j);
						}
						}
						if (j < 10)
						{
							
							sprintf(nice, "%d",j);
							LCD_Write_Char(i, 1,nice[0] );
							i++;
						}
						DelayMs(50);
				
					}
				}
				if (k == 2)
				{
					for (i = 7; i < 10; )
					{
						j = MatrixKey();
						if(i==7)
						{
						if(j>0&&j<10)
						{
            backnumber+=(j*100);
						}
						}
            if(i==8)
						{
						if(j>0&&j<10)
						{
            backnumber+=(j*10);
						}
						}
						if(i==9)
						{
						if(j>0&&j<10)
						{
            backnumber+=(j);
						}
						}
						if (j < 10)
						{
							sprintf(nice, "%d",j);
							LCD_Write_Char(i, 1,nice[0] );
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
						j = MatrixKey();
	          if(i==12)
						{
						if(j>0&&j<10)
						{
            rightnumber+=(j*100);
						}
						}
            if(i==13)
						{
						if(j>0&&j<10)
						{
            rightnumber+=(j*10);
						}
						}
						if(i==14)
						{
						if(j>0&&j<10)
						{
            rightnumber+=(j);
						}
						}
						if (j < 10)
						{
							sprintf(nice, "%d",j                                       	               );
							LCD_Write_Char(i, 1,nice[0] );
							i++;
						}
					 	DelayMs(50);
					}

				  LCD_Write_String(0, 0, "                ");
				}
			}
		}
	
		
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
						S = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = S;
					}
			/*try*/
			S = (arr[1] + arr[2] + arr[3] + arr[4] / 4);
			if (S < rightnumber)
			{

			SPK = 0;//防止一直给喇叭通电造成损坏
			DelayMs(250);

			}
		  SPK = 1;
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
			for (i = 0; i < 10 - 1; i++)
				for (j = 0; j < 10 - 1 - i; j++)
					if (arr[j] > arr[j + 1])
					{
						S = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = S;
					}
			/*try*/
			S = ((arr[1] + arr[2] + arr[3] + arr[4] ) / 4);
			if (S < leftnumber)
			{
				
			SPK = 0;//防止一直给喇叭通电造成损坏
			DelayMs(250);
				
			}
		  SPK = 1;
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
			for (i = 0; i < 10 - 1; i++)
				for (j = 0; j < 10 - 1 - i; j++)
					if (arr[j] > arr[j + 1])
					{
						S = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = S;
					}
			/*try*/
			S = (arr[1] + arr[2] + arr[3] + arr[4]  /4);
			if (S < backnumber)
			{
				
			SPK = 0;//防止一直给喇叭通电造成损坏
			DelayMs(250);
				
			}
		  SPK = 1;
			sprintf(DisTempData, "B=%6.2f", S);
			LCD_Write_String(4, 0, DisTempData);

		}
	}
			}
		}	

	}
}
void TIM1init(void)
{

	TMOD |= 0x10;
	TH1 = 0x00;
	TL1 = 0x00;
	ET1 = 1;
	EA = 1;
}
void Timer0_isr(void) interrupt 2
{
	ECHOL = 0;
	ECHOB = 0;
	ECHOR = 0;
}
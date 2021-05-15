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
* 【程序功能】：QX-A11亚克力智能小车循迹避障红外遥控三合一		   			            			    
* 【注意事项】：避免小车撞向障碍物或小车轮子堵转，红外避障怕光,P32不能接其他设备
**********************************************************************************/
//通过按板子KEY键切换模式，默认循迹模式，LED1,LED2状态指示灯灭，按一次切换到避障模式，LDE1亮，LED2灭
//再按一次切换到红外遥控模式LED2亮，LED1灭。
//黑线贴3厘米宽，否则小车摆动很厉害
#include <REG52.H>//51头文件
#include <QX_A11.h>//QX_A11智能小车配置文件
unsigned char	pwm_val_left,pwm_val_right;	//中间变量，用户请勿修改。
unsigned char 	pwm_left,pwm_right;			//定义PWM输出高电平的时间的变量。用户操作PWM的变量。
unsigned char IRtime; 		//检测红外高电平持续时间（脉宽）
unsigned char IRcord[4];    //此数组用于储存分离出来的4个字节的数据（用户码2个字节+键值码2个字节）
unsigned char IRdata[33];   //此数组用于储存红外的33位数据（第一位为引导码用户码16+键值码16）
unsigned char TH_H,TL_H,TH_L,TL_L;

bit IRpro_ok, IRok;  //第一个用于红外接收4个字节完毕。IRok用为检测脉宽完毕
sbit OUT = P2^3;
#define		PWM_DUTY		200			//定义PWM的周期，数值为定时器0溢出周期，假如定时器溢出时间为100us，则PWM周期为20ms。
#define		PWM_HIGH_MIN	70			//限制PWM输出的最小占空比。用户请勿修改。
#define		PWM_HIGH_MAX	PWM_DUTY	//限制PWM输出的最大占空比。用户请勿修改。

void Timer0_Init(void); //定时器0初始化
void Timer1_Init(void); //定时器1初始化
void EXTI0_Init(void);//外部中断0初始化
void QXMBOT_LoadPWM(void);//装入PWM输出值 
void Delay_Ms(unsigned int ms);//毫秒级延时函数
void forward(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车前进 
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车左转  
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车右转
void back_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车后退
void stop(void);//QX_A11智能小车停车
void Tracking(void);//黑线循迹
void IRavoid(void);//红外避障
void QXMBOT_IRcordpro(void);//红外解码
void QXMBOT_IR_Remote(void);//红外遥控

/*主函数*/     
void main(void)
{
	unsigned char mode;
	EA_on;//开总中断
	Timer0_Init();//定时0初始化
	Timer1_Init();//定时1初始化
	EXTI0_Init();//外部中断0初始化
	while(1)
	{
		if(KEY==0)//判断KEY是否按下
		{
			stop();//停车
			beep=0;//蜂鸣器开启
			Delay_Ms(10); //软件消抖
			if(KEY==0)//再次判断KEY是否按下
			{
				mode++;
				while(!KEY);//松手检测
				beep=1;//蜂鸣器关闭	
			}
		}
		if(mode > 2)	mode = 0;
		switch(mode)
		{
			case 0:	 LED1=1,LED2=1; Tracking(); break; //红外循迹模式,LED1,LED2状态指示灯熄灭
			case 1:	 LED1=0,LED2=1; IRavoid(); break;  //红外避障模式,LED1亮,LED2灭
			case 2:	 LED1=1,LED2=0; QXMBOT_IR_Remote(); break;//红外遥控模式,LED1灭,LED2亮
			default: stop(); /*停车*/	 break;
		}
	}	
}


/*********************************************
QX_A11智能小车前进
入口参数：LeftSpeed，RightSpeed
出口参数: 无
说明：LeftSpeed，RightSpeed分别设置左右车轮转速
**********************************************/
void forward(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//设置速度
	left_motor_go; //左电机前进
	right_motor_go; //右电机前进
}
/*小车左转*/
/*********************************************
QX_A11智能小车左转
入口参数：LeftSpeed，RightSpeed
出口参数: 无
说明：LeftSpeed，RightSpeed分别设置左右车轮转速
**********************************************/
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//设置速度
	left_motor_back; //左电机后退
	right_motor_go; //右电机前进	
}

/*********************************************
QX_A11智能小车右转
入口参数：LeftSpeed，RightSpeed
出口参数: 无
说明：LeftSpeed，RightSpeed分别设置左右车轮转速
**********************************************/
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//设置速度
	right_motor_back;//右电机后退
	left_motor_go;    //左电机前进
}
/*********************************************
QX_A11智能小车后退
入口参数：LeftSpeed，RightSpeed
出口参数: 无
说明：LeftSpeed，RightSpeed分别设置左右车轮转速
**********************************************/
void back_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//设置速度
	right_motor_back;//右电机后退
	left_motor_back; //左电机后退
}
/*********************************************
QX_A11智能小车停车
入口参数：无
出口参数: 无
说明：QX_A11智能小车停车
**********************************************/
void stop(void)
{
	left_motor_stops;
	right_motor_stops;
}
/*********************************************
QX_A11智能小车PWM输出
入口参数：无
出口参数: 无
说明：装载PWM输出,如果设置全局变量pwm_left,pwm_right分别配置左右输出高电平时间
**********************************************/
void QXMBOT_LoadPWM(void)
{
	if(pwm_left > PWM_HIGH_MAX)		pwm_left = PWM_HIGH_MAX;	//如果左输出写入大于最大占空比数据，则强制为最大占空比。
	if(pwm_left < PWM_HIGH_MIN)		pwm_left = PWM_HIGH_MIN;	//如果左输出写入小于最小占空比数据，则强制为最小占空比。
	if(pwm_right > PWM_HIGH_MAX)	pwm_right = PWM_HIGH_MAX;	//如果右输出写入大于最大占空比数据，则强制为最大占空比。
	if(pwm_right < PWM_HIGH_MIN)	pwm_right = PWM_HIGH_MIN;	//如果右输出写入小于最小占空比数据，则强制为最小占空比。
	if(pwm_val_left<=pwm_left)		Left_moto_pwm = 1;  //装载左PWM输出高电平时间
	else Left_moto_pwm = 0; 						    //装载左PWM输出低电平时间
	if(pwm_val_left>=PWM_DUTY)		pwm_val_left = 0;	//如果左对比值大于等于最大占空比数据，则为零

	if(pwm_val_right<=pwm_right)	Right_moto_pwm = 1; //装载右PWM输出高电平时间
	else Right_moto_pwm = 0; 							//装载右PWM输出低电平时间
	if(pwm_val_right>=PWM_DUTY)		pwm_val_right = 0;	//如果右对比值大于等于最大占空比数据，则为零
}
//红外循迹
void Tracking()
{
	//为0 没有识别到黑线 为1识别到黑线
	char data1,data2 = left_led1,data3 = right_led1;
	data1 = data2*10+data3;
	if(data1 == 11)//在黑线上，前进
	{
		forward(120,120);//前进
	}
	else
	{
	 	if(data1 == 10)//小幅偏右，左转
		{
			left_run(80,160);//左转
		}
		if(data1 == 1)//小幅偏左，右转
		{
			right_run(160,80);//右转
		}
		if(data1 == 0)//大幅偏左或偏右，已脱离轨道
		{
			stop();	
		}
	}
}
//红外避障
void IRavoid()
{
	//为0 没有识别到黑线 为1识别到黑线
	char data1,data2 = left_led2,data3 = right_led2;
	data1 = data2*10+data3;
	if(data1 == 11)//没检测到障碍物，前进
	{
		forward(120,120);//前进
	}
	else
	{
	 	if(data1 == 10)//右检测到障碍物，左转，记录为状态1
		{
			left_run(120,120);//左转
		}
		if(data1 == 1)//左检测到障碍物，右转，记录为状态2
		{
			right_run(120,120);//右转
		}
		if(data1 == 0)//左右都检测到障碍物，后退
		{
			stop();//停车
			Delay_Ms(100);//执行停车的时间
			back_run(120,120);//后退
			Delay_Ms(200);//执行后退的时间
			right_run(120,120);//右转掉头
			Delay_Ms(280);//执行右转的时间				
		}
	}
}
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
//红外接收解码
void QXMBOT_IRcordpro()   				 //提取它的33次脉宽进行数据解码
{
	unsigned char i, j, k, cord, value;	/*i用于处理4个字节，j用于处理一个字节中每一位，k用于33次脉宽中的哪一位
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
/*********************************************
QX_A11智能小车红外遥控
入口参数：无
出口参数: 无
说明：无
**********************************************/
void QXMBOT_IR_Remote(void)
{
	if(IRok)    //判断脉宽是否检测完毕                    
	{   
		QXMBOT_IRcordpro();//根据脉宽解码出4个字节的数据
		IRok = 0;	//重新等待脉宽检测
		if(IRpro_ok) //判断是否解码完毕  
		{
	        switch(IRcord[2])
	   		{
			     case 0x18:  stop(); Delay_Ms(200); forward(120,120); 			 //前进
			             break;
			     case 0x52:  stop(); Delay_Ms(200); back_run(120,120);  			 //后退	 
			             break;
			     case 0x08:  stop(); Delay_Ms(200); left_run(120,120); 			 //左转
			             break;
				 case 0x5A:  stop(); Delay_Ms(200); right_run(120,120); 			 //右转
			             break;
				 case 0x1C:  stop();			     //停止
			             break;
					
				 default:break;
	   		}
			IRpro_ok = 0;
		}
	}		
}
/********************* Timer0初始化************************/
void Timer0_Init(void)
{
	TMOD |= 0x02; //定时器0工作方式2，8位自动重装
	TH0 = 0x00;  //高8位装入0那么定时器溢出一次的时间是256个机器周期
	TL0 = 0x00;
	ET0 = 1;	   //定时器0中断
	TR0 = 1;     //启动定时器0	
}
/********************* Timer0初始化************************/
void Timer1_Init(void)
{
	TMOD |= 0x20;//定时器1，8位自动重装模块
	TH1 = 164;
	TL1 = 164;//11.0592M晶振，12T溢出时间约等于100微秒
	TR1 = 1;//启动定时器1
	ET1 = 1;//允许定时器1中断	
}
/********************* 外部中断0初始化************************/
void EXTI0_Init(void)
{
	IT0 = 1;	   //设置外部中断0为跳沿触发方式，来一个下降沿触发一次
	EX0 = 1;	   //启动外部中断0	
}
/********************* 外部中断0中断函数************************/
void QXMBOT_int0() interrupt 0	  		//定义外部中断0
{
	static unsigned char i;	 			//	声明静态变量（在跳出函数后在回来执行的时候不会丢失数值）i用于把33次高电平的持续时间存入IRdata
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
/********************* Timer0中断函数************************/
void timer0_int (void) interrupt 1
{
	 IRtime++; 			   //检测脉宽，1次为278us
}
/********************* Timer0中断函数************************/
void timer1_int (void) interrupt 3
{
	 pwm_val_left++;
	 pwm_val_right++;
	 QXMBOT_LoadPWM();//装载PWM输出
}	
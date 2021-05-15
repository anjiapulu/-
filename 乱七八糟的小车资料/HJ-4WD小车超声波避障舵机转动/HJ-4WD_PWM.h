/*****************HJ-4WD-WIFI四驱蓝牙WIFI智能小车例程*****************
*  平台：HJ-4WD/HJ-E/HL-1智能小车 + Keil U4 + STC89C52RC
*  名称：
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com	智能小车网站：WWW.HLMCU.COM 机器人网站：www.hjduino.com
*  编写：慧净
*  日期：2008-8-08
*  交流:智能车QQ:1526248688  开发板QQ:398115088  销售QQ:3309342008
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://www.hlmcu.com/bbs
*  免费结缘：5星好评赠送18个资料包，追加评价后再加送资料，网上网盘下载
*  视频教程：本小车配套详细视频教程，有需要请到慧净电子网站免费下载
---关注慧净电子微信公众号免费下载配套的视频教程---
******************************************************************/
//注意程序只做参考之用，要达到最理想的效果，还需要同学们细心调试。
//控制板跳线帽接法 
//J6-1 P1.0至P1.7 IO口处跳线帽全部接上 	 
//如果程序中有PWM功能，需要把J6-2 下排焊针用杜邦线接到 P0.0  P0.1 P0.2 P0.3 IO口上--详细看课件说明
#ifndef _LED_H_
#define _LED_H_
	//控制板跳线帽接法 

    //定义小车驱动模块输入IO口 
sbit IN1=P1^0;	   //  右1电机	   高电平前进 
sbit IN2=P1^1;	   //  右1电机     高电平后退	可以改接成PWM输出
sbit IN3=P1^2;	   //  右2电机     高电平后退
sbit IN4=P1^3;	   //  右2电机     高电平前进	可以改接成PWM输出
sbit IN5=P1^4;	   //  左1电机     高电平前进
sbit IN6=P1^5;	   //  左1电机     高电平后退	可以改接成PWM输出
sbit IN7=P1^6;	   //  左2电机     高电平后退
sbit IN8=P1^7;	   //  左2电机     高电平前进	可以改接成PWM输出

	/***蜂鸣器接线定义*****/
    sbit BUZZ=P2^6;

	//传感器定义 R是右(right),L是左(left)	  小车对着自己看时 分的左右
    //循迹传感器X 左P3.6  右P3.5
	#define Left_X_led        P3_6	 //P3_6接左边 红外循迹传感器 接第3路输出信号即中控板上面标记为P3
	#define Right_X_led       P3_5	 //P3_5接右边 红外循迹传感器 接第2路输出信号即中控板上面标记为P2

	//避障传感器B 左P3.7  右P3.4  
 	#define Left_B_led        P3_7	 //P3_7接左边 红外避障传感器 接第4路输出信号即中控板上面标记为P4
	#define Right_B_led       P3_4	 //P3_4接右边 红外避障传感器 接第1路输出信号即中控板上面标记为P1
		
	//电机PWM调速度IO口定义
	#define Left_moto_pwm	    P0_0	 //PWM信号端
	#define Left_moto_pwm1	  P0_1	
	#define Right_moto_pwm	  P0_2
	#define Right_moto_pwm1	  P0_3								 
	//电机转向定义							 
	#define Left_moto_go      {IN5=1,IN6=0,IN7=0,IN8=1;}     //左边两个电机向前走
	#define Right_moto_back     {IN1=0,IN2=1,IN3=1,IN4=0;}	//右边两个电机向后走
	#define Left_moto_Stop    {IN5=0,IN6=0,IN7=0,IN8=0;}    //左边两个电机停转
	#define Right_moto_Stop   {IN1=0,IN2=0,IN3=0,IN4=0;}	//右边两个电机停转	                    
	#define Right_moto_go     {IN1=1,IN2=0,IN3=0,IN4=1;}	//右边两个电机向前走
	#define Left_moto_back      {IN5=0,IN6=1,IN7=1,IN8=0;}     //左边两个电机向后走
	   
	char code str[] =  "收到指令，向前!\n";
	char code str1[] = "收到指令，向后!\n";
	char code str2[] = "收到指令，向左!\n";
	char code str3[] = "收到指令，向右!\n";
	char code str4[] = "收到指令，停止!\n";

	bit  flag_REC=0; 
	bit  flag    =0;  
	

	unsigned char  i=0;
	unsigned char  dat=0;
    unsigned char  buff[5]=0; //接收缓冲字节

	//定义变量
	unsigned char pwm_val_left  =0;//变量定义
	unsigned char push_val_left =0;// 左电机占空比N/10
	unsigned char pwm_val_right =0;
	unsigned char push_val_right=0;// 右电机占空比N/10
	bit Right_moto_stop=1;
	bit Left_moto_stop =1;
	unsigned  int  time=0;
   
/************************************************************************/
//延时函数	
   void delay(unsigned int k)
{    
     unsigned int x,y;
	 for(x=0;x<k;x++) 
	   for(y=0;y<2000;y++);
}
/************************************************************************/
//前速前进
     void  run(void)
{
   push_val_left=4;	 //速度调节变量 0-9。。。0最小，9最大
	 push_val_right=4;
	 Left_moto_go ;   //左电机往前走
	 Right_moto_go ;  //右电机往前走
}

void backrun(void)
{
     push_val_left=6;	 //速度调节变量 0-9。。。0最小，9最大
	 push_val_right=6;
		IN1=0;		 //右1电机     高电平前进 
		IN2=1;		 //右1电机     高电平后退
		IN3=1;		 //右2电机     高电平后退
		IN4=0;		 //右2电机     高电平前进
		
		IN5=0;		 //左1电机     高电平前进
		IN6=1;		 //左1电机     高电平后退
		IN7=1;		 //左2电机     高电平后退
		IN8=0;		 //左2电机     高电平前进
}

//左转
     void  leftrun(void)
{	 
     push_val_left=4;
	 push_val_right=4;
	 Left_moto_go ;   //左电机往前走
	 Right_moto_back ;  //右电机往后走
}

//右转
     void  rightrun(void)
{ 
	 push_val_left=4;
	 push_val_right=4;
	 Left_moto_back ;   //左电机往后走
	 Right_moto_go ;  //右电机往前走
}
//STOP
     void  stoprun(void)
{
    
	 Left_moto_Stop ;   //左电机往前走
	 Right_moto_Stop ;  //右电机往前走
}
/************************************************************************/
//字符串发送函数
	  void send_str( )
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str[i] != '\0')
	   {
		SBUF = str[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }
	
		  void send_str1( )
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str1[i] != '\0')
	   {
		SBUF = str1[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }	

			  void send_str2( )
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str2[i] != '\0')
	   {
		SBUF = str2[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }	
	    	
			  void send_str3()
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str3[i] != '\0')
	   {
		SBUF = str3[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }	

	      void send_str4()
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str4[i] != '\0')
	   {
		SBUF = str4[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }	
	    	
	    	
/************************************************************************/
/*                    PWM调制电机转速                                   */
/************************************************************************/
/*                    左电机调速                                        */
/*调节push_val_left的值改变电机转速,占空比            */
		void pwm_out_left_moto(void)
{  
   if(Left_moto_stop)
   {
    if(pwm_val_left<=push_val_left)
	       {
		     Left_moto_pwm=1; 
		     Left_moto_pwm1=1; 
		   }
	else 
	       {
	         Left_moto_pwm=0;
		     Left_moto_pwm1=0; 
		   }
	if(pwm_val_left>=10)
	       pwm_val_left=0;
   }
   else    
          {
           Left_moto_pwm=0;
           Left_moto_pwm1=0; 
		  }
}
/******************************************************************/
/*                    右电机调速                                  */  
   void pwm_out_right_moto(void)
{ 
  if(Right_moto_stop)
   { 
    if(pwm_val_right<=push_val_right)
	      {
	       Right_moto_pwm=1; 
		   Right_moto_pwm1=1; 
		   }
	else 
	      {
		   Right_moto_pwm=0;
		   Right_moto_pwm1=0; 
		  }
	if(pwm_val_right>=10)
	       pwm_val_right=0;
   }
   else    
          {
           Right_moto_pwm=0;
           Right_moto_pwm1=0; 
	      }
}
       
/***************************************************/
///*TIMER0中断服务子函数产生PWM信号*/
 	void timer0()interrupt 1   using 2
{
     TH0=0XFc;	  //1Ms定时
	 TL0=0X18;
	 time++;
	 pwm_val_left++;
	 pwm_val_right++;
	 pwm_out_left_moto();
	 pwm_out_right_moto();
 }	

/*********************************************************************/	

#endif
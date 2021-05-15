/*****************HJ-4WD-WIFI四驱蓝牙WIFI智能小车例程*****************
*  平台：HJ-4WD/HJ-E/HL-1智能小车 + Keil U4 + STC89C52RC
*  名称：
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com	智能小车专用网站：WWW.HLMCU.COM 机器人网站：www.hjduino.com
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
//控制板跳线帽接法 
//J6-1 P1.0至P1.7 IO口处跳线帽全部接上
    // 本程序不输入PWM小车能全速度运行。
    // 本程序不输入PWM，J21 PWM 4个跳线帽不要装上，把J20(IN)/J22(EN) 8个跳线帽装上，这样小车就能全速度运行。	
	//注意程序只做参考之用，要达到最理想的效果，还需要同学们细心调试。	
	//注意超声波接线，急性之人经常接错线，烧坏模块，请一定要核对好再通电试验，模块接错线烧坏不保修，不换货的。
	/****************************************************************************
	 硬件连接
	 舵机有三条线定义：

     暗灰： GND

     红色： VCC 4.8-5.2V

     橙黄线： 脉冲输入

	 把舵机插入单片机J3接口中	 --注意不要接错线，否则烧坏舵机，不保修，不换货。
	 超声波用杜邦线接到J1口中
	 自己安装好舵机，还有超声波固定架，小车测试时小心不要碰撞到物体，否则容易断固定支架
	****************************************************************************/

	#include <AT89x51.H>
  #include <HJ-4WD_PWM.H>
	#include <intrins.h>

	#define Sevro_moto_pwm     P2_7	   //接舵机信号端输入PWM信号调节速度

	#define  ECHO  P2_4				   //超声波接口定义
	#define  TRIG  P2_5				   //超声波接口定义

	//HJ-4WD小车驱动接线定义


	unsigned char const discode[] ={ 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xBF,0xff/*-*/};
	unsigned char const positon[3]={ 0xfe,0xfd,0xfb};
	unsigned char disbuff[4]	  ={ 0,0,0,0,};
  unsigned char posit=0;


  unsigned long S=0;
	unsigned long S1=0;
	unsigned long S2=0;
	unsigned long S3=0;
	unsigned long S4=0;
	unsigned int  timer=0;			//延时基准变量
	unsigned char timer1=0;			//扫描时间变量					

/************************************************************************/
    void Display(void)				  //扫描数码管
	{
	 if(posit==0)
	 {P0=(discode[disbuff[posit]])&0x7f;}//产生点
	 else
	 {P0=discode[disbuff[posit]];}

	  if(posit==0)
	 { P2_1=0;P2_2=1;P2_3=1;}
	  if(posit==1)
	  {P2_1=1;P2_2=0;P2_3=1;}
	  if(posit==2)
	  {P2_1=1;P2_2=1;P2_3=0;}
	  if(++posit>=3)
	  posit=0;
	}
/************************************************************************/
     void  StartModule() 		      //启动测距信号
   {
	  TRIG=1;			                
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  TRIG=0;
   }
 /***************************************************/
	  void Conut(void)		   //计算距离
	{
	  while(!ECHO);		       //当RX为零时等待
	  TR0=1;			       //开启计数
	  while(ECHO);			   //当RX为1计数并等待
	  TR0=0;				   //关闭计数
	  time=TH0*256+TL0;		   //读取脉宽长度
	  TH0=0;
	  TL0=0;
	  S=(time*1.7)/100;        //算出来是CM
	  disbuff[0]=S%1000/100;   //更新显示
	  disbuff[1]=S%1000%100/10;
	  disbuff[2]=S%1000%10 %10;
	}
/************************************************************************/

/************************************************************************/
 void  COMM( void ) 	//方向函数	      
  {
  	     
		 
		  push_val_left=5;	  //舵机向左转90度
		  timer=0;
		  while(timer<=4000); //延时400MS让舵机转到其位置		 4000
		  StartModule();	  //启动超声波测距
          Conut();	 		  //计算距离
		  S2=S;  
  
		  push_val_left=23;	  //舵机向右转90度
		  timer=0;
		  while(timer<=4000); //延时400MS让舵机转到其位置
		  StartModule();	  //启动超声波测距
          Conut();			  //计算距离
		  S4=S; 	
	

		  push_val_left=14;	  //舵机归中
		  timer=0;
		  while(timer<=4000); //延时400MS让舵机转到其位置

		  StartModule();	  //启动超声波测距
          Conut();			  //计算距离
		  S1=S; 	

          if((S2<20)||(S4<20)) //只要左右各有距离小于，20CM小车后退
		  {
		  backrun();		   //后退
		  timer=0;
		  while(timer<=2000);
		  }
		   
		  if(S2>S4)		 
		     {
				rightrun();  	//车的左边比车的右边距离小	右转	
		        timer=0;
		        while(timer<=1500);
		     }				      
		       else
		     {
		       leftrun();		//车的左边比车的右边距离大	左转
		       timer=0;
		       while(timer<=1500);
		     }
		  			   

}

/************************************************************************/
/*                    PWM调制电机转速                                   */
/************************************************************************/
/*                    左电机调速                                        */
/*调节push_val_left的值改变电机转速,占空比            */
		void pwm_Servomoto(void)
{  
 
    if(pwm_val_left<=push_val_left)
	       Sevro_moto_pwm=1; 
	else 
	       Sevro_moto_pwm=0;
	if(pwm_val_left>=200)
	pwm_val_left=0;
 
}
/***************************************************/
///*TIMER1中断服务子函数产生PWM信号*/
 	void time1()interrupt 3   using 2
{	
     TH1=(65536-100)/256;	  //100US定时
	 TL1=(65536-100)%256;
	 timer++;				  //定时器100US为准。在这个基础上延时
	 pwm_val_left++;
	 pwm_Servomoto();

	 timer1++;				 //2MS扫一次数码管
	 if(timer1>=20)
	 {
	 timer1=0;
	 Display();	
	 }
 }
/***************************************************/
///*TIMER0中断服务子函数产生PWM信号*/
 /***************************************************/

	void main(void)
{
	TMOD=0X11;
	TH1=(65536-100)/256;	  //100US定时
	TL1=(65536-100)%256;
	TH0=0XFc;
	TL0=0X18;  
	TR1= 1;
	ET1= 1;
	ET0= 1;
	EA = 1;
	delay(100);
  push_val_left=14;	  //舵机归中


	while(1)		       /*无限循环*/
	{ 
   while(Left_X_led==1&&Right_X_led==1)
	 {
	  run();
   }

	
	    while(Right_X_led==0||Left_X_led==0)/*循迹*/
	 {

				if (Left_X_led == 1 && Right_X_led == 0)
				{
					Left_moto_go;
					Right_moto_back;
					delay(50);
				}
				if (Right_X_led == 1 && Left_X_led == 0)
				{

					Right_moto_go;
					Left_moto_back;
					delay(50);
				}
				if(Right_X_led==0&&Left_X_led==0)
				{
	    if(timer>=1000)	  //100MS检测启动检测一次	 1000
	   {
	       timer=0;
		   StartModule(); //启动检测
           Conut();		  //计算距离
           if(S<25)		  //距离小于25CM
		   {
		   stoprun();	  //小车停止
		   COMM(); 		  //方向函数
		   }
		   else
		   if(S>30)		  //距离大于，30CM往前走
		   run();
	   }
	 }
 }
	 
  }
	  
	  
    
}

	
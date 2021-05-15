/*****************HJ-4WD慧净四驱蓝牙智能小车例程*****************
*  平台：HJ-4WD/HJ-E/HL-1智能小车 + Keil U4 + STC89C52
*  名称：
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com	智能小车专用网站：WWW.HLMCU.COM
*  编写：
*  日期：2008-8-08
*  交流:智能车QQ:1526248688  开发板QQ:398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.haotui.com 
*  免费结缘：5星好评赠送18个资料包，追加评价后再加送20G资料，网上网盘下载
*  视频教程：本小车配套详细视频教程，有需要请到慧净网站免费下载
******************************************************************/
    // 本程序不输入PWM，小车全速度运行。	
	//注意程序只做参考之用，要达到最理想的效果，还需要同学们细心调试。	
	//注意蓝牙模块接线，急性之人经常接错线，烧坏模块，请一定要核对好再通电试验，模块接错线烧坏不保修，不换货的。
	/****************************************************************************
	 硬件连接
	 蓝牙有4条线定义：
	  VCC	 5V
      GND	 GND
	  TDX	 TX
	  RXD	 RD
	 把蓝牙插入单片机J2接口中	 --注意不要接错线，否则烧坏模块，不保修，不换货。
	****************************************************************************/

#include<AT89x51.H>
#include<HJ-4WD_PWM.H>		  //包含HJ-4WD蓝牙智能小车驱动IO口定义等函数

	//HJ-4WD小车驱动接线定义

	#define left     'C'
    #define right    'D'
	#define up       'A'
    #define down     'B'
	#define stop     'F'
   sbit lanya=P3^2;
	 sbit zidong=P3^3;
	 int m=0,n=0;
/************************************************************************/	
//延时函数	


/************************************************************************/
//字符串发送函数

	    	
	    	
/************************************************************************/

/************************************************************************/
void sint() interrupt 4	  //中断接收3个字节
{ 
 
    if(RI)	                 //是否接收中断
    {
       RI=0;
       dat=SBUF;
       if(dat=='O'&&(i==0)) //接收数据第一帧
         {
            buff[i]=dat;
            flag=1;        //开始接收数据
         }
       else
      if(flag==1)
     {
      i++;
      buff[i]=dat;
      if(i>=2)
      {i=0;flag=0;flag_REC=1 ;}  // 停止接收
     }
	 }
}
/*********************************************************************/		 
/*--主函数--*/
	void main(void)
{
	int k=0;
		P1=0X00;	  //小车停止
		TMOD=0X21;
    TH0= 0XFc;		  //1ms定时
    TL0= 0X18;
		TH1=0xFd;  		   //11.0592M晶振，9600波特率
    TL1=0xFd;
    SCON=0x50;  
    PCON=0x00; 
    TR1=1;
    TR0= 1;
    ET0= 1;
	  EA = 1;
	  ES = 1;
	while(1)
		{
	 if(lanya==0)
	 {
	 k=2;
	 }
   if(zidong==0)
	 {
	 k=1;
	 }
	 
	 if(k==1)/*自动档*/
	 {

   while(Right_B_led==0||Left_B_led==0||(Right_B_led==0&&Left_B_led==0))/*红外避障*/
	 {
	    if(Right_B_led==0&&Left_B_led==0)		//两边检测到红外 小车后退
				  {	  
		
			      backrun();					   //调用电机向后转函数
            delay(50);
						leftrun();//调用左转函数
						delay(30);

				  }

			   
				 		if(Right_B_led==0&&Left_B_led==1)		//右边检测到红外   小车需要向左转
				  {	  
		
			      leftrun();//调用左转函数
						delay(10);
				  }

			       if(Left_B_led==0&&Right_B_led==1)	    //左边检测到红外   小车需要向右转
			 	 {
					   rightrun();//调用右转函数
				     delay(10);
			     }		
	 
	 }
	
	
	 while(Right_B_led==1&&Left_B_led==1)                                 /*循迹*/
		{
			
	 if(Left_X_led==1&&Right_X_led==1)
	 {
	 run();
	 }
	 if(Left_X_led==1&&Right_X_led==0)	 
	{
			
		Left_moto_go;						
		Right_moto_back;
				 
	}
			   
		if(Right_X_led==1&&Left_X_led==0)		
	{	  

		Right_moto_go;				
	  Left_moto_back;

 } 
		}

	
	 }	
   if(k==2)/*手动档*/
	 {
		
	 	 if(flag_REC==1)				    //
	   {
		flag_REC=0;
		if(buff[0]=='O'&&buff[1]=='N')	//第一个字节为O，第二个字节为N，第三个字节为控制码
		switch(buff[2])
	     {
		      case up :						    // 前进
			  send_str( );
			  run();
			  break;
		      case down:						// 后退
			   send_str1( );
			  backrun();
			  break;
		      case left:						// 左转
			   send_str3( );
			  leftrun();
			  break;
		      case right:						// 右转
			  send_str2( );
			  rightrun();
			  break;
		      case stop:						// 停止
			   send_str4( );
			  stoprun();
			  break;

	     }
      
					 
	 }
	 }
      
					 
	 
	
   }
}	
/*****************HJ-4WD-WIFI��������WIFI����С������*****************
*  ƽ̨��HJ-4WD/HJ-E/HL-1����С�� + Keil U4 + STC89C52RC
*  ���ƣ�
*  ��˾���۾����ӿƼ����޹�˾
*  �Ա���http://shop37031453.taobao.com       
*  ��վ��www.hjmcu.com	����С����վ��WWW.HLMCU.COM ��������վ��www.hjduino.com
*  ��д���۾�
*  ���ڣ�2008-8-08
*  ����:���ܳ�QQ:1526248688  ������QQ:398115088  ����QQ:3309342008
*  ����:11.0592MHZ
*  ˵������ѿ�Դ�����ṩԴ���������������ֱ�ӵ��۾���̳����
*  ��̳��http://www.hlmcu.com/bbs
*  ��ѽ�Ե��5�Ǻ�������18�����ϰ���׷�����ۺ��ټ������ϣ�������������
*  ��Ƶ�̳̣���С��������ϸ��Ƶ�̳̣�����Ҫ�뵽�۾�������վ�������
---��ע�۾�����΢�Ź��ں�����������׵���Ƶ�̳�---
******************************************************************/
//ע�����ֻ���ο�֮�ã�Ҫ�ﵽ�������Ч��������Ҫͬѧ��ϸ�ĵ��ԡ�
//���ư�����ñ�ӷ� 
//J6-1 P1.0��P1.7 IO�ڴ�����ñȫ������ 	 
//�����������PWM���ܣ���Ҫ��J6-2 ���ź����öŰ��߽ӵ� P0.0  P0.1 P0.2 P0.3 IO����--��ϸ���μ�˵��
#ifndef _LED_H_
#define _LED_H_
	//���ư�����ñ�ӷ� 

    //����С������ģ������IO�� 
sbit IN1=P1^0;	   //  ��1���	   �ߵ�ƽǰ�� 
sbit IN2=P1^1;	   //  ��1���     �ߵ�ƽ����	���ԸĽӳ�PWM���
sbit IN3=P1^2;	   //  ��2���     �ߵ�ƽ����
sbit IN4=P1^3;	   //  ��2���     �ߵ�ƽǰ��	���ԸĽӳ�PWM���
sbit IN5=P1^4;	   //  ��1���     �ߵ�ƽǰ��
sbit IN6=P1^5;	   //  ��1���     �ߵ�ƽ����	���ԸĽӳ�PWM���
sbit IN7=P1^6;	   //  ��2���     �ߵ�ƽ����
sbit IN8=P1^7;	   //  ��2���     �ߵ�ƽǰ��	���ԸĽӳ�PWM���

	/***���������߶���*****/
    sbit BUZZ=P2^6;

	//���������� R����(right),L����(left)	  С�������Լ���ʱ �ֵ�����
    //ѭ��������X ��P3.6  ��P3.5
	#define Left_X_led        P3_6	 //P3_6����� ����ѭ�������� �ӵ�3·����źż��пذ�������ΪP3
	#define Right_X_led       P3_5	 //P3_5���ұ� ����ѭ�������� �ӵ�2·����źż��пذ�������ΪP2

	//���ϴ�����B ��P3.7  ��P3.4  
 	#define Left_B_led        P3_7	 //P3_7����� ������ϴ����� �ӵ�4·����źż��пذ�������ΪP4
	#define Right_B_led       P3_4	 //P3_4���ұ� ������ϴ����� �ӵ�1·����źż��пذ�������ΪP1
		
	//���PWM���ٶ�IO�ڶ���
	#define Left_moto_pwm	    P0_0	 //PWM�źŶ�
	#define Left_moto_pwm1	  P0_1	
	#define Right_moto_pwm	  P0_2
	#define Right_moto_pwm1	  P0_3								 
	//���ת����							 
	#define Left_moto_go      {IN5=1,IN6=0,IN7=0,IN8=1;}     //������������ǰ��
	#define Right_moto_back     {IN1=0,IN2=1,IN3=1,IN4=0;}	//�ұ�������������
	#define Left_moto_Stop    {IN5=0,IN6=0,IN7=0,IN8=0;}    //����������ͣת
	#define Right_moto_Stop   {IN1=0,IN2=0,IN3=0,IN4=0;}	//�ұ��������ͣת	                    
	#define Right_moto_go     {IN1=1,IN2=0,IN3=0,IN4=1;}	//�ұ����������ǰ��
	#define Left_moto_back      {IN5=0,IN6=1,IN7=1,IN8=0;}     //���������������
	   
	char code str[] =  "�յ�ָ���ǰ!\n";
	char code str1[] = "�յ�ָ����!\n";
	char code str2[] = "�յ�ָ�����!\n";
	char code str3[] = "�յ�ָ�����!\n";
	char code str4[] = "�յ�ָ�ֹͣ!\n";

	bit  flag_REC=0; 
	bit  flag    =0;  
	

	unsigned char  i=0;
	unsigned char  dat=0;
    unsigned char  buff[5]=0; //���ջ����ֽ�

	//�������
	unsigned char pwm_val_left  =0;//��������
	unsigned char push_val_left =0;// ����ռ�ձ�N/10
	unsigned char pwm_val_right =0;
	unsigned char push_val_right=0;// �ҵ��ռ�ձ�N/10
	bit Right_moto_stop=1;
	bit Left_moto_stop =1;
	unsigned  int  time=0;
   
/************************************************************************/
//��ʱ����	
   void delay(unsigned int k)
{    
     unsigned int x,y;
	 for(x=0;x<k;x++) 
	   for(y=0;y<2000;y++);
}
/************************************************************************/
//ǰ��ǰ��
     void  run(void)
{
   push_val_left=4;	 //�ٶȵ��ڱ��� 0-9������0��С��9���
	 push_val_right=4;
	 Left_moto_go ;   //������ǰ��
	 Right_moto_go ;  //�ҵ����ǰ��
}

void backrun(void)
{
     push_val_left=6;	 //�ٶȵ��ڱ��� 0-9������0��С��9���
	 push_val_right=6;
		IN1=0;		 //��1���     �ߵ�ƽǰ�� 
		IN2=1;		 //��1���     �ߵ�ƽ����
		IN3=1;		 //��2���     �ߵ�ƽ����
		IN4=0;		 //��2���     �ߵ�ƽǰ��
		
		IN5=0;		 //��1���     �ߵ�ƽǰ��
		IN6=1;		 //��1���     �ߵ�ƽ����
		IN7=1;		 //��2���     �ߵ�ƽ����
		IN8=0;		 //��2���     �ߵ�ƽǰ��
}

//��ת
     void  leftrun(void)
{	 
     push_val_left=4;
	 push_val_right=4;
	 Left_moto_go ;   //������ǰ��
	 Right_moto_back ;  //�ҵ��������
}

//��ת
     void  rightrun(void)
{ 
	 push_val_left=4;
	 push_val_right=4;
	 Left_moto_back ;   //����������
	 Right_moto_go ;  //�ҵ����ǰ��
}
//STOP
     void  stoprun(void)
{
    
	 Left_moto_Stop ;   //������ǰ��
	 Right_moto_Stop ;  //�ҵ����ǰ��
}
/************************************************************************/
//�ַ������ͺ���
	  void send_str( )
                   // �����ִ�
    {
	    unsigned char i = 0;
	    while(str[i] != '\0')
	   {
		SBUF = str[i];
		while(!TI);				// �������ݴ���
		TI = 0;					// ������ݴ��ͱ�־
		i++;					// ��һ���ַ�
	   }	
    }
	
		  void send_str1( )
                   // �����ִ�
    {
	    unsigned char i = 0;
	    while(str1[i] != '\0')
	   {
		SBUF = str1[i];
		while(!TI);				// �������ݴ���
		TI = 0;					// ������ݴ��ͱ�־
		i++;					// ��һ���ַ�
	   }	
    }	

			  void send_str2( )
                   // �����ִ�
    {
	    unsigned char i = 0;
	    while(str2[i] != '\0')
	   {
		SBUF = str2[i];
		while(!TI);				// �������ݴ���
		TI = 0;					// ������ݴ��ͱ�־
		i++;					// ��һ���ַ�
	   }	
    }	
	    	
			  void send_str3()
                   // �����ִ�
    {
	    unsigned char i = 0;
	    while(str3[i] != '\0')
	   {
		SBUF = str3[i];
		while(!TI);				// �������ݴ���
		TI = 0;					// ������ݴ��ͱ�־
		i++;					// ��һ���ַ�
	   }	
    }	

	      void send_str4()
                   // �����ִ�
    {
	    unsigned char i = 0;
	    while(str4[i] != '\0')
	   {
		SBUF = str4[i];
		while(!TI);				// �������ݴ���
		TI = 0;					// ������ݴ��ͱ�־
		i++;					// ��һ���ַ�
	   }	
    }	
	    	
	    	
/************************************************************************/
/*                    PWM���Ƶ��ת��                                   */
/************************************************************************/
/*                    ��������                                        */
/*����push_val_left��ֵ�ı���ת��,ռ�ձ�            */
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
/*                    �ҵ������                                  */  
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
///*TIMER0�жϷ����Ӻ�������PWM�ź�*/
 	void timer0()interrupt 1   using 2
{
     TH0=0XFc;	  //1Ms��ʱ
	 TL0=0X18;
	 time++;
	 pwm_val_left++;
	 pwm_val_right++;
	 pwm_out_left_moto();
	 pwm_out_right_moto();
 }	

/*********************************************************************/	

#endif
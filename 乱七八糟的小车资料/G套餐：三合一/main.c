/*********************************************************************************
* ����дʱ�䡿�� 2020��12��12��
* ����    �ߡ��� �������:03
* ����    ������ 1.0
* ����    վ���� http://www.QXMBOT.com/ 
* ���Ա����̡��� http://qxmcu.taobao.com/ (ֱ����)
* ��ʵ��ƽ̨���� QX-A11�ǿ�������С��  STC89C52
* ���ⲿ���񡿣� 11.0592mhz	
* ������оƬ���� STC89C52
* �����뻷������ Keil ��Visio4
*	��Ȩ���У�����ؾ���
*	Copyright(C) QXMBOT
*	All rights reserved
***********************************************************************************
* ������˵��������ο�������ͼ��˵����
* �������ܡ���QX-A11�ǿ�������С��ѭ�����Ϻ���ң������һ		   			            			    
* ��ע�����������С��ײ���ϰ����С�����Ӷ�ת����������¹�,P32���ܽ������豸
**********************************************************************************/
//ͨ��������KEY���л�ģʽ��Ĭ��ѭ��ģʽ��LED1,LED2״ָ̬ʾ���𣬰�һ���л�������ģʽ��LDE1����LED2��
//�ٰ�һ���л�������ң��ģʽLED2����LED1��
//������3���׿�����С���ڶ�������
#include <REG52.H>//51ͷ�ļ�
#include <QX_A11.h>//QX_A11����С�������ļ�
unsigned char	pwm_val_left,pwm_val_right;	//�м�������û������޸ġ�
unsigned char 	pwm_left,pwm_right;			//����PWM����ߵ�ƽ��ʱ��ı������û�����PWM�ı�����
unsigned char IRtime; 		//������ߵ�ƽ����ʱ�䣨����
unsigned char IRcord[4];    //���������ڴ�����������4���ֽڵ����ݣ��û���2���ֽ�+��ֵ��2���ֽڣ�
unsigned char IRdata[33];   //���������ڴ�������33λ���ݣ���һλΪ�������û���16+��ֵ��16��
unsigned char TH_H,TL_H,TH_L,TL_L;

bit IRpro_ok, IRok;  //��һ�����ں������4���ֽ���ϡ�IRok��Ϊ����������
sbit OUT = P2^3;
#define		PWM_DUTY		200			//����PWM�����ڣ���ֵΪ��ʱ��0������ڣ����綨ʱ�����ʱ��Ϊ100us����PWM����Ϊ20ms��
#define		PWM_HIGH_MIN	70			//����PWM�������Сռ�ձȡ��û������޸ġ�
#define		PWM_HIGH_MAX	PWM_DUTY	//����PWM��������ռ�ձȡ��û������޸ġ�

void Timer0_Init(void); //��ʱ��0��ʼ��
void Timer1_Init(void); //��ʱ��1��ʼ��
void EXTI0_Init(void);//�ⲿ�ж�0��ʼ��
void QXMBOT_LoadPWM(void);//װ��PWM���ֵ 
void Delay_Ms(unsigned int ms);//���뼶��ʱ����
void forward(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11����С��ǰ�� 
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11����С����ת  
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11����С����ת
void back_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11����С������
void stop(void);//QX_A11����С��ͣ��
void Tracking(void);//����ѭ��
void IRavoid(void);//�������
void QXMBOT_IRcordpro(void);//�������
void QXMBOT_IR_Remote(void);//����ң��

/*������*/     
void main(void)
{
	unsigned char mode;
	EA_on;//�����ж�
	Timer0_Init();//��ʱ0��ʼ��
	Timer1_Init();//��ʱ1��ʼ��
	EXTI0_Init();//�ⲿ�ж�0��ʼ��
	while(1)
	{
		if(KEY==0)//�ж�KEY�Ƿ���
		{
			stop();//ͣ��
			beep=0;//����������
			Delay_Ms(10); //�������
			if(KEY==0)//�ٴ��ж�KEY�Ƿ���
			{
				mode++;
				while(!KEY);//���ּ��
				beep=1;//�������ر�	
			}
		}
		if(mode > 2)	mode = 0;
		switch(mode)
		{
			case 0:	 LED1=1,LED2=1; Tracking(); break; //����ѭ��ģʽ,LED1,LED2״ָ̬ʾ��Ϩ��
			case 1:	 LED1=0,LED2=1; IRavoid(); break;  //�������ģʽ,LED1��,LED2��
			case 2:	 LED1=1,LED2=0; QXMBOT_IR_Remote(); break;//����ң��ģʽ,LED1��,LED2��
			default: stop(); /*ͣ��*/	 break;
		}
	}	
}


/*********************************************
QX_A11����С��ǰ��
��ڲ�����LeftSpeed��RightSpeed
���ڲ���: ��
˵����LeftSpeed��RightSpeed�ֱ��������ҳ���ת��
**********************************************/
void forward(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//�����ٶ�
	left_motor_go; //����ǰ��
	right_motor_go; //�ҵ��ǰ��
}
/*С����ת*/
/*********************************************
QX_A11����С����ת
��ڲ�����LeftSpeed��RightSpeed
���ڲ���: ��
˵����LeftSpeed��RightSpeed�ֱ��������ҳ���ת��
**********************************************/
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//�����ٶ�
	left_motor_back; //��������
	right_motor_go; //�ҵ��ǰ��	
}

/*********************************************
QX_A11����С����ת
��ڲ�����LeftSpeed��RightSpeed
���ڲ���: ��
˵����LeftSpeed��RightSpeed�ֱ��������ҳ���ת��
**********************************************/
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//�����ٶ�
	right_motor_back;//�ҵ������
	left_motor_go;    //����ǰ��
}
/*********************************************
QX_A11����С������
��ڲ�����LeftSpeed��RightSpeed
���ڲ���: ��
˵����LeftSpeed��RightSpeed�ֱ��������ҳ���ת��
**********************************************/
void back_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//�����ٶ�
	right_motor_back;//�ҵ������
	left_motor_back; //��������
}
/*********************************************
QX_A11����С��ͣ��
��ڲ�������
���ڲ���: ��
˵����QX_A11����С��ͣ��
**********************************************/
void stop(void)
{
	left_motor_stops;
	right_motor_stops;
}
/*********************************************
QX_A11����С��PWM���
��ڲ�������
���ڲ���: ��
˵����װ��PWM���,�������ȫ�ֱ���pwm_left,pwm_right�ֱ�������������ߵ�ƽʱ��
**********************************************/
void QXMBOT_LoadPWM(void)
{
	if(pwm_left > PWM_HIGH_MAX)		pwm_left = PWM_HIGH_MAX;	//��������д��������ռ�ձ����ݣ���ǿ��Ϊ���ռ�ձȡ�
	if(pwm_left < PWM_HIGH_MIN)		pwm_left = PWM_HIGH_MIN;	//��������д��С����Сռ�ձ����ݣ���ǿ��Ϊ��Сռ�ձȡ�
	if(pwm_right > PWM_HIGH_MAX)	pwm_right = PWM_HIGH_MAX;	//��������д��������ռ�ձ����ݣ���ǿ��Ϊ���ռ�ձȡ�
	if(pwm_right < PWM_HIGH_MIN)	pwm_right = PWM_HIGH_MIN;	//��������д��С����Сռ�ձ����ݣ���ǿ��Ϊ��Сռ�ձȡ�
	if(pwm_val_left<=pwm_left)		Left_moto_pwm = 1;  //װ����PWM����ߵ�ƽʱ��
	else Left_moto_pwm = 0; 						    //װ����PWM����͵�ƽʱ��
	if(pwm_val_left>=PWM_DUTY)		pwm_val_left = 0;	//�����Ա�ֵ���ڵ������ռ�ձ����ݣ���Ϊ��

	if(pwm_val_right<=pwm_right)	Right_moto_pwm = 1; //װ����PWM����ߵ�ƽʱ��
	else Right_moto_pwm = 0; 							//װ����PWM����͵�ƽʱ��
	if(pwm_val_right>=PWM_DUTY)		pwm_val_right = 0;	//����ҶԱ�ֵ���ڵ������ռ�ձ����ݣ���Ϊ��
}
//����ѭ��
void Tracking()
{
	//Ϊ0 û��ʶ�𵽺��� Ϊ1ʶ�𵽺���
	char data1,data2 = left_led1,data3 = right_led1;
	data1 = data2*10+data3;
	if(data1 == 11)//�ں����ϣ�ǰ��
	{
		forward(120,120);//ǰ��
	}
	else
	{
	 	if(data1 == 10)//С��ƫ�ң���ת
		{
			left_run(80,160);//��ת
		}
		if(data1 == 1)//С��ƫ����ת
		{
			right_run(160,80);//��ת
		}
		if(data1 == 0)//���ƫ���ƫ�ң���������
		{
			stop();	
		}
	}
}
//�������
void IRavoid()
{
	//Ϊ0 û��ʶ�𵽺��� Ϊ1ʶ�𵽺���
	char data1,data2 = left_led2,data3 = right_led2;
	data1 = data2*10+data3;
	if(data1 == 11)//û��⵽�ϰ��ǰ��
	{
		forward(120,120);//ǰ��
	}
	else
	{
	 	if(data1 == 10)//�Ҽ�⵽�ϰ����ת����¼Ϊ״̬1
		{
			left_run(120,120);//��ת
		}
		if(data1 == 1)//���⵽�ϰ����ת����¼Ϊ״̬2
		{
			right_run(120,120);//��ת
		}
		if(data1 == 0)//���Ҷ���⵽�ϰ������
		{
			stop();//ͣ��
			Delay_Ms(100);//ִ��ͣ����ʱ��
			back_run(120,120);//����
			Delay_Ms(200);//ִ�к��˵�ʱ��
			right_run(120,120);//��ת��ͷ
			Delay_Ms(280);//ִ����ת��ʱ��				
		}
	}
}
/*====================================
������void Delay_Ms(INT16U ms)
������ms��������ʱ�β�
������12T 51��Ƭ������Ӧ��ʱ�Ӻ��뼶��ʱ����
====================================*/
void Delay_Ms(unsigned int ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 96000; 
		  while(--i);   //96T per loop
     }while(--ms);
}
//������ս���
void QXMBOT_IRcordpro()   				 //��ȡ����33������������ݽ���
{
	unsigned char i, j, k, cord, value;	/*i���ڴ���4���ֽڣ�j���ڴ���һ���ֽ���ÿһλ��k����33�������е���һλ
	cord����ȡ�������ʱ���ж��Ƿ����1������ʱ��*/
	k = 1; 						//�ӵ�һλ����ʼȡ����������������
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 8; j++)
		{
			cord = IRdata[k];	    //���������cord
			if(cord > 5)	 		//������������11.0592��t0�����ΪԼ278us*5=1390��ô�ж�Ϊ1
			value = value | 0x80;	/*���յ�ʱ�����Ƚ������λ��
			�����λ�ȷŵ�value�����λ�ں�0x08��λ��һ��
			��������ı�valua������λ����ֵֻ���������λΪ1*/
			if(j < 7)
			{
				value = value >> 1;	//valueλ�������ν���8λ���ݡ�
			}
			k++;				//ÿִ��һ������λ��1
		}
		IRcord[i] = value;	   //ÿ������һ���ֽڰ�������IRcord�����С�
		value = 0; 			   //����value�����´��ڴ�������
	}
	IRpro_ok = 1;				   //������4���ֽں�IRpro ok��1��ʾ����������	
}
/*********************************************
QX_A11����С������ң��
��ڲ�������
���ڲ���: ��
˵������
**********************************************/
void QXMBOT_IR_Remote(void)
{
	if(IRok)    //�ж������Ƿ������                    
	{   
		QXMBOT_IRcordpro();//������������4���ֽڵ�����
		IRok = 0;	//���µȴ�������
		if(IRpro_ok) //�ж��Ƿ�������  
		{
	        switch(IRcord[2])
	   		{
			     case 0x18:  stop(); Delay_Ms(200); forward(120,120); 			 //ǰ��
			             break;
			     case 0x52:  stop(); Delay_Ms(200); back_run(120,120);  			 //����	 
			             break;
			     case 0x08:  stop(); Delay_Ms(200); left_run(120,120); 			 //��ת
			             break;
				 case 0x5A:  stop(); Delay_Ms(200); right_run(120,120); 			 //��ת
			             break;
				 case 0x1C:  stop();			     //ֹͣ
			             break;
					
				 default:break;
	   		}
			IRpro_ok = 0;
		}
	}		
}
/********************* Timer0��ʼ��************************/
void Timer0_Init(void)
{
	TMOD |= 0x02; //��ʱ��0������ʽ2��8λ�Զ���װ
	TH0 = 0x00;  //��8λװ��0��ô��ʱ�����һ�ε�ʱ����256����������
	TL0 = 0x00;
	ET0 = 1;	   //��ʱ��0�ж�
	TR0 = 1;     //������ʱ��0	
}
/********************* Timer0��ʼ��************************/
void Timer1_Init(void)
{
	TMOD |= 0x20;//��ʱ��1��8λ�Զ���װģ��
	TH1 = 164;
	TL1 = 164;//11.0592M����12T���ʱ��Լ����100΢��
	TR1 = 1;//������ʱ��1
	ET1 = 1;//����ʱ��1�ж�	
}
/********************* �ⲿ�ж�0��ʼ��************************/
void EXTI0_Init(void)
{
	IT0 = 1;	   //�����ⲿ�ж�0Ϊ���ش�����ʽ����һ���½��ش���һ��
	EX0 = 1;	   //�����ⲿ�ж�0	
}
/********************* �ⲿ�ж�0�жϺ���************************/
void QXMBOT_int0() interrupt 0	  		//�����ⲿ�ж�0
{
	static unsigned char i;	 			//	������̬�������������������ڻ���ִ�е�ʱ�򲻻ᶪʧ��ֵ��i���ڰ�33�θߵ�ƽ�ĳ���ʱ�����IRdata
	static bit startflag;		//��ʼ���������־λ
	if(startflag)	 			//��ʼ����������
	{
		if( (IRtime < 53) && (IRtime >= 32) ) /*�ж��Ƿ��������룬�׵�ƽ9000us+��4500us	
		����Լ�����������11.0592������NECЭ����������8000-10000+��4000-5000 
		����Ѿ���������������ôi���ᱻ��0�ͻῪʼ���δ�������*/
			i = 0;				 //�������������ôִ��i=0�����浽IRdata�ĵ�һ��λ
		IRdata[i] = IRtime;  		 //��T0������������������������ʱ��浽�������浽�����ж�
		IRtime = 0;				 //�������㣬��һ���½��ص�ʱ���ڴ�������
		i++; 					 //�����������Ĵ���
		if(i == 33) 				 //�������34�� ������±��Ǵ�0��ʼi����33��ʾִ����34��
		{
		 	IRok = 1;				 //��ô��ʾ���������
			i = 0; 				 //�������������׼���´δ���
		}
	}
	else		  
	{
		IRtime = 0; 				 //�����뿪ʼ���������������㿪ʼ����
		startflag = 1;			 //��ʼ�����־λ��1
	}
}
/********************* Timer0�жϺ���************************/
void timer0_int (void) interrupt 1
{
	 IRtime++; 			   //�������1��Ϊ278us
}
/********************* Timer0�жϺ���************************/
void timer1_int (void) interrupt 3
{
	 pwm_val_left++;
	 pwm_val_right++;
	 QXMBOT_LoadPWM();//װ��PWM���
}	
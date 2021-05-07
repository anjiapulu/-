
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
                    ��ʱ��0��ʼ��
------------------------------------------------*/
void TIM0init(void)
{

  TMOD|= 0x01;//��ʱ��0������ʽ1
  TH0=0x00;    
  TL0=0x00; 
  ET0=1;
  EA=1;
}
/*------------------------------------------------
                    ������
------------------------------------------------*/
main()
{
  float S;       //�������
  TIM0init();    //��ʼ����ʱ��0
  LCD_Init();    //��ʼ��LCD
  while(1)
  {
   /*left*/
   TRIGL=1;       //�����ź��Ǹߵ�ƽ���壬��ȴ���10us
   DelayUs2x(10);
   TRIGL=0;
   while(!ECHOL); //�ȴ��ߵ�ƽ
   TR0=1;
   while(ECHOL);  //�ȴ��͵�ƽ
   TR0=0;
   S=TH0*256+TL0;//ȡ����ʱ��ֵ��8λ�͵�8λ�ϲ�
   S=S/58;       //Ϊʲô����58�������ף�  Y��=��X��*344��/2
			     // X��=�� 2*Y�ף�/344 -> X��=0.0058*Y�� -> ����=΢��/58 
   TH0=0;
   TL0=0;        //�����ʱ��0�Ĵ����е�ֵ
   sprintf(DisTempData,"L=%6.2f CM     ",S);//��ӡ������
   LCD_Write_String(0,0,DisTempData);       //��Һ��������ʾ
   DelayMs(250);                            //��ʱ���������ٶ�
   /*front*/
	 TRIGF=1;       //�����ź��Ǹߵ�ƽ���壬��ȴ���10us
   DelayUs2x(10);
   TRIGF=0;
   while(!ECHOF); //�ȴ��ߵ�ƽ
   TR0=1;
   while(ECHOF);  //�ȴ��͵�ƽ
   TR0=0;
   S=TH0*256+TL0;//ȡ����ʱ��ֵ��8λ�͵�8λ�ϲ�
   S=S/58;       //Ϊʲô����58�������ף�  Y��=��X��*344��/2
			     // X��=�� 2*Y�ף�/344 -> X��=0.0058*Y�� -> ����=΢��/58 
   TH0=0;
   TL0=0;        //�����ʱ��0�Ĵ����е�ֵ
   sprintf(DisTempData,"F=%6.2f CM     ",S);//��ӡ������
   LCD_Write_String(0,1,DisTempData);       //��Һ��������ʾ
   DelayMs(2500);   
	 /*RIGHT*/
	 TRIGR=1;       //�����ź��Ǹߵ�ƽ���壬��ȴ���10us
   DelayUs2x(10);
   TRIGR=0;
   while(!ECHOR); //�ȴ��ߵ�ƽ
   TR0=1;
   while(ECHOR);  //�ȴ��͵�ƽ
   TR0=0;
   S=TH0*256+TL0;//ȡ����ʱ��ֵ��8λ�͵�8λ�ϲ�
   S=S/58;       //Ϊʲô����58�������ף�  Y��=��X��*344��/2
			     // X��=�� 2*Y�ף�/344 -> X��=0.0058*Y�� -> ����=΢��/58 
   TH0=0;
   TL0=0;        //�����ʱ��0�Ĵ����е�ֵ
   sprintf(DisTempData,"R=%6.2f CM     ",S);//��ӡ������
   LCD_Write_String(0,1,DisTempData);       //��Һ��������ʾ
   DelayMs(2500);   
  }
 }

/*------------------------------------------------
                 ��ʱ���ж��ӳ���
------------------------------------------------*/
void Timer0_isr(void) interrupt 1
{
 ECHOL=0;
	ECHOF=0;
	 ECHOR=0;
}

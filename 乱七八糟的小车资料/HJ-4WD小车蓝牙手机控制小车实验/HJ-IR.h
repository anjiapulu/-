/*****************HJ-4WD�۾�������������С��ר��ͷ�ļ�*****************
*  ƽ̨��HJ-4WD/HJ-E/HL-1����С�� + Keil U4 + STC89C52
*  ���ƣ�
*  ��˾���۾����ӿƼ����޹�˾
*  �Ա���http://shop37031453.taobao.com       
*  ��վ��www.hjmcu.com	����С��ר����վ��WWW.HLMCU.COM
*  ��д���۾�
*  ���ڣ�2008-8-08
*  ����:���ܳ�QQ:1526248688  ������QQ:398115088
*  ����:11.0592MHZ
*  ˵������ѿ�Դ�����ṩԴ���������������ֱ�ӵ��۾���̳����
*  ��̳��http://hjdz.haotui.com 
*  ��ѽ�Ե��5�Ǻ�������18�����ϰ���׷�����ۺ��ټ���20G���ϣ�������������
*  ��Ƶ�̳̣���С��������ϸ��Ƶ�̳̣�����Ҫ�뵽�۾���վ�������
******************************************************************/
#ifndef _LED_H_
#define _LED_H_


    #define Imax 14000    //�˴�Ϊ����Ϊ11.0592ʱ��ȡֵ, 
    #define Imin 8000    //��������Ƶ�ʵľ���ʱ,
    #define Inum1 1450    //Ҫ�ı���Ӧ��ȡֵ��
    #define Inum2 700 
    #define Inum3 3000 

	unsigned char f=0;
    unsigned char Im[4]={0x00,0x00,0x00,0x00};
    unsigned char show[2]={0,0};
    unsigned long m,Tc;
    unsigned char IrOK;

   
	
//�ⲿ�жϽ������
  void intersvr1(void) interrupt 2 using 1
{
    Tc=TH0*256+TL0;                                               //��ȡ�ж�ʱ����ʱ��
    TH0=0; 
    TL0=0;              //��ʱ�ж���������
 if((Tc>Imin)&&(Tc<Imax))
      { 
        m=0;
        f=1;
        return;
      }       //�ҵ���ʼ��

   if(f==1)
      {
        if(Tc>Inum1&&Tc<Inum3) 
    {
   Im[m/8]=Im[m/8]>>1|0x80; m++; 
       }
      if(Tc>Inum2&&Tc<Inum1) 
        {
         Im[m/8]=Im[m/8]>>1; m++; //ȡ��
  }
  if(m==32) 
   {
         m=0;  
         f=0;
         if(Im[2]==~Im[3]) 
      {
           IrOK=1; 
   }
        else IrOK=0;   //ȡ����ɺ��ж϶����Ƿ���ȷ
     }
               //׼������һ��
   }
 
}

#endif
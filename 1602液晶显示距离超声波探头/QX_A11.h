#ifndef _QX_A11_H
#define _QX_A11_H


#define MAIN_Fosc		11059200L	//������ʱ��
#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)

/*�������IO����*/
sbit Left_moto_pwm = P1^5; //Ϊ1 ����ʹ��
sbit IN1 = P1^4; //Ϊ1 ������ת
sbit IN2 = P1^3; //Ϊ1 ������ת
sbit IN3 = P1^2; //Ϊ1 �ҵ����ת
sbit IN4 = P1^1; //Ϊ1 �ҵ����ת
sbit Right_moto_pwm = P1^0; //Ϊ1 �ҵ��ʹ��
sbit TRIGL = P2 ^ 0;
sbit ECHOL = P2 ^ 1;
sbit TRIGB = P3 ^ 4;
sbit ECHOB = P3 ^ 5;
sbit TRIGR = P3 ^ 6;
sbit ECHOR = P3 ^ 7;
sbit SPK = P2 ^ 2;
/*��������*/
sbit beep = P2^2;//������

#endif
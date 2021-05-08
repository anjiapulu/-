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
//sbit TRIGL = P2 ^ 0;
//sbit ECHOL = P2 ^ 1;
//sbit TRIGB = P2 ^ 2;
//sbit ECHOB = P2 ^ 3;
//sbit TRIGR = P3 ^ 4;
//sbit ECHOR = P3 ^ 5;

/*��������*/

sbit KEY = P3^3;
//sbit beep = P2^2;//������
//sbit left_led1 = P3^5;//��Ѱ���ź� Ϊ0 û��ʶ�𵽺��� Ϊ1ʶ�𵽺���
//sbit right_led1 = P3^4;//��Ѱ���ź�	Ϊ0 û��ʶ�𵽺��� Ϊ1ʶ�𵽺���
//sbit left_led2 = P3^6;//������ź� Ϊ0 ʶ���ϰ��� Ϊ1û��ʶ���ϰ���
//sbit right_led2 = P3^7;//�ұ����ź�	Ϊ0 ʶ���ϰ��� Ϊ1û��ʶ���ϰ���
#define left_motor_en		EN1 = 1	//����ʹ��
#define right_motor_en		EN2 = 1	//�ҵ��ʹ��


#define left_motor_stops	IN1 = 0, IN2 = 0//����ֹͣ
#define right_motor_stops	IN3 = 0, IN4 = 0//�ҵ��ֹͣ

#define left_motor_go		IN1 = 1, IN2 = 0//��������
#define left_motor_back		IN1 = 0, IN2 = 1//������ת
#define right_motor_go		IN3 = 0, IN4 = 1//�ҵ������
#define right_motor_back	IN3 = 1, IN4 = 0//�ҵ����ת

#endif
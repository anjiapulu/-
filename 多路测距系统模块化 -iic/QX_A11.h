#ifndef _QX_A11_H
#define _QX_A11_H
#define MAIN_Fosc		11059200L	//定义主时钟
#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)
/*------------------------------------------------
            电机驱动IO定义
------------------------------------------------*/
sbit Left_moto_pwm = P1^7; //为1 左电机使能
sbit IN1 = P1^6; //为1 左电机正转
sbit IN2 = P1^5; //为1 左电机反转
sbit IN3 = P1^4; //为1 右电机反转
sbit IN4 = P1^3; //为1 右电机正转
sbit Right_moto_pwm = P1^2; //为1 右电机使能
/*------------------------------------------------
            超声波驱动IO定义
------------------------------------------------*/
sbit TRIGL = P2 ^ 0;
sbit ECHOL = P2 ^ 1;
sbit TRIGB = P3 ^ 4;
sbit ECHOB = P3 ^ 5;
sbit TRIGR = P3 ^ 6;
sbit ECHOR = P3 ^ 7;
sbit SPK = P2 ^ 2;

sbit SCL=P2^0;
sbit SDA=P2^1;
#endif
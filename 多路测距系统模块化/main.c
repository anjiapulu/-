#include <reg52.h>
#include "conf.h"
/*------------------------------------------------
				������
------------------------------------------------*/
void main()
{ 
	int leftnumber=0, backnumber=0, rightnumber=0;
	Timer0Init();/*pwm�������*/
	LCD_Init();  /*1602��ʼ��*/
	TIM1init();  /*����������ʱ��1��ʼ��*/
	while (1)
	{
		keydous();
		hcsr04();
	}
}
#include <reg52.h>
//#include "iic1602.h"
#include "1602.h"
#include "keydous.h"
#include "hcsr04.h"
#include <QX_A11.h>
#include "pwm.h"

/*------------------------------------------------
				������
------------------------------------------------*/
void main()
{ int leftnumber=0, backnumber=0, rightnumbe=0;
	Timer0Init();/*pwm�������*/
	LCD_Init();  /*1602��ʼ��*/
	TIM1init();  /*����������ʱ��1��ʼ��*/
	while (1)
	{
//		keydous();
		hcsr04();
	}
}
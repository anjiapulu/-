#include <reg52.h>
#include "1602.h"
#include "keydous.h"
#include "hcsr04.h"
#include <QX_A11.h>
#include "at24c02.h"
#include "pwm.h"
/*------------------------------------------------
				������
------------------------------------------------*/
void main()
{
	LCD_Init();  /*1602��ʼ��*/
	TIM1init();  /*��������ʱ����ʼ��*/
	Timer0Init();
	while (1)
	{
		keydous();
		hcsr04();
		pwm();
	}
}
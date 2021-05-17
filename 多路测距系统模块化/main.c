#include <reg52.h>
#include "1602.h"
#include "keydous.h"
#include "hcsr04.h"
#include <QX_A11.h>
#include "at24c02.h"
#include "pwm.h"
/*------------------------------------------------
				主函数
------------------------------------------------*/
void main()
{
	LCD_Init();  /*1602初始化*/
	TIM1init();  /*超声波定时器初始化*/
	Timer0Init();
	while (1)
	{
		keydous();
		hcsr04();
		pwm();
	}
}
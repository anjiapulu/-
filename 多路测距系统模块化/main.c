#include <reg52.h>
#include "conf.h"
/*------------------------------------------------
				主函数
------------------------------------------------*/
void main()
{

	Timer0Init(); /*pwm定时器初始化*/

	LCD_Init(); /*1602初始化*/

	TIM1init(); /*HC-SR04定时器初始化*/

	while (1)
	{
		keydous();

		hcsr04();
	}
}
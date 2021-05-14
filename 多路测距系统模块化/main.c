#include <reg52.h>
#include "1602.h"
#include "keydous.h"
#include "hcsr04.h"
#include <QX_A11.h>
/*------------------------------------------------
				Ö÷º¯Êý
------------------------------------------------*/
main()
{
	LCD_Init();
	TIM1init();
	while (1)
	{
		keydous();
		hcsr04();
	}
}
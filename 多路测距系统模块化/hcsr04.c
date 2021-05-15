#include <stdio.h>
#include <reg52.h>
#include <QX_A11.h>
//#include <math.h>
#include "delay.h"
#include "1602.h"
int leftnumber, backnumber, rightnumber,i,j;
void Timer0_isr(void) interrupt 2
{
	ECHOL = 0;
	ECHOB = 0;
	ECHOR = 0;
}
void TIM1init(void)
{

	TMOD |= 0x10;
	TH1 = 0x00;
	TL1 = 0x00;
	ET1 = 1;
}

void hcsr04()
{ float S, arr[5], temp;
	unsigned char DisTempData[7];

	/*------------------------------------------------
					右方
	------------------------------------------------*/
	if (1)
	{
		/*one*/
		TRIGR = 1;
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);
		TR1 = 1;
		while (ECHOR);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;
		arr[0] = S;
		TH1 = 0;
		TL1 = 0;
		/*two*/
		TRIGR = 1;
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);
		TR1 = 1;
		while (ECHOR);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;
		arr[1] = S;
		TH1 = 0;
		TL1 = 0;
		/*third*/
		TRIGR = 1;
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);
		TR1 = 1;
		while (ECHOR);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;
		arr[2] = S;
		TH1 = 0;
		TL1 = 0;
		/*four*/
		TRIGR = 1;
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);
		TR1 = 1;
		while (ECHOR);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;
		arr[3] = S;
		TH1 = 0;
		TL1 = 0;
		/*five*/
		TRIGR = 1;
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);
		TR1 = 1;
		while (ECHOR);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;
		arr[4] = S;
		TH1 = 0;
		TL1 = 0;
		/*try*/
		for (i = 0; i < 5 - 1; i++)
			for (j = 0; j < 5 - 1 - i; j++)
				if (arr[j] > arr[j + 1])
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
		/*try*/
		S = ((arr[1] + arr[2] + arr[3]) / 3);
		if (S < rightnumber)
		{

			SPK = 0;//防止一直给喇叭通电造成损坏
			DelayMs(250);

		}
		SPK = 1;
		sprintf(DisTempData, "R=%6.2f", S);
		LCD_Write_String(0, 1, DisTempData);

	}
	/*------------------------------------------------
				左方
	------------------------------------------------*/
	if (1)
	{
		/*one*/
		TRIGL = 1;
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL);
		TR1 = 1;
		while (ECHOL);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[0] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;
		/*two*/
		TRIGL = 1;
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL);
		TR1 = 1;
		while (ECHOL);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[1] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;
		/*third*/
		TRIGL = 1;
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL);
		TR1 = 1;
		while (ECHOL);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;
		arr[2] = S;
		TH1 = 0;
		TL1 = 0;
		/*four*/
		TRIGL = 1;
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL);
		TR1 = 1;
		while (ECHOL);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;
		arr[3] = S;
		TH1 = 0;
		TL1 = 0;
		/*five*/
		TRIGL = 1;
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL);
		TR1 = 1;
		while (ECHOL);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;
		arr[4] = S;
		TH1 = 0;
		TL1 = 0;

		/*try*/
		for (i = 0; i < 5 - 1; i++)
			for (j = 0; j < 5 - 1 - i; j++)
				if (arr[j] > arr[j + 1])
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
		/*try*/
		S = ((arr[1] + arr[2] + arr[3]) / 3);
		if (S < leftnumber)
		{

			SPK = 0;//防止一直给喇叭通电造成损坏
			DelayMs(250);

		}
		SPK = 1;
		sprintf(DisTempData, "L=%6.2f", S);
		LCD_Write_String(8, 1, DisTempData);

	}
	/*------------------------------------------------
				  后方
	------------------------------------------------*/
	if (1)
	{
		TRIGB = 1;
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);
		TR1 = 1;
		while (ECHOB);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[0] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;
		/*two*/
		TRIGB = 1;
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);
		TR1 = 1;
		while (ECHOB);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[1] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;
		/*third*/
		TRIGB = 1;
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);
		TR1 = 1;
		while (ECHOB);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[2] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;
		/*four*/
		TRIGB = 1;
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);
		TR1 = 1;
		while (ECHOB);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[3] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;
		/*five*/
		TRIGB = 1;
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);
		TR1 = 1;
		while (ECHOB);
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[4] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;
		/*try*/
		for (i = 0; i < 5 - 1; i++)
			for (j = 0; j < 5 - 1 - i; j++)
				if (arr[j] > arr[j + 1])
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
		/*try*/
		S = ((arr[1] + arr[2] + arr[3]) / 3);
		if (S < backnumber)
		{

			SPK = 0;//防止一直给喇叭通电造成损坏
			DelayMs(250);

		}
		SPK = 1;
		sprintf(DisTempData, "B=%6.2f", S);
		LCD_Write_String(4, 0, DisTempData);
	}
}

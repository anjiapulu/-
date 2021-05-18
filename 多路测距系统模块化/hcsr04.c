#include <stdio.h>
#include <reg52.h>
#include <QX_A11.h>
#include <math.h>
#include "delay.h"
#include "1602.h"
#include "pwm.h"
int i,j;
extern int leftnumber, backnumber, rightnumber ;
extern float S1,S2,S3;
unsigned char DisTempData[7];
float  arr[5], temp;
void Timer1_isr(void) interrupt 2
{
	ECHOL = 0;
	ECHOB = 0;
	ECHOR = 0;
}
void TIM1init(void)
{
	TMOD |= 0x10;
	TH1=0;
	TL1=0;
	ET1 = 1;
}
void rightdis()
{
/*one*/
		TRIGR = 1;
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);
		TR1 = 1;
		while (ECHOR);
		TR1 = 0;
		S1 = TH1 * 256 + TL1;
		S1 = S1 / 58;
		arr[0] = S1;
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
		S1 = TH1 * 256 + TL1;
		S1 = S1 / 58;
		arr[1] = S1;
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
		S1 = TH1 * 256 + TL1;
		S1 = S1 / 58;
		arr[2] = S1;
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
		S1 = TH1 * 256 + TL1;
		S1 = S1 / 58;
		arr[3] = S1;
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
		S1 = TH1 * 256 + TL1;
		S1 = S1 / 58;
		arr[4] = S1;
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
		S1 = ((arr[1] + arr[2] + arr[3]) / 3)*1.089;
		if (S1 < rightnumber)
		{
			
			SPK = 0;//防止一直给喇叭通电造成损坏
			DelayMs(200);
		}
		SPK = 1;
		if(S1<500)
		{
		sprintf(DisTempData, "R=%6.2f", S1);
		LCD_Write_String(0, 1, DisTempData);
		}
		else 
		{
			LCD_Write_String(2, 1, "eerror");
		}
		DelayMs(300);
	
}
void leftdis()
{
/*one*/
		TRIGL = 1;
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL);
		TR1 = 1;
		while (ECHOL);
		TR1 = 0;
		S2 = TH1 * 256 + TL1;
		S2 = S2 /58 ;       //     58    ,  Y =(X *344)/2
		arr[0] = S2;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
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
		S2 = TH1 * 256 + TL1;
		S2 = S2 / 58;       //     58    ,  Y =(X *344)/2
		arr[1] = S2;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
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
		S2 = TH1 * 256 + TL1;
		S2 = S2 / 58;
		arr[2] = S2;
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
		S2 = TH1 * 256 + TL1;
		S2 = S2 / 58;
		arr[3] = S2;
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
		S2 = TH1 * 256 + TL1;
		S2 = S2 / 58;
		arr[4] = S2;
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
		S2 = ((arr[1] + arr[2] + arr[3]) / 3)*1.089;
		if (S2 < leftnumber)
		{
      
			SPK = 0;//防止一直给喇叭通电造成损坏
			DelayMs(200);

		}
		SPK = 1;
	  if(S2<500)
		{
		sprintf(DisTempData, "L=%6.2f", S2);
		LCD_Write_String(8, 1, DisTempData);
		}
    else {LCD_Write_String(10, 1, "eerror");}
		DelayMs(300);

}

void backdis()
{  
	/*one*/
    TRIGB = 1;
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);
		TR1 = 1;
		while (ECHOB);
		TR1 = 0;
		S3 = TH1 * 256 + TL1;
		S3 = S3 / 58;       //     58    ,  Y =(X *344)/2
		arr[0] = S3;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
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
		S3 = TH1 * 256 + TL1;
		S3 = S3 / 58;       //     58    ,  Y =(X *344)/2
		arr[1] = S3;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
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
		S3 = TH1 * 256 + TL1;
		S3 = S3 / 58;       //     58    ,  Y =(X *344)/2
		arr[2] = S3;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
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
		S3 = TH1 * 256 + TL1;
		S3 = S3 / 58;       //     58    ,  Y =(X *344)/2
		arr[3] = S3;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
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
		S3 = TH1 * 256 + TL1;
		S3 = S3 / 58;       //     58    ,  Y =(X *344)/2
		arr[4] = S3;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
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
		S3 = ((arr[1] + arr[2] + arr[3]) / 3)*1.089;
		if (S3 < backnumber)
		{
			
			SPK = 0;//防止一直给喇叭通电造成损坏
			DelayMs(200);
			
		}
		SPK = 1;
		if(S3<500)
		{
		sprintf(DisTempData, "B=%6.2f", S3);
		LCD_Write_String(4, 0, DisTempData);
		}
    else {LCD_Write_String(6, 0, "eerror");}
		DelayMs(300);
}
void hcsr04()
{ 
	
	/*------------------------------------------------
					右方
	------------------------------------------------*/
	rightdis();
	rpwm();
	/*------------------------------------------------
				左方
	------------------------------------------------*/
  leftdis();
	lpwm();
	/*------------------------------------------------
				  后方
	------------------------------------------------*/
  backdis();
	bpwm();
}

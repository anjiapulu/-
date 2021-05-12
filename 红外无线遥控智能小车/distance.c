#include <reg52.h>
#include <stdio.h>
#include <math.h>
#include "1602.h"
#include "delay.h"
#include "string.h"
#include "MatrixKey.h"
sbit TRIGL = P2 ^ 0;
sbit ECHOL = P2 ^ 1;
sbit TRIGB = P3 ^ 4;
sbit ECHOB = P3 ^ 5;
sbit TRIGR = P3 ^ 6;
sbit ECHOR = P3 ^ 7;
sbit SPK = P2 ^ 2;

/*------------------------------------------------
				   ��ʱ��
------------------------------------------------*/
void TIM1init(void)
{

	TMOD |= 0x10;
	TH1 = 0x00;
	TL1 = 0x00;
	ET1 = 1;
	EA = 1;

}
/*------------------------------------------------
				������
------------------------------------------------*/
distancet(void);
{

	TIM1init();
	LCD_Init();
	while (1)
	{

		/*����������ֵ����*/
		while (k <= 3)
		{
			if (k == 0)
			{
					LCD_Write_String(0, 1, " L___ B___ R___ ");
			}
			LCD_Write_String(0, 0, "   input dist   ");
			KeyNum = MatrixKey();
			if (KeyNum == 13)
			{
				k++;
				if (k == 1)
				{
					for (i = 2; i < 5;)
					{
						KeyNum = MatrixKey();
						if(i==2)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            leftnumber+=(KeyNum*100);
						}
						}
            if(i==3)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            leftnumber+=(KeyNum*10);
						}
						}
						if(i==4)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            leftnumber+=(KeyNum);
						}
						}
						if (KeyNum < 10)
						{
							
							LCD_Write_Char(i, 1, studentid[KeyNum]);
							i++;
						}
						DelayMs(50);
				
					}
				}
				if (k == 2)
				{
					for (i = 7; i < 10; )
					{
						KeyNum = MatrixKey();
						if(i==7)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            backnumber+=(KeyNum*100);
						}
						}
            if(i==8)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            backnumber+=(KeyNum*10);
						}
						}
						if(i==9)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            backnumber+=(KeyNum);
						}
						}
						if (KeyNum < 10)
						{
							LCD_Write_Char(i, 1, studentid[KeyNum]);
							i++;
						}
						DelayMs(50);
					}
				}
				if (k == 3)
				{
          k=4;
					for (i = 12; i < 15; )
					{
						KeyNum = MatrixKey();
	          if(i==12)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            rightnumber+=(KeyNum*100);
						}
						}
            if(i==13)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            rightnumber+=(KeyNum*10);
						}
						}
						if(i==14)
						{
						if(KeyNum>0&&KeyNum<10)
						{
            rightnumber+=(KeyNum);
						}
						}
						if (KeyNum < 10)
						{
							LCD_Write_Char(i, 1, studentid[KeyNum]);
							i++;
						}
					 	DelayMs(50);
					}

				  LCD_Write_String(0, 0, "                ");
				}
			}
		}
	
		
		/*------------------------------------------------
						�ҷ�
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
			S = ((arr[1] + arr[2] + arr[3] + arr[4] / 4);
			temp=rightnumber;
			if (S < temp)
			{

			SPK = 0;//��ֹһֱ������ͨ�������
			DelayMs(250);

			}
		  SPK = 1;
			sprintf(DisTempData, "R=%6.2f",S);
			LCD_Write_String(0, 1, DisTempData);
		}
		/*------------------------------------------------
					��
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
			for (i = 0; i < 10 - 1; i++)
				for (j = 0; j < 10 - 1 - i; j++)
					if (arr[j] > arr[j + 1])
					{
						temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
					}
			/*try*/
			S = ((arr[1] + arr[2] + arr[3] + arr[4] ) / 4);
			temp=leftnumber;
			if (S < temp)
			{
				
			SPK = 0;//��ֹһֱ������ͨ�������
			DelayMs(250);
				
			}
		  SPK = 1;
			sprintf(DisTempData,"L=%6.2f", S);
			LCD_Write_String(8, 1, DisTempData);
		}
		/*------------------------------------------------
					  ��
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
			for (i = 0; i < 10 - 1; i++)
				for (j = 0; j < 10 - 1 - i; j++)
					if (arr[j] > arr[j + 1])
					{
						temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
					}
			/*try*/
			S = (arr[1] + arr[2] + arr[3] + arr[4]  /4);
			temp=backnumber;
			if (S < temp)
			{
				
			SPK = 0;//��ֹһֱ������ͨ�������
			DelayMs(250);
				
			}
		  SPK = 1;
			sprintf(DisTempData, "B=%6.2f", S);
			LCD_Write_String(4, 0, DisTempData);

		}
	}
}

/*------------------------------------------------
				 �ж�
------------------------------------------------*/
void Timer0_isr(void) interrupt 2
{
	ECHOL = 0;
	ECHOB = 0;
	ECHOR = 0;
}
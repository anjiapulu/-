#include "reg51.h"
#include "string.h"
#include "delay.h"
#include "iic1602.h"
#include "MatrixKey.h"
#include "at24c02.h"
unsigned char code redistance[] = " L___ F___ R___ ";
unsigned char code safe[] = "    safe now    ";
unsigned char code danger[] = "   danger now   ";
unsigned char code setting[] = "   input dist   ";
unsigned char code number[] = "0123456789";
char setdistance[] = " L___ F___ R___ ", KeyNum = 10;
int leftnumber, lbaiwei, lshiwei, lgewei,
frontnumber, fbaiwei, fshiwei, fgewei,
rightnumber, rbaiwei, rshiwei, rgewei,
i, j, k, l;
int main()
{
	k = 0;
	lcd_init();
	dispaly_character(0, 0, setting);
	dispaly_character(0, 1, redistance);
	while (1)
	{
		KeyNum = MatrixKey();
		/*save*/
		if (KeyNum == 11)
		{
			ISendStr(0xA0, 0, setdistance, 16);
			j = k;
		}
		/*load*/
		if (KeyNum == 12)
		{
			IRcvStr(0xA0, 0, setdistance, 16);
			dispaly_character(0, 1, setdistance);
			k = j;
		}
		/*set distance*/
		if (KeyNum == 13)
		{
			k++;
			if (k == 1)
			{ 
				for(i=0;i<15;i++)
				{
				setdistance[i] =redistance[i];
				}
				for (i = 2; i < 5;)
				{
					KeyNum = MatrixKey();
					if (KeyNum < 10)
					{
						setdistance[i] = number[KeyNum];
						dispaly_character(0, 1, setdistance);
						if (i == 2)
						{
							lbaiwei = MatrixKey() * 100;
						}
						if (i == 3)
						{
							lshiwei = MatrixKey() * 10;
						}
						if (i == 4)
						{
							lgewei = MatrixKey();
						}
						leftnumber = lbaiwei + lshiwei + lgewei;
						i++;
					}
				}
			}

			if (k == 2)
			{
				for (i = 7; i < 10;)
				{
					KeyNum = MatrixKey();
					if (KeyNum < 10)
					{

						setdistance[i] = number[KeyNum];
						dispaly_character(0, 1, setdistance);
						if (i == 7)
						{
							fbaiwei = MatrixKey() * 100;
						}
						if (i == 8)
						{
							fshiwei = MatrixKey() * 10;
						}
						if (i == 9)
						{
							fgewei = MatrixKey();
						}
						frontnumber = fbaiwei + fshiwei + fgewei;
						i++;
					}
				}
			}

			if (k == 3)
			{
				for (i = 12; i < 15;)
				{
					KeyNum = MatrixKey();
					if (KeyNum < 10)
					{
						setdistance[i] = number[KeyNum];
						dispaly_character(0, 1, setdistance);
						if (i == 12)
						{
							rbaiwei = MatrixKey() * 100;
						}
						if (i ==13)
						{
							rshiwei = MatrixKey() * 10;
						}
						if (i == 14)
						{
							rgewei = MatrixKey();
						}
						rightnumber = rbaiwei + rshiwei + rgewei;
						i++;
					}
				}
				k = 0;
			}




		}

	}
	return 0;
}
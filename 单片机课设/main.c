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
char left[] = "___", front[] = "___", right[] = "___", KeyNum = 10;
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
			ISendStr(0xA0, 0, left, 3);

		}
		/*load*/
		if (KeyNum == 12) 
		{
			IRcvStr(0xA0, 0, left, 3);
			k = 0;
		}
		/*set distance*/
		if (KeyNum == 13) 
		{
			k++;
			if (k == 1)
			{
				char left[] = "___";
				dispaly_character(2, 1, left);
				for (i = 0; i < 3;)
				{
					KeyNum = MatrixKey();
					if (KeyNum < 10)
					{
						if (i == 0)
						{
							lbaiwei = MatrixKey() * 100;
						}
						if (i == 1)
						{
							lshiwei = MatrixKey() * 10;
						}
						if (i == 2)
						{
							lgewei = MatrixKey();
						}
						leftnumber = lbaiwei + lshiwei + lgewei;
						left[i] = number[KeyNum];
						dispaly_character(2, 1, left);
						i++;
					}
				}
			}

			if (k == 2)
			{
				char front[] = "___";
				dispaly_character(7, 1, front);
				for (i = 0; i < 3;)
				{
					KeyNum = MatrixKey();
					if (KeyNum < 10)
					{
						if (i == 0)
						{
							fbaiwei = MatrixKey() * 100;
						}
						if (i == 1)
						{
							fshiwei = MatrixKey() * 10;
						}
						if (i == 2)
						{
							fgewei = MatrixKey();
						}
						frontnumber = fbaiwei + fshiwei + fgewei;
						front[i] = number[KeyNum];
						dispaly_character(7, 1, front);
						i++;
					}
				}
			}

			if (k == 3)
			{
				char	right[] = "___";
				dispaly_character(12, 1, right);
				for (i = 0; i < 3;)
				{
					KeyNum = MatrixKey();
					if (KeyNum < 10)
					{
						if (i == 0)
						{
							rbaiwei = MatrixKey() * 100;
						}
						if (i == 1)
						{
							rshiwei = MatrixKey() * 10;
						}
						if (i == 2)
						{
							rgewei = MatrixKey();
						}
						rightnumber = rbaiwei + rshiwei + rgewei;
						right[i] = number[KeyNum];
						dispaly_character(12, 1, right);
						i++;
					}
				}
				k = 0;
			}




		}
	
	}
	return 0;
}
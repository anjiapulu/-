#include <reg52.h>
//#include "iic1602.h"
#include "1602.h"
#include "delay.h"
#include "string.h"
#include "MatrixKey.h"

int leftnumber, backnumber, rightnumber;
unsigned char code studentid[] = "0123456789";
int KeyNum;
extern int i, j, k = 0;
void  keydous()
{
#if 0
	/*------------------------------------------------
			at24c02¥Ê»°
	------------------------------------------------*/

	if (KeyNum == 11)
	{
		ISendStr(0xA0, 0, leftnumber, 4);
		ISendStr(0xA0, 4, backnumber, 4);
		ISendStr(0xA0, 8, rightnumber, 4);
	}
	if (KeyNum == 12)
	{
		IRcvStr(0xA0, 0, leftnumber, 4);
		IRcvStr(0xA0, 4, backnumber, 4);
		IRcvStr(0xA0, 8, rightnumber, 4);
		k = 4;
	}
#endif
	/*------------------------------------------------
			∑‰√˘∆˜æØΩ‰÷µ ‰»Î
	------------------------------------------------*/
	while (k < 3)
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
			switch (k)
			{
			case 1:
				for (i = 2; i < 5;)
				{
					KeyNum = MatrixKey();
					switch (i)
					{
					case 2:if (KeyNum > 0 && KeyNum < 10)leftnumber += (KeyNum * 100); break;
					case 3: if (KeyNum > 0 && KeyNum < 10)leftnumber += (KeyNum * 10); break;
					case 4: if (KeyNum >= 0 && KeyNum < 10)leftnumber += (KeyNum); break;
					}

					if (KeyNum < 10)
					{
						LCD_Write_Char(i, 1, studentid[KeyNum]);
						i++;
					}
					DelayMs(50);
				}
				break;

			case 2:
				for (i = 7; i < 10; )
				{
					KeyNum = MatrixKey();
					switch (i)
					{
					case 7: if (KeyNum > 0 && KeyNum < 10)backnumber += (KeyNum * 100); break;
					case 8: if (KeyNum > 0 && KeyNum < 10)backnumber += (KeyNum * 10); break;
					case 9: if (KeyNum >= 0 && KeyNum < 10)backnumber += (KeyNum); break;
					}
					if (KeyNum < 10)
					{
						LCD_Write_Char(i, 1, studentid[KeyNum]);
						i++;
					}
					DelayMs(50);
				}
				break;
			case 3:
				k = 4;
				for (i = 12; i < 15; )
				{
					KeyNum = MatrixKey();
					switch (i)
					{
					case 12: if (KeyNum > 0 && KeyNum < 10)rightnumber += (KeyNum * 100); break;
					case 13: if (KeyNum > 0 && KeyNum < 10)rightnumber += (KeyNum * 10); break;
					case 14: if (KeyNum >= 0 && KeyNum < 10)rightnumber += (KeyNum); break;
					}

					if (KeyNum < 10)
					{
						LCD_Write_Char(i, 1, studentid[KeyNum]);
						i++;
					}
					DelayMs(50);
				}
				LCD_Write_String(0, 0, "                ");

				break;

			}
		}

	}

}
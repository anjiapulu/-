#include <reg52.h>
#include <stdio.h>
#include <math.h>
#include "1602.h"
#include "delay.h"
#include "string.h"
#include "MatrixKey.h"

sbit TRIGL = P2 ^ 0;
sbit ECHOL = P2 ^ 1;
sbit TRIGB = P2 ^ 2;
sbit ECHOB = P2 ^ 3;
sbit TRIGR = P3 ^ 6;
sbit ECHOR = P3 ^ 7;
//unsigned char code setdistance[] = " L___ F___ R___ ", KeyNum = 10;
//unsigned char code number[] = "0123456789";
unsigned char DisTempData[7];
float S,arr[9], temp;
/*------------------------------------------------
				   0   
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
				主函数
------------------------------------------------*/
main()
{
TIM1init();    
LCD_Init();    
while (1)
{
	
	int i, j;
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
			/*SIX*/
		TRIGR = 1;      
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);     
		TR1 = 1;
		while (ECHOR);     
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[5] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;           
		/*SEVEN*/
		TRIGR = 1;       
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);  
		TR1 = 1;
		while (ECHOR);  
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[6] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;          
		/*EIGHT*/
		TRIGR = 1;       
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);      
		TR1 = 1;
		while (ECHOR);       
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[7] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;           
		/*NINE*/
		TRIGR = 1;       
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);      
		TR1 = 1;
		while (ECHOR);     
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[8] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;          
		/*TEN*/
				TRIGR = 1;       
		DelayUs2x(10);
		TRIGR = 0;
		while (!ECHOR);      
		TR1 = 1;
		while (ECHOR);    
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[9] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
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
		S = ((arr[2] + arr[3] + arr[4]+arr[5]+arr[6]+arr[7]) / 6)+0.50;
		sprintf(DisTempData, "R=%6.2f", S);  
		LCD_Write_String(0, 1, DisTempData);       
		DelayMs(500);
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
		/*SIX*/
		TRIGL = 1;       
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL);     
		TR1 = 1;
		while (ECHOL);       
		TR1 = 0;
		S = TH1 * 256 + TL1; 
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[5] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;             
		/*SEVEN*/
		TRIGL = 1;       
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL); 
		TR1 = 1;
		while (ECHOL);  
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;      
		arr[6] = S;	     
		TH1 = 0;
		TL1 = 0;        
		/*EIGHT*/
		TRIGL = 1;       
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL);
		TR1 = 1;
		while (ECHOL);  
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;      
		arr[7] = S;	     
		TH1 = 0;
		TL1 = 0;       
		/*NINE*/
		TRIGL = 1;       
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL);
		TR1 = 1;
		while (ECHOL);  
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;      
		arr[8] = S;	     
		TH1 = 0;
		TL1 = 0;      
		/*TEN*/
				TRIGL = 1;       
		DelayUs2x(10);
		TRIGL = 0;
		while (!ECHOL); 
		TR1 = 1;
		while (ECHOL);  
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;     
		arr[9] = S;	     
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
		S = ((arr[2] + arr[3] + arr[4]+arr[5]+arr[6]+arr[7]) / 6)+0.20;
		sprintf(DisTempData, "L=%6.2f", S);
		LCD_Write_String(4, 0, DisTempData);    
		DelayMs(1000);
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
				/*SIX*/
		TRIGB = 1;      
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);    
		TR1 = 1;
		while (ECHOB);    
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[5] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;           
		/*SEVEN*/
		TRIGB = 1;       
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);      
		TR1 = 1;
		while (ECHOB);       
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[6] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;          
		/*EIGHT*/
		TRIGB = 1;       
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);  
		TR1 = 1;
		while (ECHOB);     
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[7] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;           
		/*NINE*/
		TRIGB = 1;      
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);     
		TR1 = 1;
		while (ECHOB);     
		TR1 = 0;
		S = TH1 * 256 + TL1; 
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[8] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
		TH1 = 0;
		TL1 = 0;         
		/*TEN*/
		TRIGB = 1;       
		DelayUs2x(10);
		TRIGB = 0;
		while (!ECHOB);      
		TR1 = 1;
		while (ECHOB);    
		TR1 = 0;
		S = TH1 * 256 + TL1;
		S = S / 58;       //     58    ,  Y =(X *344)/2
		arr[9] = S;	     // X =( 2*Y )/344 -> X =0.0058*Y  ->   =  /58 
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
		S = ((arr[2] + arr[3] + arr[4]+arr[5]+arr[6]+arr[7]) / 6)+0.30 ;
		sprintf(DisTempData, "B=%6.2f", S);
		LCD_Write_String(8, 1, DisTempData);

	}
 }

}
/*------------------------------------------------
			     中断
------------------------------------------------*/
void Timer0_isr(void) interrupt 2
{
ECHOL = 0;
ECHOB = 0;
ECHOR = 0;
}
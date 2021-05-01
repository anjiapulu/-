#include <REGX52.H>
unsigned char MatrixKey()
{ 
	unsigned char KeyNumber=10;
	while(1)
	{
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){while(P1_7==0);return 1;}
	if(P1_6==0){while(P1_6==0);return 4;}
	if(P1_5==0){while(P1_5==0);return 7;}
	if(P1_4==0){while(P1_4==0);return 11;} /*save*/
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){while(P1_7==0);return 2;}
	if(P1_6==0){while(P1_6==0);return 5;}
	if(P1_5==0){while(P1_5==0);return 8;}
	if(P1_4==0){while(P1_4==0);return 0;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){while(P1_7==0);return 3; }
	if(P1_6==0){while(P1_6==0);return 6; }
	if(P1_5==0){while(P1_5==0);return 9; }
	if(P1_4==0){while(P1_4==0);return 12;}/*load*/
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){while(P1_7==0);return 13;} //left
  if(P1_6==0){while(P1_6==0);return 14;} //front
	if(P1_5==0){while(P1_5==0);return 15;} //right
	P1=0xFF;
	return KeyNumber;
}
}

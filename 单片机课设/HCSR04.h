#ifndef __HCSR04_H__
#define __HCSR04_H__
 unsigned char DisTempData[16];
 float S;
 sbit TRIGL = P1^0 ;
 sbit ECHOL = P1^1 ;
 sbit TRIGF = P1^2 ;
 sbit ECHOF = P1^3 ;
 sbit TRIGR = P1^4 ;
 sbit ECHOR = P1^5 ;
void TIM0init();
void Timer0_isr();
#endif
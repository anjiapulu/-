#include <reg52.h>          //??????
#include <intrins.h>
#include "delay.h"
#define  _Nop()  _nop_()       


                                              
sbit SDA=P3^2;            //??I2C?????
sbit SCL=P3^3;            //??I2C?????

                          
bit ack;	              //?????
   



/*------------------------------------------------
                    ????
------------------------------------------------*/
void Start_I2c()
{
  SDA=1;   //???????????
  _Nop();
  SCL=1;
  _Nop();    //??????????4.7us,??
  _Nop();
  _Nop();
  _Nop();
  _Nop();    
  SDA=0;     //??????
  _Nop();    //??????????4?
  _Nop();
  _Nop();
  _Nop();
  _Nop();       
  SCL=0;    //??I2C??,?????????
  _Nop();
  _Nop();
}
/*------------------------------------------------
                    ????
------------------------------------------------*/
void Stop_I2c()
{
  SDA=0;    //???????????
  _Nop();   //???????????
  SCL=1;    //??????????4?
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  SDA=1;    //??I2C??????
  _Nop();
  _Nop();
  _Nop();
  _Nop();
}





void  SendByte(unsigned char c)
{
 unsigned char BitCnt;
 
 for(BitCnt=0;BitCnt<8;BitCnt++)  //?????????8?
    {
     if((c<<BitCnt)&0x80)SDA=1;   //?????
       else  SDA=0;                
     _Nop();
     SCL=1;               //??????,????????????
      _Nop(); 
      _Nop();             //???????????4?
      _Nop();
      _Nop();
      _Nop();         
     SCL=0; 
    }
    
    _Nop();
    _Nop();
    SDA=1;               //8??????????,???????
    _Nop();
    _Nop();   
    SCL=1;
    _Nop();
    _Nop();
    _Nop();
    if(SDA==1)ack=0;     
       else ack=1;        //???????????
    SCL=0;
    _Nop();
    _Nop();
}








unsigned char  RcvByte()
{
  unsigned char retc;
  unsigned char BitCnt;
  
  retc=0; 
  SDA=1;             //?????????
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        SCL=0;       //??????,???????
        _Nop();
        _Nop();      //?????????4.7us
        _Nop();
        _Nop();
        _Nop();
        SCL=1;       //???????????????
        _Nop();
        _Nop();
        retc=retc<<1;
        if(SDA==1)retc=retc+1; //????,????????retc?
        _Nop();
        _Nop(); 
      }
  SCL=0;    
  _Nop();
  _Nop();
  return(retc);
}



void Ack_I2c(void)
{
  
  SDA=0;     
  _Nop();
  _Nop();
  _Nop();      
  SCL=1;
  _Nop();
  _Nop();              //?????????4?
  _Nop();
  _Nop();
  _Nop();  
  SCL=0;               //????,??I2C????????
  _Nop();
  _Nop();    
}

void NoAck_I2c(void)
{
  
  SDA=1;
  _Nop();
  _Nop();
  _Nop();      
  SCL=1;
  _Nop();
  _Nop();              //?????????4?
  _Nop();
  _Nop();
  _Nop();  
  SCL=0;                //????,??I2C????????
  _Nop();
  _Nop();    
}







bit ISendStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no)
{
   unsigned char i;

   Start_I2c();               //????
   SendByte(sla);             //??????
     if(ack==0)return(0);
   SendByte(suba);            //???????
     if(ack==0)return(0);

   for(i=0;i<no;i++)
    {   
     SendByte(*s);            //????
       if(ack==0)return(0);
     s++;
    } 
 Stop_I2c();                  //????
  return(1);
}


bit IRcvStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no)
{
   unsigned char i;

   Start_I2c();               //????
   SendByte(sla);             //??????
     if(ack==0)return(0);
   SendByte(suba);            //???????
     if(ack==0)return(0);

   Start_I2c();
   SendByte(sla+1);
      if(ack==0)return(0);

   for(i=0;i<no-1;i++)
    {   
     *s=RcvByte();              //????
      Ack_I2c();                //????? 
     s++;
    } 
   *s=RcvByte();
    NoAck_I2c();                 //?????
   Stop_I2c();                    //????
  return(1);
}
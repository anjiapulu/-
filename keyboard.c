
#include<reg52.h> 
#include"keyboard.h"
#include"delay.h"

#define KeyPort P3

/*------------------------------------------------
按键扫描函数，返回扫描键值
------------------------------------------------*/
unsigned char KeyScan(void)  //键盘扫描函数，使用行列反转扫描法
{
 unsigned char cord_h,cord_l;//行列值中间变量
 KeyPort=0x0f;            //行线输出全为0
 cord_h=KeyPort&0x0f;     //读入列线值
 if(cord_h!=0x0f)    //先检测有无按键按下
 {
  DelayMs(10);        //去抖
  if((KeyPort&0x0f)!=0x0f)
  {
    cord_h=KeyPort&0x0f;  //读入列线值
    KeyPort=cord_h|0xf0;  //输出当前列线值
    cord_l=KeyPort&0xf0;  //读入行线值

    while((KeyPort&0xf0)!=0xf0);//等待松开并输出

    return(cord_h+cord_l);//键盘最后组合码值
   }
  }return(10);     //返回该值
}

unsigned char KeyPro(void)
{
 switch(KeyScan())
 {
  case 0x7e:return 1;break;// 按下相应的键显示相对应的码值
  case 0x7d:return 4;break;//
  case 0x7b:return 7;break;//
  case 0x77:return 0;break;//

  case 0xbe:return 2;break;
  case 0xbd:return 5;break;
  case 0xbb:return 8;break;
  case 0xb7:return 11;break;

  case 0xde:return 3;break;
  case 0xdd:return 6;break;
  case 0xdb:return 9;break;
  case 0xd7:return 12;break;
  //case 0xee:return '0';break;
  //case 0xed:return '.';break;
  //case 0xeb:return '=';break;
  //case 0xe7:return '/';break;
  default:return 10;
	
 }
}
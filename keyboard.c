
#include<reg52.h> 
#include"keyboard.h"
#include"delay.h"

#define KeyPort P3

/*------------------------------------------------
����ɨ�躯��������ɨ���ֵ
------------------------------------------------*/
unsigned char KeyScan(void)  //����ɨ�躯����ʹ�����з�תɨ�跨
{
 unsigned char cord_h,cord_l;//����ֵ�м����
 KeyPort=0x0f;            //�������ȫΪ0
 cord_h=KeyPort&0x0f;     //��������ֵ
 if(cord_h!=0x0f)    //�ȼ�����ް�������
 {
  DelayMs(10);        //ȥ��
  if((KeyPort&0x0f)!=0x0f)
  {
    cord_h=KeyPort&0x0f;  //��������ֵ
    KeyPort=cord_h|0xf0;  //�����ǰ����ֵ
    cord_l=KeyPort&0xf0;  //��������ֵ

    while((KeyPort&0xf0)!=0xf0);//�ȴ��ɿ������

    return(cord_h+cord_l);//������������ֵ
   }
  }return(10);     //���ظ�ֵ
}

unsigned char KeyPro(void)
{
 switch(KeyScan())
 {
  case 0x7e:return 1;break;// ������Ӧ�ļ���ʾ���Ӧ����ֵ
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
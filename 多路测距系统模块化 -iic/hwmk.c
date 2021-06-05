#include <reg52.h> //51Í·ÎÄ¼þ
#include <QX_A11.h>//QX-A51ÖÇÄÜÐ¡³µÅäÖÃÎÄ¼
#include "delay.h"
/*====================================
 ×Ô¶¨ÒåÀàÐÍÃû
====================================*/
typedef unsigned char INT8U;
typedef unsigned char uchar;
typedef unsigned int INT16U;
typedef unsigned int uint;

/*====================================
 Ó²¼þ½Ó¿ÚÎ»ÉùÃ÷
====================================*/
sbit IR  = P3^2;     //¶¨ÒåºìÍâÂö³åÊý¾Ý½Ó¿Ú	Íâ²¿ÖÐ¶ÏOÊäÈë¿Ú

uchar IRtime; 		//¼ì²âºìÍâ¸ßµçÆ½³ÖÐøÊ±¼ä£¨Âö¿í£©
uchar IRcord[4];    //´ËÊý×éÓÃÓÚ´¢´æ·ÖÀë³öÀ´µÄ4¸ö×Ö½ÚµÄÊý¾Ý£¨ÓÃ»§Âë2¸ö×Ö½Ú+¼üÖµÂë2¸ö×Ö½Ú£©
uchar IRdata[33];   //´ËÊý×éÓÃÓÚ´¢´æºìÍâµÄ33Î»Êý¾Ý£¨µÚÒ»Î»ÎªÒýµ¼ÂëÓÃ»§Âë16+¼üÖµÂë16£©
bit IRpro_ok, IRok;  //µÚÒ»¸öÓÃÓÚºìÍâ½ÓÊÕ4¸ö×Ö½ÚÍê±Ï¡£IRokÓÃÎª¼ì²âÂö¿íÍê±Ï

void init()	   //³õÊ¼»¯¶¨Ê±Æ÷0 ºÍÍâ²¿ÖÐ¶Ï0
{
	TMOD = 0x02; //¶¨Ê±Æ÷0¹¤×÷·½Ê½2£¬8Î»×Ô¶¯ÖØ×°
	TH0 = 0x00;  //¸ß8Î»×°Èë0ÄÇÃ´¶¨Ê±Æ÷Òç³öÒ»´ÎµÄÊ±¼äÊÇ256¸ö»úÆ÷ÖÜÆÚ
	TL0 = 0x00;
	EA = 1;      //×ÜÖÐ¶Ï
	ET0 = 1;	   //¶¨Ê±Æ÷0ÖÐ¶Ï
	TR0 = 1;     //Æô¶¯¶¨Ê±Æ÷0
	IT0 = 1;	   //ÉèÖÃÍâ²¿ÖÐ¶Ï0ÎªÌøÑØ´¥·¢·½Ê½£¬À´Ò»¸öÏÂ½µÑØ´¥·¢Ò»´Î
	EX0 = 1;	   //Æô¶¯Íâ²¿ÖÐ¶Ï0
}

void time0() interrupt 1   //¶¨Òå¶¨Ê±Æ÷0
{
	IRtime++; 			   //¼ì²âÂö¿í£¬1´ÎÎª278us
}

void int0() interrupt 0	  		//¶¨ÒåÍâ²¿ÖÐ¶Ï0
{
	static uchar i;	 			//	ÉùÃ÷¾²Ì¬±äÁ¿£¨ÔÚÌø³öº¯ÊýºóÔÚ»ØÀ´Ö´ÐÐµÄÊ±ºò²»»á¶ªÊ§ÊýÖµ£©iÓÃÓÚ°Ñ33´Î¸ßµçÆ½µÄ³ÖÐøÊ±¼ä´æÈëIRdata
	static bit startflag;		//¿ªÊ¼´¢´æÂö¿í±êÖ¾Î»
	if(startflag)	 			//¿ªÊ¼½ÓÊÕÂö¿í¼ì²â
	{
		if( (IRtime < 53) && (IRtime >= 32) ) /*ÅÐ¶ÏÊÇ·ñÊÇÒýµ¼Âë£¬µ×µçÆ½9000us+¸ß4500us	
		Õâ¸ö×Ô¼º¿ÉÒÔËãÎÒÒÔ11.0592À´ËãÁËNECÐ­ÒéµÄÒýµ¼ÂëµÍ8000-10000+¸ß4000-5000 
		Èç¹ûÒÑ¾­½ÓÊÕÁËÒýµ¼ÂëÄÇÃ´i²»»á±»ÖÃ0¾Í»á¿ªÊ¼ÒÀ´Î´æÈëÂö¿í*/
			i = 0;				 //Èç¹ûÊÇÒýµ¼ÂëÄÇÃ´Ö´ÐÐi=0°ÑËû´æµ½IRdataµÄµÚÒ»¸öÎ»
		IRdata[i] = IRtime;  		 //ÒÔT0µÄÒç³ö´ÎÊýÀ´¼ÆËãÂö¿í£¬°ÑÕâ¸öÊ±¼ä´æµ½Êý×éÀïÃæµ½ºóÃæÅÐ¶Ï
		IRtime = 0;				 //¼ÆÊýÇåÁã£¬ÏÂÒ»¸öÏÂ½µÑØµÄÊ±ºòÔÚ´æÈëÂö¿í
		i++; 					 //¼ÆÊýÂö¿í´æÈëµÄ´ÎÊý
		if(i == 33) 				 //Èç¹û´æÈë34´Î Êý×éµÄÏÂ±êÊÇ´Ó0¿ªÊ¼iµÈÓÚ33±íÊ¾Ö´ÐÐÁË34´Î
		{
		 	IRok = 1;				 //ÄÇÃ´±íÊ¾Âö¿í¼ì²âÍê±Ï
			i = 0; 				 //°ÑÂö¿í¼ÆÊýÇåÁã×¼±¸ÏÂ´Î´æÈë
		}
	}
	else		  
	{
		IRtime = 0; 				 //Òýµ¼Âë¿ªÊ¼½øÈë°ÑÂö¿í¼ÆÊýÇåÁã¿ªÊ¼¼ÆÊý
		startflag = 1;			 //¿ªÊ¼´¦Àí±êÖ¾Î»ÖÃ1
	}
}

void IRcordpro()   				 //ÌáÈ¡ËüµÄ33´ÎÂö¿í½øÐÐÊý¾Ý½âÂë
{
	uchar i, j, k, cord, value;	/*iÓÃÓÚ´¦Àí4¸ö×Ö½Ú£¬jÓÃÓÚ´¦ÀíÒ»¸ö×Ö½ÚÖÐÃ¿Ò»Î»£¬kÓÃÓÚ33´ÎÂö¿íÖÐµÄÄÄÒ»Î»
	cordÓÃÓÚÈ¡³öÂö¿íµÄÊ±¼äÅÐ¶ÏÊÇ·ñ·ûºÏ1µÄÂö¿íÊ±¼ä*/
	k = 1; 						//´ÓµÚÒ»Î»Âö¿í¿ªÊ¼È¡£¬¶ªÆúÒýµ¼ÂëÂö¿í
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 8; j++)
		{
			cord = IRdata[k];	    //°ÑÂö¿í´æÈëcord
			if(cord > 5)	 		//Èç¹ûÂö¿í´óÓÚÎÒ11.0592µÄt0Òç³öÂÊÎªÔ¼278us*5=1390ÄÇÃ´ÅÐ¶ÏÎª1
			value = value | 0x80;	/*½ÓÊÕµÄÊ±ºòÊÇÏÈ½ÓÊÕ×îµÍÎ»£¬
			°Ñ×îµÍÎ»ÏÈ·Åµ½valueµÄ×î¸ßÎ»ÔÚºÍ0x08°´Î»»òÒ»ÏÂ
			ÕâÑù²»»á¸Ä±ävaluaµÄÆäËûÎ»µÄÊýÖµÖ»»áÈÃËû×î¸ßÎ»Îª1*/
			if(j < 7)
			{
				value = value >> 1;	//valueÎ»×óÒÆÒÀ´Î½ÓÊÕ8Î»Êý¾Ý¡£
			}
			k++;				//Ã¿Ö´ÐÐÒ»´ÎÂö¿íÎ»¼Ó1
		}
		IRcord[i] = value;	   //Ã¿´¦ÀíÍêÒ»¸ö×Ö½Ú°ÑËü·ÅÈëIRcordÊý×éÖÐ¡£
		value = 0; 			   //ÇåÁãvalue·½±ãÏÂ´ÎÔÚ´æÈëÊý¾Ý
	}
	IRpro_ok = 1;				   //½ÓÊÕÍê4¸ö×Ö½ÚºóIRpro okÖÃ1±íÊ¾ºìÍâ½âÂëÍê³É	
}
/*PWM¿ØÖÆÊ¹ÄÜ Ð¡³µÇ°½ø*/
void forward()
{
	left_motor_go; //×óµç»úÇ°½ø
	right_motor_go; //ÓÒµç»úÇ°½ø
}

	
/*PWM¿ØÖÆÊ¹ÄÜ Ð¡³µºóÍË*/
void backward()
{
	left_motor_back; //×óµç»úºóÍË
	right_motor_back; //ÓÒµç»úºóÍË	
}


/*PWM¿ØÖÆÊ¹ÄÜ Ð¡³µ×ó×ª*/
void left_run()
{
	left_motor_stops; //×óµç»úÍ£Ö¹
	right_motor_go; //ÓÒµç»úÇ°½ø	
}


/*PWM¿ØÖÆÊ¹ÄÜ Ð¡³µÓÒ×ª*/
void right_run()
{
	right_motor_stops;//ÓÒµç»úÍ£Ö¹
	left_motor_go;    //×óµç»úÇ°½ø
}


/*Ð¡³µÍ£Ö¹*/
void stop()
{
	right_motor_stops;//ÓÒµç»úÍ£Ö¹
	left_motor_stops; //×óµç»úÍ£Ö¹	
}

void hwmk()
{
	init();	//Ö´ÐÐ³õÊ¼»¯¶¨Ê±Æ÷0ºÍÍâ²¿ÖÐ¶Ï0
	Left_moto_pwm = Right_moto_pwm = 1;//Ê¹ÄÜ×óÓÒµç»ú
	while(1)	//´óÑ­»·
	{
		if(IRok)    //ÅÐ¶ÏÂö¿íÊÇ·ñ¼ì²âÍê±Ï                    
		{   
			IRcordpro();//¸ù¾ÝÂö¿í½âÂë³ö4¸ö×Ö½ÚµÄÊý¾Ý
			IRok = 0;	//ÖØÐÂµÈ´ýÂö¿í¼ì²â
			if(IRpro_ok) //ÅÐ¶ÏÊÇ·ñ½âÂëÍê±Ï  
			{
		        switch(IRcord[2])
		   		{
				     case 0x18:  stop(); DelayMs(200); forward(); 			 //Ç°½ø
				             break;
				     case 0x52:  stop(); DelayMs(200); backward();  			 //ºóÍË	 
				             break;
				     case 0x08:  stop(); DelayMs(200); left_run(); 			 //×ó×ª
				             break;
					 case 0x5A:  stop(); DelayMs(200); right_run(); 			 //ÓÒ×ª
				             break;
					 case 0x1C:  stop();			     //Í£Ö¹
				             break;
					 default:break;
		   		}
				IRpro_ok = 0;
			}
		}	
	}
}
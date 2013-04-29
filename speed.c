/******************************************************************************************
程序名：检查小车行使距离-LCD1602
编写人：Yayi
论坛：rtrobot.org　　　                                                
/******************************************************************************************/
#include "main.h"
#include <REGX52.h>

unsigned int motor1=0;	 //计左电机码盘脉冲值
unsigned int motor2=0;	 //计右电机码盘脉冲值
unsigned int speed1=0;	 //计左电机码盘脉冲值
unsigned int speed2=0;	 //计右电机码盘脉冲
unsigned int kk;

 void motorspeeds()
{

	if(k==1000)
	{ k=0;		
	  ++kk;
	if(kk==10)
	{	kk=0;		//重新定义k的值
		speed1=1;
		speed2=motor2;
	//	motor1=0;	 	//重新定义motor1的值
		motor2=0;		//重新定义motor1的值
	}}		
}



/******************************************************************************************
�����������С����ʹ����-LCD1602
��д�ˣ�Yayi
��̳��rtrobot.org������                                                
/******************************************************************************************/
#include "main.h"
#include <REGX52.h>

unsigned int motor1=0;	 //��������������ֵ
unsigned int motor2=0;	 //���ҵ����������ֵ
unsigned int speed1=0;	 //��������������ֵ
unsigned int speed2=0;	 //���ҵ����������
unsigned int kk;

 void motorspeeds()
{

	if(k==1000)
	{ k=0;		
	  ++kk;
	if(kk==10)
	{	kk=0;		//���¶���k��ֵ
		speed1=1;
		speed2=motor2;
	//	motor1=0;	 	//���¶���motor1��ֵ
		motor2=0;		//���¶���motor1��ֵ
	}}		
}



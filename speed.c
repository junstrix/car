/******************************************************************************************
�����������С����ʹ����-LCD1602
��д�ˣ�Yayi
��̳��rtrobot.org������                                                
 ******************************************************************************************/
#include "main.h"
#include <REGX52.h>

unsigned int motor1=0;	 //��������������ֵ
unsigned int motor2=0;	 //���ҵ����������ֵ
unsigned int mo_length1=0;	 //�������ߵľ���
unsigned int mo_length2=0;	 //���ҵ���ߵľ���
unsigned int kk;

 void motorspeeds()
{	if (k>=1000)		   //ʱ�䵽0.1��
     {
		k=0;
	  ++kk;
	if(kk>=10)			   //ʱ�䵽1��
	{	kk=0;		//���¶���k��ֵ
	    ++mo_time;
		mo_length1=motor1;	  //����21�����̿�϶����̥�ܳ�21cm���ٶȵ���һ���Ӽ������̿�϶/2
		mo_length2=motor2;
		total_length+=(motor1+motor2)/2;
		motor1=0;	 	//���¶���motor1��ֵ
		motor2=0;		//���¶���motor1��ֵ
	}}		
}



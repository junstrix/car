#include "main.h"
#include "LCD1602.h"
#include <REGX52.h>

unsigned int motor1=0;	 //��������������ֵ
unsigned int motor2=0;	 //���ҵ����������ֵ
unsigned int mo_length1=0;	 //�������ߵľ���
unsigned int mo_length2=0;	 //���ҵ���ߵľ���
unsigned int count_kk;

void motorspeeds(void)
{	
	if (count_k>=100)		   //ʱ�䵽0.01��
	{

		count_k=0;
		++count_kk;
		if(count_kk>=100)			   //ʱ�䵽1��
		{	
			count_kk=0;		//���¶���k��ֵ
			++mo_time;
			mo_length1=motor1;	  //����21�����̿�϶����̥�ܳ�21cm���ٶȵ���һ���Ӽ������̿�϶/2
			mo_length2=motor2;
			total_length+=(motor1+motor2)/2;
			motor1=0;	 	//���¶���motor1��ֵ
			motor2=0;		//���¶���motor1��ֵ
		}
	}
}

#include <REGX52.h>
#include "motor.h"
#include "LCD1602.h"
#include "main.h"

unsigned int motor1=0;	 //��������������ֵ
unsigned int motor2=0;	 //���ҵ����������ֵ
unsigned int mo_length1=0;	 //�������ߵľ���
unsigned int mo_length2=0;	 //���ҵ���ߵľ���

/*�����ͬ�ٶ���ǰת��*/
void mo_forword(void)
{
	Con_ZKB(927,73,100,900);
}
void mo_forword_slow(void)
{
	Con_ZKB(827,173,200,800);
}
/*΢�ҵ�*/
void mo_R_forword(void)
{
	Con_ZKB(860,140,100,900);
}
void mo_R_forword_slow(void)
{
	Con_ZKB(800,200,200,800);
}
/*΢���*/
void mo_L_forword(void)
{
	Con_ZKB(950,50,100,900);
}
void mo_L_forword_slow(void)
{
	Con_ZKB(850,150,200,800);
}
/*�����ͬ�ٶ����ת��*/
void mo_back(void)
{
	Con_ZKB(73,927,900,100);
}
/*ֹͣ*/
void mo_stop(void)
{
	Con_ZKB(500,500,500,500);
}
/*����ת,�ҵ��ͣת������ת*/
void mo_right(void)
{
	Con_ZKB(500,500,100,900);
}
/*����ת������ͣת���ҵ��ת*/
void mo_left(void)
{
	Con_ZKB(927,73,500,500);
}
/*ռ�ձȿ���,���٣������ С��Ϊ�ߵ�ƽ������Ϊ�͵�ƽ*/
void Con_ZKB(uint a, uint b, uint c, uint d)
{
	ZKB1 = a;
	ZKB2 = b;
	ZKB3 = c;
	ZKB4 = d;
}
/*
 * ���Ʒ�������led�� 
 * 1 -- on
 * other -- off
 */
void buzzer_led(uchar a)
{
	if (a==1) {
		BUZZER = 0;
		WARNING_LED = 1;
	}
	else {
		BUZZER = 1;
		WARNING_LED = 0;
	}
}

/* ����� */
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

/* ���ȿ��� */
/* 1 -- on  */
/* other -- off */
void motor_fan_con(uchar a)
{
	if (a == 1) {
		MOTOR_FAN = 1;
	}
	else {
		MOTOR_FAN = 0;
	}
}

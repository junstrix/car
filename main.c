#include <REGX52.h>
#include <stdio.h>
#include <ctype.h>
#include "main.h"
#include "LCD1602.h"
#include "motor.h"
#include "motorspeed.h"



void init_sys(void);
unsigned int ZKB1,ZKB2,ZKB3,ZKB4;
unsigned int k=0;
unsigned char mo_time;
unsigned int total_length=0;	 //��С���ߵľ���

void main(void)
{
	init_sys();
	LcdInitiate();         //����LCD��ʼ������  
	Delay1ms(2);
	WriteInstruction(0x01);//����ʾ������Ļָ��
	DisMenuInit();
    Con_ZKB(10,990,40,960);
	while(1){


		ClearVarData();
		WriteVarData(0x05,mo_time);
		WriteVarData(0x0d,total_length);
		Delay1ms(30);
	
	}
}

void init_sys(void)            /*ϵͳ��ʼ������*/ 
{ 
	/*��ʱ����ʼ��*/ 
	TMOD=V_TMOD; 
	TH0=V_TH0; 
	TL0=V_TL0; 
	TR0=1; 
	ET0=1; 
	EX0 = 1; 		//�����ⲿ�ж�0�ж�
	IT0 = 1; 		//1�����ش���  0���͵�ƽ����
	EX1 = 1;
	IT1	= 1;
	EA=1; 

}

void timer0(void) interrupt 1 using 2 
{ 
	static uchar click=0;                  /*�жϴ�������������*/ 
	TH0=V_TH0;                                    /*�ָ���ʱ����ʼֵ*/ 
	TL0=V_TL0; 
	++click; 
    ++k;							 //ÿ0.1ms��һ��
	motorspeeds(); 					  //���þ����ʱ����ʾ
	if (click>=1000)
		click=0; 
	if (click<=ZKB1)      /*��С��ռ�ձ�ֵʱ����͵�ƽ������ʱ�Ǹߵ�ƽ���Ӷ�ʵ��ռ�ձȵĵ���*/ 
		P1_0=0; 
	else 
		P1_0=1; 
	if (click<=ZKB2)                        
		P1_1=0; 
	else 
		P1_1=1;
	if (click<=ZKB3)      /*��С��ռ�ձ�ֵʱ����͵�ƽ������ʱ�Ǹߵ�ƽ���Ӷ�ʵ��ռ�ձȵĵ���*/ 
		P1_2=0; 
	else 
		P1_2=1;

	if (click<=ZKB4)                        
		P1_3=0; 
	else 
		P1_3=1;
}


/*********************************************************************************************
�ⲿ�ж�INT0������1������
/********************************************************************************************/
void intersvr1(void) interrupt 0 using 1
{
	motor1++;		
}
/*********************************************************************************************
�ⲿ�ж�INT1������2������
/********************************************************************************************/
void intersvr2(void) interrupt 2 using 3
{
	motor2++;
}
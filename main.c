#include <REGX52.h>
#include "main.h"
#include "LCD1602.h"
#include "motor.h"

void init_sys(void);
unsigned int ZKB1,ZKB2,ZKB3,ZKB4;

void main(void)
{
	mo_forword();	
}

void init_sys(void)            /*ϵͳ��ʼ������*/ 
{ 
	/*��ʱ����ʼ��*/ 
	TMOD=V_TMOD; 
	TH0=V_TH0; 
	TL0=V_TL0; 
	TR0=1; 
	ET0=1; 
	EA=1;  
	SCON  = 0x50;		        /* SCON: mode 1, 8-bit UART, enable rcvr      */
	/*TMOD  = 0x20;               [> TMOD: timer 1, mode 2, 8-bit reload        <]*/
	TL1 = 0XFD;
	TH1   = 0Xfd;                /* TH1:  reload value for 1200 baud @ 16MHz   */
	TR1   = 1;                  /* TR1:  timer 1 run                          */
	TI    = 1; 
}

void timer0(void) interrupt 1 using 2 
{ 
	static uchar click=0;                  /*�жϴ�������������*/ 
	TH0=V_TH0;                                    /*�ָ���ʱ����ʼֵ*/ 
	TL0=V_TL0; 
	++click; 
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

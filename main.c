#include <REGX52.h>
#include <stdio.h>
#include "main.h"
#include "LCD1602.h"
#include "motor.h"

void init_sys(void);
unsigned int ZKB1,ZKB2,ZKB3,ZKB4;

void main(void)
{
	init_sys();
	LcdInitiate();         //调用LCD初始化函数  
	Delay1ms(2);
	WriteInstruction(0x01);//清显示：清屏幕指令
	DisMenuInit();
	while(1){
		mo_forword();
		ClearVarData();
		WriteVarData(0x05,ZKB1);
		WriteVarData(0x0d,ZKB2);
		WriteVarData(0x45,ZKB3);
		WriteVarData(0x4d,ZKB4);
		mo_back();
		ClearVarData();
		WriteVarData(0x05,ZKB1);
		WriteVarData(0x0d,ZKB2);
		WriteVarData(0x45,ZKB3);
		WriteVarData(0x4d,ZKB4);
	}
}

void init_sys(void)            /*系统初始化函数*/ 
{ 
	/*定时器初始化*/ 
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
	static uchar click=0;                  /*中断次数计数器变量*/ 
	TH0=V_TH0;                                    /*恢复定时器初始值*/ 
	TL0=V_TL0; 
	++click; 
	if (click>=1000)
		click=0; 
	if (click<=ZKB1)      /*当小于占空比值时输出低电平，高于时是高电平，从而实现占空比的调整*/ 
		P1_0=0; 
	else 
		P1_0=1; 
	if (click<=ZKB2)                        
		P1_1=0; 
	else 
		P1_1=1;
	if (click<=ZKB3)      /*当小于占空比值时输出低电平，高于时是高电平，从而实现占空比的调整*/ 
		P1_2=0; 
	else 
		P1_2=1;

	if (click<=ZKB4)                        
		P1_3=0; 
	else 
		P1_3=1;
}

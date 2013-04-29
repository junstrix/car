#include <REGX52.h>
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
		if (CarTurnLeft) {
			mo_left();
		}
		else if (CarTurnRight) {
			mo_right();
		}
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
		MOTOR_R1=0;
	else 
		MOTOR_R1=1; 
	if (click<=ZKB2)                        
		MOTOR_R2=0; 
	else 
		MOTOR_R2=1;
	if (click<=ZKB3)      /*当小于占空比值时输出低电平，高于时是高电平，从而实现占空比的调整*/
		MOTOR_L1=0; 
	else 
		MOTOR_L1=1;
	if (click<=ZKB4)                        
		MOTOR_L2=0; 
	else 
		MOTOR_L2=1;
}

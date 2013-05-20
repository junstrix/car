#include <REGX52.h>
#include "LCD1602.h"
#include "motor.h"
#include "main.h"

void init_sys(void);
unsigned int ZKB1,ZKB2,ZKB3,ZKB4;
unsigned int count_k=0;
unsigned int count_kk;
unsigned int count_coin=0;//硬币数量
unsigned int count_bottle=0;//瓶子数量
unsigned char mo_time;
unsigned int total_length=0;	 //计小车走的距离

void main(void)
{
	motor_fan_con(0);
	buzzer_led(0);
	init_sys();
	LcdInitiate();         //调用LCD初始化函数  
	Delay1ms(2);
	WriteInstruction(0x01);//清显示：清屏幕指令
	DisMenuInit();
	mo_forword();
	while(1){
		if (DeviateLeftTrack) {
			mo_R_forword();
		}
		if(DeviateRightTrack)	
		{
			mo_L_forword();
		}
		if(CarTurnLeft){
			mo_left();
			buzzer_led(1);
			Delay1ms(20);
			buzzer_led(0);
		}
		if (CarTurnRight) {
			mo_right();
			buzzer_led(1);
			Delay1ms(20);
			buzzer_led(0);
		}
		if (CHECK_COIN) {
			Delay1ms(5);
			if (CHECK_COIN) {
				mo_stop();
				buzzer_led(1);
				Delay1ms(500);
				mo_forword();
				buzzer_led(0);
				Delay1ms(50);       //不能太小，不能太大，太小会冲出跑道，小了会多次检测！
				if (!CHECK_COIN) {
					count_coin++;
				}
			}
		}
		if (UpBottle) {
			motor_fan_con(0);
			buzzer_led(1);
			Delay1ms(50);
			buzzer_led(0);
			if (NoBottle) {
				count_bottle++;
			}
		}
		if (DownBottle) {
			Delay1ms(2);
			if (DownBottle) {
				mo_stop();
				motor_fan_con(1);
				Delay1ms(250);
				mo_forword();
				motor_fan_con(0);
			}
			if (NoBottle) {
				count_bottle++;
				motor_fan_con(0);
			}
		}
		if (count_kk>=50&&count_kk<51) { //变量显示稳定控制
			ClearVarData();
			WriteVarData(0x05,mo_time);
			WriteVarData(0x0d,total_length);
			WriteVarData(0x45,count_coin);
			WriteVarData(0x4d,count_bottle);
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
	EX0=1; 		//允许外部中断0中断
	IT0=1; 		//1：下沿触发  0：低电平触发
	EX1=1;
	IT1=1;
	EA=1; 
}

void timer0(void) interrupt 1 using 2 
{ 
	static uchar click=0;                  /*中断次数计数器变量*/ 
	TH0=V_TH0;                                    /*恢复定时器初始值*/ 
	TL0=V_TL0; 
	++click; 
	++count_k;							 //每0.1ms记一次
	motorspeeds(); 					  //调用距离和时间显示
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


/*********************************************************************************************
  外部中断INT0计算电机1的脉冲
/********************************************************************************************/
void intersvr1(void) interrupt 0 using 1
{
	motor1++;		
}
/*********************************************************************************************
  外部中断INT1计算电机2的脉冲
/********************************************************************************************/
void intersvr2(void) interrupt 2 using 3
{
	motor2++;
}

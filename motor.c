#include <REGX52.h>
#include "motor.h"
#include "LCD1602.h"
#include "main.h"

unsigned int motor1=0;	 //计左电机码盘脉冲值
unsigned int motor2=0;	 //计右电机码盘脉冲值
unsigned int mo_length1=0;	 //计左电机走的距离
unsigned int mo_length2=0;	 //计右电机走的距离

/*两电机同速度向前转动*/
void mo_forword(void)
{
	Con_ZKB(927,73,100,900);
}
void mo_forword_slow(void)
{
	Con_ZKB(827,173,200,800);
}
/*微右调*/
void mo_R_forword(void)
{
	Con_ZKB(860,140,100,900);
}
void mo_R_forword_slow(void)
{
	Con_ZKB(800,200,200,800);
}
/*微左调*/
void mo_L_forword(void)
{
	Con_ZKB(950,50,100,900);
}
void mo_L_forword_slow(void)
{
	Con_ZKB(850,150,200,800);
}
/*两电机同速度向后转动*/
void mo_back(void)
{
	Con_ZKB(73,927,900,100);
}
/*停止*/
void mo_stop(void)
{
	Con_ZKB(500,500,500,500);
}
/*向右转,右电机停转，左电机转*/
void mo_right(void)
{
	Con_ZKB(500,500,100,900);
}
/*向左转，左电机停转，右电机转*/
void mo_left(void)
{
	Con_ZKB(927,73,500,500);
}
/*占空比控制,车速，方向等 小数为高电平，大数为低电平*/
void Con_ZKB(uint a, uint b, uint c, uint d)
{
	ZKB1 = a;
	ZKB2 = b;
	ZKB3 = c;
	ZKB4 = d;
}
/*
 * 控制蜂鸣器和led灯 
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

/* 测距离 */
void motorspeeds(void)
{	
	if (count_k>=100)		   //时间到0.01秒
	{

		count_k=0;
		++count_kk;
		if(count_kk>=100)			   //时间到1秒
		{	
			count_kk=0;		//重新定义k的值
			++mo_time;
			mo_length1=motor1;	  //共有21个码盘空隙，轮胎周长21cm，速度等于一秒钟计数码盘空隙/2
			mo_length2=motor2;
			total_length+=(motor1+motor2)/2;
			motor1=0;	 	//重新定义motor1的值
			motor2=0;		//重新定义motor1的值
		}
	}
}

/* 风扇控制 */
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

#include "main.h"
#include "LCD1602.h"
#include <REGX52.h>

unsigned int motor1=0;	 //计左电机码盘脉冲值
unsigned int motor2=0;	 //计右电机码盘脉冲值
unsigned int mo_length1=0;	 //计左电机走的距离
unsigned int mo_length2=0;	 //计右电机走的距离
unsigned int count_kk;

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

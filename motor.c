#include <REGX52.h>
#include "motor.h"
#include "LCD1602.h"
#include "main.h"

/*两电机同速度向前转动*/
void mo_forword(void)
{
	Con_ZKB(990,10,40,960);
}
/*两电机同速度向后转动*/
void mo_back(void)
{
	Con_ZKB(10,990,960,40);
}
/*停止*/
void mo_stop(void)
{
	Con_ZKB(50,50,50,50);
}
/*向右转,右电机停转，左电机转*/
void mo_right(void)
{
	Con_ZKB(990,10,960,40);
}
/*微调右转*/
void mo_mic_right(void)
{
	/* code */
}
/*向左转，左电机停转，右电机转*/
void mo_left(void)
{
	Con_ZKB(10,990,40,960);
}
/*微调左转*/
void mo_mic_left(void)
{
	/* code */
}
/*占空比控制,车速，方向等 小数为高电平，大数为低电平*/
void Con_ZKB(uint a, uint b, uint c, uint d)
{
	ZKB1 = a;
	ZKB2 = b;
	ZKB3 = c;
	ZKB4 = d;
}

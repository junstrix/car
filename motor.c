#include <REGX52.h>
#include "motor.h"
#include "LCD1602.h"
#include "main.h"

/*两电机同速度向前转动*/
void mo_forword(void)
{
	Con_ZKB(927,73,100,900);
}
/*微右调*/
void mo_R_forword(void)
{
	Con_ZKB(860,140,100,900);
}
/*微左调*/
void mo_L_forword(void)
{
	Con_ZKB(950,50,100,900);
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

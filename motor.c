#include <REGX52.h>
#include "motor.h"
#include "LCD1602.h"
#include "main.h"

/*�����ͬ�ٶ���ǰת��*/
void mo_forword(void)
{
	Con_ZKB(927,73,100,900);
}
/*΢�ҵ�*/
void mo_R_forword(void)
{
	Con_ZKB(860,140,100,900);
}
/*΢���*/
void mo_L_forword(void)
{
	Con_ZKB(950,50,100,900);
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

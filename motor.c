#include <REGX52.h>
#include "motor.h"
#include "LCD1602.h"
#include "main.h"

/*�����ͬ�ٶ���ǰת��*/
void mo_forword(void)
{
	Con_ZKB(990,10,40,960);
}
/*�����ͬ�ٶ����ת��*/
void mo_back(void)
{
	Con_ZKB(10,990,960,40);
}
/*ֹͣ*/
void mo_stop(void)
{
	Con_ZKB(50,50,50,50);
}
/*����ת,�ҵ��ͣת������ת*/
void mo_right(void)
{
	Con_ZKB(990,10,960,40);
}
/*΢����ת*/
void mo_mic_right(void)
{
	/* code */
}
/*����ת������ͣת���ҵ��ת*/
void mo_left(void)
{
	Con_ZKB(10,990,40,960);
}
/*΢����ת*/
void mo_mic_left(void)
{
	/* code */
}
/*ռ�ձȿ���,���٣������ С��Ϊ�ߵ�ƽ������Ϊ�͵�ƽ*/
void Con_ZKB(uint a, uint b, uint c, uint d)
{
	ZKB1 = a;
	ZKB2 = b;
	ZKB3 = c;
	ZKB4 = d;
}

#include <REGX52.h>
#include "motor.h"
#define uint unsigned int
#define uchar unsigned char
/*�����ͬ�ٶ���ǰת��*/
void mo_forword(void)
{
	Con_ZKB(990,10,960,40);
}
/*�����ͬ�ٶ����ת��*/
void mo_back(void)
{
	Con_ZKB(10,990,40,960);
}
/*ֹͣ*/
void mo_stop(void)
{
	Con_ZKB(50,50,40,960);
}
/*����ת,�ҵ��ͣת������ת*/
void mo_right(void)
{
	/* code */
}
/*΢����ת*/
void mo_mic_right(void)
{
	/* code */
}
/*����ת������ͣת���ҵ��ת*/
void mo_left(void)
{
	/* code */
}
/*΢����ת*/
void mo_mic_left(void)
{
	/* code */
}
/*ռ�ձȿ���*/
void Con_ZKB(uint a, uint b, uint c, uint d)
{
	ZKB1 = a;
	ZKB2 = b;
	ZKB3 = c;
	ZKB4 = d;
}

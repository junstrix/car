#include <REGX52.h>
#include "main.h"
#include "LCD1602.h"
#include "motor.h"
#include "motorspeed.h"

void init_sys(void);
unsigned int ZKB1,ZKB2,ZKB3,ZKB4;
unsigned int count_k=0;
unsigned int count_coin=0;//Ӳ������
unsigned int count_bottle=0;//ƿ������
unsigned char mo_time;
unsigned int total_length=0;	 //��С���ߵľ���

void main(void)
{
	init_sys();
	LcdInitiate();         //����LCD��ʼ������  
	Delay1ms(2);
	WriteInstruction(0x01);//����ʾ������Ļָ��
	DisMenuInit();
	mo_forword();
	buzzer_led(0);
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
				Delay1ms(50);       //����̫С������̫��̫С�����ܵ���С�˻��μ�⣡
				if (!CHECK_COIN) {
					count_coin++;
				}
			}
		}
		if (UpBottle) {
			Delay1ms(5);
			if (NoBottle) {
				count_bottle++;
			}
		}
		if (DownBottle) {
			Delay1ms(5);
			if (NoBottle) {
				count_bottle++;
			}
		}
		if (count_kk>=50&&count_kk<51) { //������ʾ�ȶ�����
			ClearVarData();
			WriteVarData(0x05,mo_time);
			WriteVarData(0x0d,total_length);
			WriteVarData(0x45,count_coin);
			WriteVarData(0x4d,count_bottle);
		}
	}
}

void init_sys(void)            /*ϵͳ��ʼ������*/ 
{ 
	/*��ʱ����ʼ��*/ 
	TMOD=V_TMOD; 
	TH0=V_TH0; 
	TL0=V_TL0; 
	TR0=1; 
	ET0=1; 
	EX0 = 1; 		//�����ⲿ�ж�0�ж�
	IT0 = 1; 		//1�����ش���  0���͵�ƽ����
	EX1 = 1;
	IT1	= 1;
	EA=1; 
}

void timer0(void) interrupt 1 using 2 
{ 
	static uchar click=0;                  /*�жϴ�������������*/ 
	TH0=V_TH0;                                    /*�ָ���ʱ����ʼֵ*/ 
	TL0=V_TL0; 
	++click; 
	++count_k;							 //ÿ0.1ms��һ��
	motorspeeds(); 					  //���þ����ʱ����ʾ
	if (click>=1000)
		click=0; 
	if (click<=ZKB1)      /*��С��ռ�ձ�ֵʱ����͵�ƽ������ʱ�Ǹߵ�ƽ���Ӷ�ʵ��ռ�ձȵĵ���*/
		MOTOR_R1=0;
	else 
		MOTOR_R1=1; 
	if (click<=ZKB2)                     
		MOTOR_R2=0; 
	else 
		MOTOR_R2=1;
	if (click<=ZKB3)      /*��С��ռ�ձ�ֵʱ����͵�ƽ������ʱ�Ǹߵ�ƽ���Ӷ�ʵ��ռ�ձȵĵ���*/
		MOTOR_L1=0; 
	else 
		MOTOR_L1=1;
	if (click<=ZKB4)                        
		MOTOR_L2=0; 
	else 
		MOTOR_L2=1;
}


/*********************************************************************************************
  �ⲿ�ж�INT0������1������
/********************************************************************************************/
void intersvr1(void) interrupt 0 using 1
{
	motor1++;		
}
/*********************************************************************************************
  �ⲿ�ж�INT1������2������
/********************************************************************************************/
void intersvr2(void) interrupt 2 using 3
{
	motor2++;
}

#include <REGX52.h>
#include <intrins.h>  //����_nop_()���������ͷ�ļ�
#include "LCD1602.h"

unsigned char *str_time = "Time:"; //��ʾ�ַ��˵�   
unsigned char *str_run = "Run:";
unsigned char *str_coins = "Coin:";
unsigned char *str_bottle = "Bot:";
unsigned char Nchar[]=" "; //���ַ�
unsigned char digit[]={"0123456789"}; //�����ַ�������ʾ����

/*****************************************************
  �������ܣ���ʱ���ɺ���
  ��ڲ�����n
 ***************************************************/
void Delay1ms(unsigned int i)      //��ʱ����,i����ʽ����
{
	unsigned int j;
	for( ;i>0;i--)             //����i��ʵ�ʲ�������һ��ֵ,���i���ܸ���ֵ
		for(j=0;j<125;j++)
			;
}

/*****************************************************
  �������ܣ��ж�Һ��ģ���æµ״̬
  ����ֵ��result��result=1��æµ;result=0����æ
 ***************************************************/
unsigned char BusyTest(void)
{
	bit result;
	LCD_RS=0;       //���ݹ涨��RSΪ�͵�ƽ��RWΪ�ߵ�ƽʱ�����Զ�״̬
	LCD_RW=1;
	LCD_EN=1;        //E=1���������д
	_nop_();   //�ղ���
	_nop_();
	_nop_(); 
	_nop_();   //�ղ����ĸ��������ڣ���Ӳ����Ӧʱ��	
	result=LCD_BUSY;  //��æµ��־��ƽ����result
	LCD_EN=0;
	return result;
}
/*****************************************************
  �������ܣ���ģʽ����ָ�����ʾ��ַд��Һ��ģ��
  ��ڲ�����dictate
 ***************************************************/
void WriteInstruction (unsigned char dictate)
{   
	while(BusyTest()==1); //���æ�͵ȴ�
	LCD_RS=0;                  //���ݹ涨��RS��R/WͬʱΪ�͵�ƽʱ������д��ָ��
	LCD_RW=0;   
	LCD_EN=0;                   //E�õ͵�ƽ(���ݱ�8-6��дָ��ʱ��EΪ�����壬
	// ������E��0��1���������䣬����Ӧ����"0"
	_nop_();
	_nop_();             //�ղ��������������ڣ���Ӳ����Ӧʱ��
	LCDIO=dictate;            //����������P0�ڣ���д��ָ����ַ
	_nop_();
	_nop_();
	_nop_();
	_nop_();               //�ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
	LCD_EN=1;                   //E�øߵ�ƽ
	_nop_();
	_nop_();
	_nop_();
	_nop_();               //�ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
	LCD_EN=0;                  //��E�ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ�鿪ʼִ������
}
/*****************************************************
  �������ܣ�ָ���ַ���ʾ��ʵ�ʵ�ַ
  ��ڲ�����x
 ***************************************************/
void WriteAddress(unsigned char x)
{
	WriteInstruction(x|0x80); //��ʾλ�õ�ȷ�������涨Ϊ"80H+��ַ��x"
}
/*****************************************************
  �������ܣ�������(�ַ��ı�׼ASCII��)д��Һ��ģ��
  ��ڲ�����y(Ϊ�ַ�����)
 ***************************************************/
void WriteData(unsigned char y)
{
	while(BusyTest()==1);  
	LCD_RS=1;           //RSΪ�ߵ�ƽ��RWΪ�͵�ƽʱ������д������
	LCD_RW=0;
	LCD_EN=0;            //E�õ͵�ƽ(���ݱ�8-6��дָ��ʱ��EΪ�����壬
	// ������E��0��1���������䣬����Ӧ����"0"
	LCDIO=y;           //����������P0�ڣ���������д��Һ��ģ��
	_nop_();
	_nop_();
	_nop_();
	_nop_();       //�ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
	LCD_EN=1;          //E�øߵ�ƽ
	_nop_();
	_nop_();
	_nop_();
	_nop_();        //�ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
	LCD_EN=0;            //��E�ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ�鿪ʼִ������
}
/*��ղ˵���ʾ������*/
void ClearVarData(void)
{
	unsigned char i=0;
	WriteAddress(0x05);
	for (i = 0; i < 4; i++) {
		WriteData(Nchar[0]);
	}
	WriteAddress(0x0d);
	for (i = 0; i < 3; i++) {
		WriteData(Nchar[0]);
	}
	WriteAddress(0x45);
	for (i = 0; i < 4; i++) {
		WriteData(Nchar[0]);
	}
	WriteAddress(0x4d);
	for (i = 0; i < 3; i++) {
		WriteData(Nchar[0]);
	}
}
/**********************************************
  ��ʾһ��������ֵ,������������ܳ�������
  ��һ������Ϊ��ʾ��ַ���ڶ�����Ϊ��ʾ����
 **********************************************/
void WriteVarData(unsigned char addr, unsigned int x)
{
	unsigned char D1,D2,D3,D4,D5;
	WriteInstruction(addr|0x80); //д��������ʾ��ַ
	D1=x%10;             //ģ�����ݲɼ� D1=x%10;              //�����λ����
	D2=(x%100)/10;        //����ʮλ����
	D3=(x%1000)/100;      //�����λ����
	D4=(x%10000)/1000;    //����ǧλ����
	D5=x/10000;            //������λ����
	if (x<100) {
		WriteData(digit[D2]);
		WriteData(digit[D1]);
	}
	else if (x<1000) {
		WriteData(digit[D3]);
		WriteData(digit[D2]);
		WriteData(digit[D1]);
	}
	else if (x<10000) {
		WriteData(digit[D4]);
		WriteData(digit[D3]);
		WriteData(digit[D2]);
		WriteData(digit[D1]);
	}
	else
	{
		WriteData(digit[D5]);
		WriteData(digit[D4]);
		WriteData(digit[D3]);
		WriteData(digit[D2]);
		WriteData(digit[D1]);
	}
}

/*****************************************************
  �������ܣ���LCD����ʾģʽ���г�ʼ������
 ***************************************************/
void LcdInitiate(void)
{
	Delay1ms(5);             //��ʱ15ms���״�дָ��ʱӦ��LCDһ�νϳ��ķ�Ӧʱ��
	WriteInstruction(0x38);  //��ʾģʽ���ã�16��2��ʾ��5��7����8λ���ݽӿ�
	Delay1ms(2);   //��ʱ5ms��
	WriteInstruction(0x38);
	Delay1ms(2);
	WriteInstruction(0x38);
	Delay1ms(2);
	WriteInstruction(LCD_DISPLAY_ON|LCD_CURSOR_OFF|LCD_CURSOR_BLINK_OFF);  //��ʾģʽ���ã���ʾ�����޹�꣬�޹����˸
	Delay1ms(2);
	WriteInstruction(0x06);  //��ʾģʽ���ã�������ƣ��ַ�����
	Delay1ms(2);
	WriteInstruction(LCD_CLEAR_SCREEN);  //����Ļָ�����ǰ����ʾ�������
	Delay1ms(2);
}
/*************************************************************
 ��ʾ��ʼ������ʾ�˵�
 *************************************************************/
void DisMenuInit(void)
{
	/*LcdInitiate();         //����LCD��ʼ������  */
	/*Delay1ms(2);*/
	/*WriteInstruction(0x01);//����ʾ������Ļָ��*/
	unsigned int i=0;
	WriteAddress(0x00);  // ������ʾλ��Ϊ��һ�еĵ�1����
	while(*str_time != '\0')
	{
		WriteData(*str_time);
		str_time++;
		i++;
	}
	str_time = str_time - i;
	i = 0;
	WriteAddress(0x09);
	while(*str_run != '\0'){
		WriteData(*str_run);
		str_run++;
		i++;
	}
	str_run = str_run - i;
	i = 0;
	WriteAddress(0x40);
	while(*str_coins != '\0'){
		WriteData(*str_coins);
		str_coins++;
		i++;
	}
	str_coins = str_coins - i;
	i = 0;
	WriteAddress(0x49);
	while(*str_bottle != '\0'){
		WriteData(*str_bottle);
		str_bottle++;
		i++;
	}
	str_bottle = str_bottle - i;
}

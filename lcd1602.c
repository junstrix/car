#include <REGX52.h>
#include <intrins.h>  //包含_nop_()函数定义的头文件
#include "LCD1602.h"

unsigned char *str_time = "Time:"; //显示字符菜单   
unsigned char *str_run = "Run:";
unsigned char *str_coins = "Coin:";
unsigned char *str_bottle = "Bot:";
unsigned char Nchar[]=" "; //空字符
unsigned char digit[]={"0123456789"}; //定义字符数组显示数字

/*****************************************************
  函数功能：延时若干毫秒
  入口参数：n
 ***************************************************/
void Delay1ms(unsigned int i)      //延时程序,i是形式参数
{
	unsigned int j;
	for( ;i>0;i--)             //变量i由实际参数传入一个值,因此i不能赋初值
		for(j=0;j<125;j++)
			;
}

/*****************************************************
  函数功能：判断液晶模块的忙碌状态
  返回值：result。result=1，忙碌;result=0，不忙
 ***************************************************/
unsigned char BusyTest(void)
{
	bit result;
	LCD_RS=0;       //根据规定，RS为低电平，RW为高电平时，可以读状态
	LCD_RW=1;
	LCD_EN=1;        //E=1，才允许读写
	_nop_();   //空操作
	_nop_();
	_nop_(); 
	_nop_();   //空操作四个机器周期，给硬件反应时间	
	result=LCD_BUSY;  //将忙碌标志电平赋给result
	LCD_EN=0;
	return result;
}
/*****************************************************
  函数功能：将模式设置指令或显示地址写入液晶模块
  入口参数：dictate
 ***************************************************/
void WriteInstruction (unsigned char dictate)
{   
	while(BusyTest()==1); //如果忙就等待
	LCD_RS=0;                  //根据规定，RS和R/W同时为低电平时，可以写入指令
	LCD_RW=0;   
	LCD_EN=0;                   //E置低电平(根据表8-6，写指令时，E为高脉冲，
	// 就是让E从0到1发生正跳变，所以应先置"0"
	_nop_();
	_nop_();             //空操作两个机器周期，给硬件反应时间
	LCDIO=dictate;            //将数据送入P0口，即写入指令或地址
	_nop_();
	_nop_();
	_nop_();
	_nop_();               //空操作四个机器周期，给硬件反应时间
	LCD_EN=1;                   //E置高电平
	_nop_();
	_nop_();
	_nop_();
	_nop_();               //空操作四个机器周期，给硬件反应时间
	LCD_EN=0;                  //当E由高电平跳变成低电平时，液晶模块开始执行命令
}
/*****************************************************
  函数功能：指定字符显示的实际地址
  入口参数：x
 ***************************************************/
void WriteAddress(unsigned char x)
{
	WriteInstruction(x|0x80); //显示位置的确定方法规定为"80H+地址码x"
}
/*****************************************************
  函数功能：将数据(字符的标准ASCII码)写入液晶模块
  入口参数：y(为字符常量)
 ***************************************************/
void WriteData(unsigned char y)
{
	while(BusyTest()==1);  
	LCD_RS=1;           //RS为高电平，RW为低电平时，可以写入数据
	LCD_RW=0;
	LCD_EN=0;            //E置低电平(根据表8-6，写指令时，E为高脉冲，
	// 就是让E从0到1发生正跳变，所以应先置"0"
	LCDIO=y;           //将数据送入P0口，即将数据写入液晶模块
	_nop_();
	_nop_();
	_nop_();
	_nop_();       //空操作四个机器周期，给硬件反应时间
	LCD_EN=1;          //E置高电平
	_nop_();
	_nop_();
	_nop_();
	_nop_();        //空操作四个机器周期，给硬件反应时间
	LCD_EN=0;            //当E由高电平跳变成低电平时，液晶模块开始执行命令
}
/*清空菜单显示变量的*/
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
  显示一个变量的值,运算量过大可能出现问题
  第一个参数为显示地址，第二参数为显示变量
 **********************************************/
void WriteVarData(unsigned char addr, unsigned int x)
{
	unsigned char D1,D2,D3,D4,D5;
	WriteInstruction(addr|0x80); //写入数据显示地址
	D1=x%10;             //模拟数据采集 D1=x%10;              //计算个位数字
	D2=(x%100)/10;        //计算十位数字
	D3=(x%1000)/100;      //计算百位数字
	D4=(x%10000)/1000;    //计算千位数字
	D5=x/10000;            //计算万位数字
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
  函数功能：对LCD的显示模式进行初始化设置
 ***************************************************/
void LcdInitiate(void)
{
	Delay1ms(5);             //延时15ms，首次写指令时应给LCD一段较长的反应时间
	WriteInstruction(0x38);  //显示模式设置：16×2显示，5×7点阵，8位数据接口
	Delay1ms(2);   //延时5ms　
	WriteInstruction(0x38);
	Delay1ms(2);
	WriteInstruction(0x38);
	Delay1ms(2);
	WriteInstruction(LCD_DISPLAY_ON|LCD_CURSOR_OFF|LCD_CURSOR_BLINK_OFF);  //显示模式设置：显示开，无光标，无光标闪烁
	Delay1ms(2);
	WriteInstruction(0x06);  //显示模式设置：光标右移，字符不移
	Delay1ms(2);
	WriteInstruction(LCD_CLEAR_SCREEN);  //清屏幕指令，将以前的显示内容清除
	Delay1ms(2);
}
/*************************************************************
 显示初始化，显示菜单
 *************************************************************/
void DisMenuInit(void)
{
	/*LcdInitiate();         //调用LCD初始化函数  */
	/*Delay1ms(2);*/
	/*WriteInstruction(0x01);//清显示：清屏幕指令*/
	unsigned int i=0;
	WriteAddress(0x00);  // 设置显示位置为第一行的第1个字
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

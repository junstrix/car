#define uint unsigned int
#define uchar unsigned char

#define MOTOR_R1 P2_0 //电机接口
#define MOTOR_R2 P2_1
#define MOTOR_L1 P2_2
#define MOTOR_L2 P2_3
#define TRACK1 P1_0 //传感器接口
#define TRACK2 P1_1
#define TRACK3 P1_2
#define TRACK4 P1_3
#define COIN_IO P1_4 //硬币接口
#define BOTTLE_IO_H P1_5 //瓶子接口(上)
#define BOTTLE_IO_L P1_6 //瓶子接口(下)
#define BUZZER P1_7 //蜂鸣器接口
#define WARNING_LED P3_0 //警示LED灯

#define NoBlockLine (TRACK1==1&&TRACK2==1&&TRACK3==1&&TRACK4==1) ||\
			    (TRACK1==0&&TRACK2==0&&TRACK3==0&&TRACK4==0)   //同时检测到白线或黑线
#define DeviateRightTrack TRACK1==1&&TRACK2==1&&TRACK3==0&&TRACK4==1 //车微右斜
#define DeviateLeftTrack TRACK1==1&&TRACK2==0&&TRACK3==1&&TRACK4==1 //车微左斜
#define CarTurnLeft (TRACK1==1&&TRACK2==1&&TRACK3==0&&TRACK4==0) ||\  
			    (TRACK1==1&&TRACK2==0&&TRACK3==0&&TRACK4==0)//遇到左转弯
#define CarTurnRight (TRACK1==0&&TRACK2==0&&TRACK3==1&&TRACK4==1) ||\
			     (TRACK1==0&&TRACK2==0&&TRACK3==0&&TRACK4==1)//遇到右转弯
#define CHECK_COIN (COIN_IO==0)//检测有硬币
#define NoBottle (BOTTLE_IO_H==1&&BOTTLE_IO_L==1)//没有瓶子
#define UpBottle (BOTTLE_IO_H==0&&BOTTLE_IO_L==0) //正立瓶子
#define DownBottle (BOTTLE_IO_H==0&&BOTTLE_IO_L==1) //倒立瓶子

extern void mo_forword(void);
extern void mo_back(void);
extern void mo_stop(void);
extern void mo_right(void);
extern void mo_left(void);
extern void Con_ZKB(unsigned int a, unsigned int b,\
		unsigned int c, unsigned int d);
extern void mo_R_forword(void);
extern void mo_L_forword(void);
extern void buzzer_led(unsigned char a);

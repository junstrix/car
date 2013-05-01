#define uint unsigned int
#define uchar unsigned char

#define MOTOR_R1 P1_0 //电机接口
#define MOTOR_R2 P1_1
#define MOTOR_L1 P1_2
#define MOTOR_L2 P1_3

#define TRACK1 P2_4 //传感器接口
#define TRACK2 P2_5
#define TRACK3 P2_6
#define TRACK4 P2_7

#define NoBlockLine TRACK1==1&&TRACK2==1&&TRACK3==1&&TRACK4==1 //没有检测到黑线
#define DeviateRightTrack TRACK1==1&&TRACK2==1&&TRACK3==0&&TRACK4==1 //偏离右轨道
#define DeviateLeftTrack TRACK1==1&&TRACK2==0&&TRACK3==1&&TRACK4==1 //偏离左轨道
#define CarTurnLeft TRACK1==1&&TRACK2==1&&TRACK3==0&&TRACK4==0 //检测到左转角
#define CarTurnRight TRACK1==0&&TRACK2==0&&TRACK3==1&&TRACK4==1 //检测到右转角

extern void mo_forword(void);
extern void mo_back(void);
extern void mo_stop(void);
extern void mo_right(void);
extern void mo_mic_right(void);
extern void mo_left(void);
extern void mo_mic_left(void);
extern void Con_ZKB(unsigned int a, unsigned int b,\
		unsigned int c, unsigned int d);

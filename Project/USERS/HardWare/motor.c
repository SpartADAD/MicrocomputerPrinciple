/****************************motor.c********************************/
#include "motor.h"
#include "gpio.h"
#include "STC15F2K60S2.h"
#include "math.h"
#include "main.h"
#include "delay.h"
#include "82c55.h"

#define CLOCK_WISE		        1
#define COUNTER_CLOCK_WISE		0

void MotorControl(void)
{
	uint32_t xdata vel = 0;
	vel=10+((MOTOR_VEL_HIGH<<1)|MOTOR_VEL_LOW)*30;
	
	if(MOTOR_SWITCH)
	{
		if(MOTOR_ROTATE_DIRECTION)
		{
			MotorRotate(CLOCK_WISE,vel);
		}
		else
		{
			MotorRotate(COUNTER_CLOCK_WISE,vel);	
		}
	}
}
#define SEQUENCE    4
void MotorRotate(uint8_t rotateDirection,uint32_t rotateVel)
{
	uint8_t xdata sequence=0;
	uint8_t xdata myCode=0;
	if(rotateDirection)
	{
		for(sequence = 0; sequence<SEQUENCE;sequence++)
		{
			myCode=pow(2,sequence);
			
			P1=myCode;
			DelayMs(rotateVel);
			
			myCode=myCode|(myCode<<1);
			if(myCode>0x0f)
			{
				myCode=0x09;
			}
			
			P1=myCode;
			DelayMs(rotateVel);
		}
	}
	else
	{
		for(sequence = SEQUENCE-1; sequence>0;sequence--)
		{
			myCode=pow(2,sequence);
			
			P1=myCode;
			DelayMs(rotateVel);
			
			myCode=myCode|(myCode>>1);
			if(myCode==0x01)
			{
				myCode=0x09;
			}
			
			P1=myCode;
			DelayMs(rotateVel);
		}
	}

}
/*** @brief  电机旋转
			timeControl是半个周期的时间2.5ms*400 =1s
			静态变量runTime用来计数 计算运行时间 由于本函数是2.5ms运行1次所以当runTime运行等于2倍的timeControl相当于1个周期=2s
runtime<=timeControl时电机顺时针 timeControl<runTime<=2*timeControl另外半个周期让电机逆时针
			runStep是控制通电相序，通过传入序号控制电机相序通电（由82C55 A0 A1 A2 A3控制）
			通过读取82C55 B1 B0读取开关去控制电机转速rotateVel由1-4 每次相当于增加2.5ms延时 
  * @param  void           
  * @retval None
  */

#define MOTOR_VEL_HIGH_C55 PORTx_ReadBits(PORT_B,PORT_PIN_1)
#define MOTOR_VEL_LOW_C55 PORTx_ReadBits(PORT_B,PORT_PIN_0)

void MotorRotateByTIM(void)
{
	uint8_t xdata myCode[8]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09};
	uint16_t xdata timeControl=400;
	uint16_t xdata rotateVel=1+((MOTOR_VEL_HIGH_C55<<1)|MOTOR_VEL_LOW_C55);
	static  uint8_t xdata rotateDirection=CLOCK_WISE;
	static uint32_t xdata runTime=0;
	static uint16_t xdata rotateVelTime=0;
	static char xdata runStep =0;
	runTime++;
	rotateVelTime++;
	
	if(runTime<=timeControl)
	{
		rotateDirection = CLOCK_WISE;
	}
	else if(runTime>timeControl&&runTime<=2*timeControl)
	{
		rotateDirection = COUNTER_CLOCK_WISE;
	}
	else if(runTime>2*timeControl)
	{
		runTime=0;
		rotateDirection = CLOCK_WISE;
	}
	
	if(rotateVelTime>=rotateVel)
	{
		rotateVelTime = 0;
		if(rotateDirection)
		{
			runStep++;
			if(runStep>=8)
				runStep=0;
		}
		else
		{
			runStep--;
			if(runStep<0)
				runStep=7;
		}
	}
	
	P8255_A = myCode[runStep];
}


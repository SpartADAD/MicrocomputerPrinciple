/****************************motor.c********************************/
#include "motor.h"
#include "gpio.h"
#include "STC15F2K60S2.h"
#include "math.h"
#include "main.h"
#include "delay.h"
/*顺时针*/
#define CLOCK_WISE		        1
/*逆时针*/
#define COUNTER_CLOCK_WISE		0
/**
  * @brief  电机运动函数
  * @param  vel 延时时间控制电机旋转速度
  * @retval void
  */
void MotorControl(void)
{
	uint32_t xdata vel = 0;
	vel=10+((MOTOR_VEL_HIGH<<1)|MOTOR_VEL_LOW)*30;
	
	/*电机是否启动*/
	if(MOTOR_SWITCH)
	{
		/*电机旋转方向控制*/
		if(MOTOR_ROTATE_DIRECTION)
		{
			/*电机顺时针旋转*/
			MotorRotate(CLOCK_WISE,vel);
		}
		else
		{
			/*电机逆时针旋转*/
			MotorRotate(COUNTER_CLOCK_WISE,vel);	
		}
	}
}
/*电机的相数*/
#define SEQUENCE    4
/**
  * @brief  电机旋转函数 通过计算由于通电顺序是A AB这样的，由真值表可知
可视为4次循环，不过在最后一次循环的时候情况特殊
需要判断，特殊处理赋值,用 
  * @param  rotateDirection：电机旋转方向
  * @param  rotateVel: 通过延时时间，传入DelayMs()控制电机的速度
	* @param  myCode变量是个人解算的电机输出控制直接赋予P1口数值
  * @retval void
  */
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
			/*特殊处理赋值*/
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
			/*特殊处理赋值*/
			if(myCode==0x01)
			{
				myCode=0x09;
			}
			
			P1=myCode;
			DelayMs(rotateVel);
		}
	}

}

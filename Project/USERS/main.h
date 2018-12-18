/****************************main.h***********************************/
#ifndef __MAIN_H
#define __MAIN_H

#include "STC15F2K60S2.h"
#include <intRIns.h>
#include <ABSACC.h>
#include <math.h>
#include <stdio.h>
/*定义使用哪个定时器控制5ms运行周期*/
#define RUN_PERIOD_BY_TIM   FIVE_MS_RUN_BY_TIM0
/*定义5ms运行周期通过定时器0*/
#define FIVE_MS_RUN_BY_TIM0         0
/*定义5ms运行周期通过定时器1*/
#define FIVE_MS_RUN_BY_TIM1         1
/*一次中断为250微秒*/
#define ONE_INTTEUPT_TIME           250
/*TIM0周期为250微秒进一次中断   20次为5ms  5000*/
#define PERIOD_RUN      ((int)(5000/(MACHINE_PEROID*ONE_INTTEUPT_TIME)))

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

//系统时钟定义 12M HZ
#define  SYSCLK 	12000000

//机器周期   1us
#define MACHINE_PEROID (int)(12.0f/(float)(SYSCLK/1000000))


//圆周率宏定义
#define PI (3.1415926f)

typedef struct{
		uint8_t flag;
		uint8_t receiveDataByUsart;
		uint8_t c55LedMode;


}gParam_t;
	
	
extern gParam_t gParam;



//状态位枚举类型定义
typedef enum {RESET = 0, SET = 1} FlagStatus, ITStatus;
//使能失能状态枚举类型定义
typedef enum {disable = 0, enable}FunctionalState_t;





#endif
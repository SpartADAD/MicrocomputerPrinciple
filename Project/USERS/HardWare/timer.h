/***********************gpio.h************************/

#ifndef __TIMER_H
#define __TIMER_H

#include "main.h"

#define THIRTEEN_BIT_COUNT                0 
#define	SIXTEEN_BIT_COUNT                 1
#define	EIGHT_BIT_AUTO_RELOUD_COUNT       2
#define	TWO_EIGHT_BIT_COUNT               3

void TIM0_Init(uint16_t workMode,uint16_t timerStartValue);
void TIM1_Init(uint16_t workMode,uint16_t timerStartValue);
#endif

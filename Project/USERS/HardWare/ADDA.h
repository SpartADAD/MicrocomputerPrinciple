/*************************ADDA.h********************************/
#ifndef __ADDA_H
#define __ADDA_H

#include "main.h"

#define ADDA_EXP  DAC_EXP
#define ADC_EXP   1
#define DAC_EXP   2

void LedShow(void);
void AdcHD7279Show(void);
void AdcInit(void);
uint8_t GetAdcValue(void);
void ShowVoltage(void);

void DacOUT(void);





#endif
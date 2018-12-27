/*************************ADDA.h********************************/
#ifndef __ADDA_H
#define __ADDA_H

#include "main.h"
/*通过预编译宏选择实ADC和DAC实验下载*/
#define ADDA_EXP  ADC_EXP
#define ADC_EXP   1
#define DAC_EXP   2

void LedShow(void);
void AdcHD7279Show(void);
void AdcInit(void);
uint8_t GetAdcValue(void);
void ShowVoltage(void);

void DacOUT(void);





#endif
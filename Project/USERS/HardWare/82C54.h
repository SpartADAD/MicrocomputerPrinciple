/*************************82C55.h********************************/
#ifndef __82C54_H
#define __82C54_H

#include "main.h"
/*通过预编译宏进行编译下载操作*/
#define C54_EXPERIMENT_1     1
#define C54_EXPERIMENT_2     2
#define C54_EXPERIMENT_3     3

#define C54_EXPERIMENT   C54_EXPERIMENT_1




#define COUNT_0    0
#define COUNT_1    1
#define COUNT_2    2


#define INTERRUPT_MODE    0
#define MONOSTABLE_TRIGGER_MODE	    1
#define FREQUENCY_DIVISION_MODE   2
#define SQUARE_WAVE_MODE    3
#define SOFTWARE_GATING_SINGAL_GENERATOR_MODE    4
#define HARDWARE_GATING_SINGAL_GENERATOR_MODE    5

#define BINARY_COUNT 0
#define BCD_COUNT    1

void Init_82C54(uint8_t count_x, uint8_t counterMode, uint16_t countTime,uint8_t codeMode);
void EXInterruptLed(void);
void MyExperiment82C54(void);
void My82C54Init(void);
void ShowCountTime(void);
void DiffFangBo(void);
#endif
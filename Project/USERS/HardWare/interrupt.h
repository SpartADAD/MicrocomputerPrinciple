/***********************gpio.h************************/

#ifndef __INTERRUPT_H
#define __INTERRUPT_H


#define EX_INTERRUPT0    0
#define EX_INTERRUPT1    1

#define EX_INTERRUPT_BY_LOW_LEVEL    0
#define EX_INTERRUPT_BY_EDGE         1

uint8_t GetRunFlag(void);

void EXHandlerInit(uint8_t EXNumber,uint8_t workMode);
void Interrupt_Priority(uint8_t priority);

#endif

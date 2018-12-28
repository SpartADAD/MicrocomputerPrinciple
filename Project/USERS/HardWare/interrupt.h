/***********************interrupt.h************************/

#ifndef __INTERRUPT_H
#define __INTERRUPT_H

/*外部中断0*/
#define EX_INTERRUPT0    0
/*外部中断1*/
#define EX_INTERRUPT1    1
/*外部中断低电平触发*/
#define EX_INTERRUPT_BY_LOW_LEVEL    0
/*外部中断边沿触发*/
#define EX_INTERRUPT_BY_EDGE         1

uint8_t GetRunFlag(void);

void EXHandlerInit(uint8_t EXNumber,uint8_t workMode);
void Interrupt_Priority(uint8_t priority);

#define LEFT_TO_RIGHT 0
#define RIGHT_TO_LEFT 1

#endif

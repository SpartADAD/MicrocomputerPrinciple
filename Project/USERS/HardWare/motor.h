/***********************motor.h************************/

#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
/*控制电机启动*/
#define MOTOR_SWITCH GPIOx_ReadBits(GPIOP3,GPIO_PIN_2)
/*控制电机旋转方向*/
#define MOTOR_ROTATE_DIRECTION GPIOx_ReadBits(GPIOP3,GPIO_PIN_3)
/*控制电机速度高位*/
#define MOTOR_VEL_HIGH GPIOx_ReadBits(GPIOP3,GPIO_PIN_4)
/*控制电机速度低位*/
#define MOTOR_VEL_LOW GPIOx_ReadBits(GPIOP3,GPIO_PIN_5)

void MotorRotate(uint8_t rotateDirection,uint32_t rotateVel);
void MotorControl(void);
#endif

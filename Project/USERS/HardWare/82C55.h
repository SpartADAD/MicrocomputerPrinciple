/*************************82C55.h********************************/
#ifndef __82C55_H
#define __82C55_H

#include "main.h"
#define GROUP_A   0
#define GROUP_B   1


#define PORT_A				0
#define PORT_B				1
/*C口高四位PC7-PC4和PORT_A组成A组*/
#define PORT_C_HIGH   2
/*C口低四位PC3-PC0和PORT_B组成B组*/
#define PORT_C_LOW		3


void C55_Init(uint8_t group,uint8_t groupWorkMode,uint8_t Port,uint8_t PortInOrOut);



#endif
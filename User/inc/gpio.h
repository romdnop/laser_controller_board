#ifndef _GPIO_H
#define _GPIO_H
#include "stm8s.h"
#include "tim4.h"
void HW_GPIO_Init(void);

uint8_t saved_led_map = 0;

#endif
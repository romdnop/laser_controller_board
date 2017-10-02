#ifndef _TIM2_H
#define _TIM2_H
#include "stm8s.h"

extern volatile uint16_t tim2_cycles_count;

void TIM2_init(void);
void TIM2_Stop(void);
void TIM2_Start(void);

#endif
#ifndef _TIM4_H
#define _TIM4_H
#include "stm8s.h"

#define TIMER_PERIOD (uint8_t)0xFF
//extern volatile uint8_t timer_phase;
extern volatile uint8_t tim4_cycles_count;


void TIM4_init(void);

#endif
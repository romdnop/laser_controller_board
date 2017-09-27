#ifndef _TIM4_H
#define _TIM4_H
#include "stm8s.h"

#define TIMER_PERIOD 128
extern volatile uint8_t timer_phase;
extern volatile uint8_t cycles_count;
#endif
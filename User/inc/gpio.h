#ifndef _GPIO_H
#define _GPIO_H
#include "stm8s.h"
#include "tim4.h"

#define OUT_PORT        GPIOC
#define OUT1_PIN        GPIO_PIN_3
#define OUT2_PIN        GPIO_PIN_4
#define OUT3_PIN        GPIO_PIN_6
#define OUT4_PIN        GPIO_PIN_7

#define BUZER_PORT      GPIOC
#define BUZER_PIN       GPIO_PIN_5

void HW_GPIO_Init(void);


extern uint8_t saved_led_map;




#endif
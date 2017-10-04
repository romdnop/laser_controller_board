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

#define HEELING_PORT    GPIOD
#define HEELING_PIN     GPIO_PIN_4



#define LED_PORT        GPIOD
#define LED_PIN         GPIO_PIN_5

void HW_GPIO_Init(void);
void HW_GPIO_Set(uint8_t map,uint8_t mask);

extern uint8_t saved_led_map;




#endif
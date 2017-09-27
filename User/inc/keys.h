#ifndef _KEYS_H
#define _KEYS_H
#include "stm8s.h"
#include "stm8s_gpio.h"

#define KEY_V_PORT      GPIOA
#define KEY_V_PIN       GPIO_PIN_2

#define KEY_H_PORT      GPIOD
#define KEY_H_PIN       GPIO_PIN_6

typedef enum
{
  KEY_V,
  KEY_H,
  KEY_NO
}KEY_Code;

void KEYS_Init(void);
KEY_Code KEYS_CheckPress(void);

#endif
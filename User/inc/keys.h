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
  KEY_NO = 0,
  KEY_V,
  KEY_H
}KEY_Code;

typedef enum
{
  KEYS_FIRST_CHECK,
  KEYS_TIMER_START,
  KEYS_TIMER_CHECK,
  KEYS_EXIT 
}KEYS_StatesTypeDef;

typedef struct
{
  KEY_Code lastCode;
  KEY_Code currentCode;
  KEY_Code tempCode;
  uint8_t vPressCount;
  uint8_t hPressCount;
  KEYS_StatesTypeDef state;
}KEY_TypeDefStruct;


void KEYS_Init(void);
KEY_Code KEYS_CheckPress(void);

void KEYS_Reset(KEY_TypeDefStruct *keys);
void KEYS_Proceed(KEY_TypeDefStruct *keys, uint8_t *mask);
uint8_t KEYS_Execute(KEY_TypeDefStruct *keys);

#endif
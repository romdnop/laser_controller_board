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
  IDLE,
  START,
  FIRST_CHECK,
  SECOND_CHECK,
  EXIT
}KEY_StatesStruct;



typedef struct
{
  KEY_Code code;
  KEY_Code lastPressedCode;
  uint8_t pressCount;
  KEY_StatesStruct state;
  volatile uint8_t *pauseCycles;
  //uint8_t lastCyclesCount;
}KEY_TypeDefStruct;

void KEYS_Init(void);
KEY_Code KEYS_CheckPress(void);


void KEYS_DeInit(KEY_TypeDefStruct *keysStruct);
void KEYS_Start(KEY_TypeDefStruct *keysStruct);
void KEYS_Reload(KEY_TypeDefStruct *keysStruct);
KEY_Code KEYS_Execute(KEY_TypeDefStruct *keysStruct);


#endif
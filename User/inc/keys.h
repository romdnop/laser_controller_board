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
  KEY_Code localFirstCode;
  KEY_Code localSecondCode;
  KEY_Code globalLastCode;
  uint8_t globalPressCount;

  KEY_StatesStruct state;
  volatile uint8_t *pauseCycles;
}KEY_TypeDefStruct;



typedef enum
{
  CHECK1,
  TIMER_START,
  TIMER_CHECK,
  KEYS_EXIT 
}KEYS2_StatesTypeDef;

typedef struct
{
  KEY_Code lastCode;
  KEY_Code currentCode;
  KEY_Code tempCode;
  uint8_t vPressCount;
  uint8_t hPressCount;
  KEYS2_StatesTypeDef state;
}KEY2_TypeDefStruct;


void KEYS_Init(void);
KEY_Code KEYS_CheckPress(void);


void KEYS_DeInit(KEY_TypeDefStruct *keysStruct);
void KEYS_Start(KEY_TypeDefStruct *keysStruct);
void KEYS_Reload(KEY_TypeDefStruct *keysStruct);
KEY_Code KEYS_Execute(KEY_TypeDefStruct *keysStruct);


void KEYS2_Reset(KEY2_TypeDefStruct *keys);
void KEYS2_Proceed(KEY2_TypeDefStruct *keys, uint8_t *mask);
uint8_t KEYS2_Execute(KEY2_TypeDefStruct *keys);

#endif
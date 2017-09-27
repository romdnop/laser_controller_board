#include "keys.h"
#include "tim4.h"

//Input, pull-up
void KEYS_Init(void)
{
  GPIO_DeInit(KEY_V_PORT);
  GPIO_DeInit(KEY_H_PORT);
  
  GPIO_Init(KEY_V_PORT,KEY_V_PIN, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(KEY_H_PORT,KEY_H_PIN, GPIO_MODE_IN_PU_NO_IT);
}


KEY_Code KEYS_CheckPress(void)
{
  if(!(KEY_V_PORT->IDR & KEY_V_PIN))//check press1
  {                                 //return key_code
      return KEY_V;
  }
  if(!(KEY_H_PORT->IDR & KEY_H_PIN))//check press1
  {                                 //return key_code
      return KEY_H;
  }
  return KEY_NO;
}


void KEYS_DeInit(KEY_TypeDefStruct *keysStruct)
{
  keysStruct->localFirstCode = KEY_NO;
  keysStruct->localSecondCode = KEY_NO;
  keysStruct->globalLastCode = KEY_NO;
  
  keysStruct->state = IDLE;
  keysStruct->pauseCycles = &cycles_count;
  *keysStruct->pauseCycles = 0;

  keysStruct->globalPressCount = 0;
}


void KEYS_Start(KEY_TypeDefStruct *keysStruct)
{
  keysStruct->state = IDLE;
}


void KEYS_Reload(KEY_TypeDefStruct *keysStruct)
{
  KEYS_DeInit(keysStruct);
  KEYS_Start(keysStruct);
}


KEY_Code KEYS_Execute(KEY_TypeDefStruct *keysStruct)
{
  if(keysStruct->state == IDLE)
  {
    return KEY_NO;
  }
  switch(keysStruct->state)
  {
    case START:
      if(keysStruct->globalPressCount > 2)
      {
        keysStruct->globalPressCount = 0;
      }
      keysStruct->state++;
    case FIRST_CHECK:
      keysStruct->localFirstCode = KEYS_CheckPress();
      if(keysStruct->localFirstCode != KEY_NO)
      {
        *keysStruct->pauseCycles = 0;
        keysStruct->state++;
      }
      return KEY_NO;
    case SECOND_CHECK:
      keysStruct->localSecondCode = KEYS_CheckPress();
      if(*keysStruct->pauseCycles > 3)
      {
        if(keysStruct->localSecondCode == keysStruct->localFirstCode)
        {
          if(keysStruct->globalLastCode == keysStruct->localSecondCode)
          {
            keysStruct->globalPressCount++;
          }
          keysStruct->globalLastCode = keysStruct->localSecondCode;
          keysStruct->state++;
        }
        keysStruct->localFirstCode = KEY_NO;
        keysStruct->localSecondCode = KEY_NO;
        keysStruct->state = START; //need prepare after local reset
      }
      return KEY_NO;
    case EXIT:
      return keysStruct->globalLastCode;
  }
  return KEY_NO;
}

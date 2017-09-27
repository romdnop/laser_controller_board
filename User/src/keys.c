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
  keysStruct->code = KEY_NO;
  keysStruct->state = IDLE;
  keysStruct->pauseCycles = &cycles_count;
  *keysStruct->pauseCycles = 0;
  //keysStruct->lastCyclesCount = 0;
  keysStruct->lastPressedCode = KEY_NO;
  keysStruct->pressCount = 0;
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
      keysStruct->code = KEYS_CheckPress();
      if(keysStruct->code != KEY_NO)
      {
        keysStruct->state++;
        *keysStruct->pauseCycles = 0;
        return KEY_NO;
      }
    case FIRST_CHECK:
      if( *keysStruct->pauseCycles < 3)
      {
        return KEY_NO;
      }
      keysStruct->code = KEYS_CheckPress();
      if(keysStruct->code != KEY_NO)
      {
        keysStruct->state++;
      }
    case SECOND_CHECK:
    
    case EXIT:
      return keysStruct->code;
  }
  return KEY_NO;
}

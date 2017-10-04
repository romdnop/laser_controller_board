#include "keys.h"
#include "tim4.h"
#include "gpio.h"

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



void KEYS_Reset(KEY_TypeDefStruct *keys)
{
  keys->currentCode = KEY_NO;
  keys->lastCode = KEY_NO;
  keys->tempCode = KEY_NO;
  keys->vPressCount = 0;
  keys->hPressCount = 0;
}



void KEYS_Proceed(KEY_TypeDefStruct *keys, uint8_t *mask)
{
  keys->lastCode = keys->currentCode;

  //output proceed
  if(keys->lastCode == KEY_V)
  {
    keys->vPressCount++;
    if(keys->vPressCount>2)
    {
      keys->vPressCount=0;
    }
    
    if(keys->vPressCount & 1)
    {
      *mask |= 1;
    }
    
    if(keys->vPressCount & 2)
    {
      *mask |= 2;
    }
    if(!keys->vPressCount)
    {
      *mask &= ~3;
    }
  }
  
  if(keys->lastCode == KEY_H)
  {
    keys->hPressCount++;
    if(keys->hPressCount>2)
    {
      keys->hPressCount=0;
    }
    
    if(keys->hPressCount & 1)
    {
      *mask |= 4;
    }
    
    if(keys->hPressCount & 2)
    {
      *mask |= 8;
    }
    if(!keys->hPressCount)
    {
      *mask &= ~12;
    }

  }
}



uint8_t KEYS_Execute(KEY_TypeDefStruct *keys)
{

  switch(keys->state)
  {
    case KEYS_FIRST_CHECK:
      keys->tempCode =  KEYS_CheckPress();
      if(keys->tempCode != KEY_NO)
      {
        keys->state = KEYS_TIMER_START;
        return 0;
      }
      return 0;
    case KEYS_TIMER_START:
      tim4_cycles_count = 0;
      keys->state = KEYS_TIMER_CHECK;
      return 0;
    case KEYS_TIMER_CHECK:
      if(tim4_cycles_count > 80)
      {
        keys->currentCode = KEYS_CheckPress();
        if((keys->currentCode == keys->tempCode)&&(keys->currentCode!=KEY_NO))
        {
          keys->state = KEYS_EXIT;
          return 0;
        }
        keys->state = KEYS_FIRST_CHECK;
      }
      return 0;
    case KEYS_EXIT:
      return 1;
    default:
      return 0;
  }
}

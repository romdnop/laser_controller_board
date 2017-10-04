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


void KEYS_DeInit(KEY_TypeDefStruct *keysStruct)
{
  keysStruct->localFirstCode = KEY_NO;
  keysStruct->localSecondCode = KEY_NO;
  keysStruct->globalLastCode = KEY_NO;
  
  keysStruct->state = IDLE;
  keysStruct->pauseCycles = &tim4_cycles_count;
  *keysStruct->pauseCycles = 0;

  keysStruct->globalPressCount = 0;
}


void KEYS_Start(KEY_TypeDefStruct *keysStruct)
{
  keysStruct->state = START;
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
      GPIOC->ODR ^= GPIO_PIN_3;
      return keysStruct->globalLastCode;
  }
  return KEY_NO;
}



uint8_t KEYS_Proceed(KEY_TypeDefStruct *keysStruct)
{
  if(keysStruct->globalLastCode == KEY_V)
  {
    switch(keysStruct->globalPressCount)
    {
      case 1:
        //
        KEYS_Reload(keysStruct);
        return 1;
      case 2:
        //
        KEYS_Reload(keysStruct);
        return 1;
      default:
        KEYS_Reload(keysStruct);
        return 0;
    }
  }
  if(keysStruct->globalLastCode == KEY_H)
  {
    switch(keysStruct->globalPressCount)
    {
      case 1:
        //
        KEYS_Reload(keysStruct);
        return 1;
      case 2:
        //
        KEYS_Reload(keysStruct);
        return 1;
      default:
        KEYS_Reload(keysStruct);
        return 0;
    }
  }
  KEYS_Reload(keysStruct);
  return 0;
}


void KEYS2_Reset(KEY2_TypeDefStruct *keys)
{
  keys->currentCode = KEY_NO;
  keys->lastCode = KEY_NO;
  keys->tempCode = KEY_NO;
  keys->vPressCount = 0;
  keys->hPressCount = 0;
  //keys->state = CHECK1;
}



void KEYS2_Proceed(KEY2_TypeDefStruct *keys, uint8_t *mask)
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



uint8_t KEYS2_Execute(KEY2_TypeDefStruct *keys)
{

  switch(keys->state)
  {
    case CHECK1:
      keys->tempCode =  KEYS_CheckPress();
      if(keys->tempCode != KEY_NO)
      {
        keys->state = TIMER_START;
        return 0;
      }
      return 0;
    case TIMER_START:
      tim4_cycles_count = 0;
      keys->state = TIMER_CHECK;
      return 0;
    case TIMER_CHECK:
      if(tim4_cycles_count > 80)
      {
        keys->currentCode = KEYS_CheckPress();
        if((keys->currentCode == keys->tempCode)&&(keys->currentCode!=KEY_NO))
        {
          keys->state = KEYS_EXIT;
          return 0;
        }
        keys->state = CHECK1;
      }
      return 0;
    case KEYS_EXIT:
      return 1;
    default:
      return 0;
  }
}

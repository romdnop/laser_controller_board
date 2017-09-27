#include "keys.h"


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
  {
    delay_ms(10);//delay 10ms
    if(!(KEY_V_PORT->IDR & KEY_V_PIN))//one more check
    {                                   //return key_code
      return KEY_V;
    }
  }
  if(!(KEY_H_PORT->IDR & KEY_H_PIN))//check press1
  {
    delay_ms(10);//delay 10ms
    if(!(KEY_H_PORT->IDR & KEY_H_PIN))//one more check
    {                                   //return key_code
      return KEY_H;
    }
  }
  return KEY_NO;
}

#include "main.h"

KEY_TypeDefStruct keys;
Beep_StructTypeDef beep;

int main(void)
{
  // ---------- CLK CONFIG -----------------------
  CLK_DeInit();

  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); // set 16 MHz for CPU
  
  TIM2_init();
  
  
  BEEP_StartShortBeep(&beep);
  //TIM2_Stop();
  //TIM2_Start();
  
  
  BEEP_StartZumming(&beep);
  
  KEYS_Reload(&keys);
  
  __enable_interrupt();
  while(1)
  {
    if(KEYS_Execute(&keys) != KEY_NO)
    {
      
    }
    BEEP_Execute(&beep);
  }
}




void assert_failed(uint8_t *file, uint32_t line)
{
  while(1);
}
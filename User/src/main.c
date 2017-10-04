#include "main.h"


Beep_StructTypeDef beep;
KEY_TypeDefStruct keys;
HEEL_StructTypeDef heel;

int main(void)
{
  // ---------- CLK CONFIG -----------------------
  CLK_DeInit();

  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); // set 16 MHz for CPU
  
  TIM2_init();
  TIM4_init();
  TIM1_init();
  
  HW_GPIO_Init();
  BEEP_StartShortBeep(&beep);

  KEYS_Reset(&keys);
  
  /* Define FLASH programming time */
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);

  /* Unlock Data memory */
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  saved_led_map = FLASH_ReadByte(eeprom_address);
  
  HEEL_Reset(&heel);
  BEEP_StartLongBeep(&beep);
  __enable_interrupt();
  while(1)
  {
    if(KEYS_Execute(&keys))
    {
      KEYS_Proceed(&keys, &saved_led_map);
      BEEP_StartShortBeep(&beep);
      
      FLASH_Unlock(FLASH_MEMTYPE_DATA);
      FLASH_ProgramByte(eeprom_address, saved_led_map);
      FLASH_Lock(FLASH_MEMTYPE_DATA);
      
      keys.state = KEYS_FIRST_CHECK;
    }
    
    HW_GPIO_Set(saved_led_map, tim1_mask);
    
    HEEL_Execute(&heel, &beep);
    
    //Check heeling
    /*
    if(!(HEELING_PORT->IDR & HEELING_PIN))
    {
      BEEP_StartZumming(&beep);
    }
    else{
      BEEP_StopZumming(&beep);
    }
    */
    BEEP_Execute(&beep);
  }
}




void assert_failed(uint8_t *file, uint32_t line)
{
  while(1);
}
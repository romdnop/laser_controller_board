#include "main.h"

KEY_TypeDefStruct keys;
Beep_StructTypeDef beep;
KEY2_TypeDefStruct keys2;
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
  //TIM2_Stop();
  //TIM2_Start();
  
  
  //BEEP_StartZumming(&beep);
  
  KEYS_Reload(&keys);
  KEYS2_Reset(&keys2);
  //OUT_PORT->ODR |= OUT1_PIN;
  
  /* Define FLASH programming time */
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);

  /* Unlock Data memory */
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  saved_led_map = FLASH_ReadByte(eeprom_address);
  
  BEEP_StartLongBeep(&beep);
  __enable_interrupt();
  while(1)
  {
    /*
    keys2.tempCode =  KEYS_CheckPress();
    if(keys2.tempCode != KEY_NO)
    {
      delay_ms(80);
      keys2.currentCode = KEYS_CheckPress();
      if((keys2.currentCode == keys2.tempCode)&&(keys2.currentCode!=KEY_NO))
      {
        //unlock eeprom
        //proceed
        KEYS2_Proceed(&keys2, &saved_led_map);
        BEEP_StartShortBeep(&beep);
        //lock eeprom
        //FLASH_Unlock(FLASH_MEMTYPE_DATA);
        //FLASH_ProgramByte(eeprom_address, saved_led_map);
        //FLASH_Lock(FLASH_MEMTYPE_DATA);
      }
    }
    */
    
    
    if(KEYS2_Execute(&keys2))
    {
      KEYS2_Proceed(&keys2, &saved_led_map);
      BEEP_StartShortBeep(&beep);
      //KEYS2_Reset(&keys2);
      
      FLASH_Unlock(FLASH_MEMTYPE_DATA);
      FLASH_ProgramByte(eeprom_address, saved_led_map);
      FLASH_Lock(FLASH_MEMTYPE_DATA);
      
      keys2.state = CHECK1;
    }
    
    HW_GPIO_Set(saved_led_map, tim1_mask);
    
    if(!(HEELING_PORT->IDR & HEELING_PIN))
    {
      BEEP_StartZumming(&beep);
    }
    else{
      BEEP_StopZumming(&beep);
    }

    BEEP_Execute(&beep);
  }
}




void assert_failed(uint8_t *file, uint32_t line)
{
  while(1);
}
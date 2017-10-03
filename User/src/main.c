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
  TIM4_Init();
  
  
  HW_GPIO_Init();
  BEEP_StartShortBeep(&beep);
  //TIM2_Stop();
  //TIM2_Start();
  
  
  BEEP_StartZumming(&beep);
  
  KEYS_Reload(&keys);
  KEYS2_Reset(&keys2);
  //OUT_PORT->ODR |= OUT1_PIN;
  __enable_interrupt();
  while(1)
  {
    //if(KEYS_Execute(&keys) != KEY_NO)
    //{
    //  
    //}
    
    
    
    keys2.tempCode =  KEYS_CheckPress();
    if(keys2.tempCode != KEY_NO)
    {
      delay_ms(120);
      keys2.currentCode = KEYS_CheckPress();
      if((keys2.currentCode == keys2.tempCode)&&(keys2.currentCode!=KEY_NO))
      {
        //unlock eeprom
        //proceed
        KEYS2_Proceed(&keys2, &saved_led_map);
        BEEP_StartShortBeep(&beep);
        //lock eeprom
        
        
        
        
        /*
        if(keys2.currentCode == keys2.lastCode)
        {
          keys2.pressCount++;
        }
        else
        {
          keys2.lastCode = keys2.currentCode;
        }
        if(keys2.pressCount>2)
        {
          KEYS2_Reset(&keys2);
        }
        GPIOC->ODR ^= GPIO_PIN_3;
        */
      }
    }
    HW_GPIO_Set(saved_led_map);
    
    //modulation_funtion
    //need setup tim1 on 8ms period 50% duty
    
    

    //delay_ms(0xFFFF);
    //  GPIOC->ODR ^= GPIO_PIN_3;
    BEEP_Execute(&beep);
  }
}




void assert_failed(uint8_t *file, uint32_t line)
{
  while(1);
}
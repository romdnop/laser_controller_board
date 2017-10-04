#include "gpio.h"
#include "keys.h"

uint8_t saved_led_map = 0;

void HW_GPIO_Init(void)
{
  GPIO_DeInit(OUT_PORT);
  GPIO_DeInit(HEELING_PORT);
  //GPIO_Init(OUT_PORT,output_pins,GPIO_MODE_OUT_PP_LOW_FAST);
  OUT_PORT->ODR = GPIO_ODR_RESET_VALUE; /* Reset Output Data Register */
  OUT_PORT->DDR = GPIO_DDR_RESET_VALUE; /* Reset Data Direction Register */
  OUT_PORT->CR1 = GPIO_CR1_RESET_VALUE; /* Reset Control Register 1 */
  OUT_PORT->CR2 = GPIO_CR2_RESET_VALUE; /* Reset Control Register 2 */
  
  /* Reset corresponding bit to GPIO_Pin in CR2 register */
  OUT_PORT->CR2 &= (uint8_t)(~(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7));
  /* Low level */
  OUT_PORT->ODR &= (uint8_t)(~(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7));
  /* Set Output mode */
  OUT_PORT->DDR |= (uint8_t)(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
  /* Pull-Up or Push-Pull */
  OUT_PORT->CR1 |= (uint8_t)(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
  
  
  
  //Init buttons pins
  GPIO_DeInit(KEY_V_PORT);
  GPIO_DeInit(KEY_H_PORT);
  
  KEY_V_PORT->DDR &= ~KEY_V_PIN;
  KEY_V_PORT->CR1 |= KEY_V_PIN;
  KEY_V_PORT->CR2 &= ~KEY_V_PIN;
    
  KEY_H_PORT->DDR &= ~KEY_H_PIN;
  KEY_H_PORT->CR1 |= KEY_H_PIN;
  KEY_H_PORT->CR2 &= ~KEY_H_PIN;
  
  HEELING_PORT->DDR &= ~HEELING_PIN;
  HEELING_PORT->CR1 |= HEELING_PIN;
  HEELING_PORT->CR2 &= ~HEELING_PIN;
  
  
  LED_PORT->CR2 &= ~LED_PIN;
  LED_PORT->ODR |= LED_PIN;
  LED_PORT->DDR |= LED_PIN;
  LED_PORT->CR1 |= LED_PIN;
}


void HW_GPIO_Set(uint8_t map, uint8_t mask)
{
  if(map & 1 &mask)
  {
    OUT_PORT->ODR |= OUT1_PIN;
  }
  else
  {
    OUT_PORT->ODR &= ~OUT1_PIN;
  }

  if(map & 2 & mask)
  {
    OUT_PORT->ODR |= OUT2_PIN;
  }
  else
  {
    OUT_PORT->ODR &= ~OUT2_PIN;
  }
  
  if(map & 4 & mask)
  {
    OUT_PORT->ODR |= OUT3_PIN;
  }
  else
  {
    OUT_PORT->ODR &= ~OUT3_PIN;
  }
  
  
  if(map & 8 & mask)
  {
    OUT_PORT->ODR |= OUT4_PIN;
  }
  else
  {
    OUT_PORT->ODR &= ~OUT4_PIN;
  }
}



void HW_GPIO_CheckHeeling(void)
{
  
}
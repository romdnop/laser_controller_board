#include "gpio.h"

uint8_t saved_led_map = 0;

void HW_GPIO_Init(void)
{
  GPIO_DeInit(OUT_PORT);
  //GPIO_Init(OUT_PORT,output_pins,GPIO_MODE_OUT_PP_LOW_FAST);
  OUT_PORT->ODR = GPIO_ODR_RESET_VALUE; /* Reset Output Data Register */
  OUT_PORT->DDR = GPIO_DDR_RESET_VALUE; /* Reset Data Direction Register */
  OUT_PORT->CR1 = GPIO_CR1_RESET_VALUE; /* Reset Control Register 1 */
  OUT_PORT->CR2 = GPIO_CR2_RESET_VALUE; /* Reset Control Register 2 */
  
  /* Reset corresponding bit to GPIO_Pin in CR2 register */
  OUT_PORT->CR2 &= (uint8_t)(~(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_5|GPIO_PIN_7));
  /* Low level */
  OUT_PORT->ODR &= (uint8_t)(~(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_5|GPIO_PIN_7));
  /* Set Output mode */
  OUT_PORT->DDR |= (uint8_t)(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_5|GPIO_PIN_7);
  /* Pull-Up or Push-Pull */
  OUT_PORT->CR1 |= (uint8_t)(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_5|GPIO_PIN_7);
}


void HW_GPIO_Set(uint8_t map)
{
  if(map & 1)
  {
    OUT_PORT->ODR |= OUT1_PIN;
  }
  else if(map & 2)
  {
    OUT_PORT->ODR |= OUT2_PIN;
  }
  else if(map & 4)
  {
    OUT_PORT->ODR |= OUT3_PIN;
  }
  else if(map & 8)
  {
    OUT_PORT->ODR |= OUT4_PIN;
  }
}
#include "tim2.h"
#include "gpio.h"
//timer for BUZZER


volatile uint16_t tim2_cycles_count = 0;

void TIM2_init(void)
{
  TIM2_DeInit();

  TIM2->PSCR = (uint8_t)(TIM2_PRESCALER_32);
  TIM2->ARRH = (uint8_t)(125 >> 8);            //400Hz - 1250; 4kHz - 125
  TIM2->ARRL = (uint8_t)(125);
  TIM2->CCMR1 |= (6<<4);                        //Output compare toggle mode
  TIM2->CCMR1 |= (1<<3);                        //preload enable
  TIM2->CCMR1 &= ~(3);                          //configured as output
  TIM2->CCR1H = (uint8_t)(63>>8);              //50% duty cycle
  TIM2->CCR1L = (uint8_t)(63);//625
  TIM2->IER |= TIM2_IER_CC1IE;
  TIM2->CCER1 |= TIM2_CCER1_CC1E;
  TIM2->CR1 |= TIM2_CR1_CEN;
}


void TIM2_Stop(void)
{
  TIM2->CCER1 &= ~TIM2_CCER1_CC1E;
  BUZER_PORT->ODR &= ~BUZER_PIN;
}


void TIM2_Start(void)
{
  TIM2->CCER1 |= TIM2_CCER1_CC1E;
}


void TIM2_Toggle(void)
{
  TIM2->CCER1 ^= TIM2_CCER1_CC1E;
}

#pragma vector=0x10
__interrupt void  TIM2_CaptureIRqHandler(void)
{
  if(TIM2->SR1 & TIM2_SR1_CC1IF)
  {
    TIM2->SR1 &= ~TIM2_SR1_CC1IF;
    tim2_cycles_count++;
  }
}



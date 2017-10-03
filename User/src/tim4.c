#include "tim4.h"
#include "stm8s.h"

//timer for 60Hz

//volatile uint8_t timer_phase = 0;
volatile uint8_t tim4_cycles_count = 0;

void TIM4_Init(void)
{
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIMER_PERIOD);
  TIM4_SetCounter(0);
  TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);
  TIM4_Cmd(ENABLE);
}

#pragma vector=0x19 //each 8ms
__interrupt void TIM4_IRQ_Handler(void)
{
  //clear it flag
  if(TIM4->SR1 & TIM4_SR1_UIF)
  {
    TIM4->SR1 &= ~TIM4_SR1_UIF;
    //timer_phase ^= 0xFF;
    tim4_cycles_count++;
  }
}
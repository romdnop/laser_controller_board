#include "tim4.h"
#include "stm8s.h"

void TIM4_Init(void)
{
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_1, TIMER_PERIOD);
  TIM4_SetCounter(0);
  TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);
  TIM4_Cmd(ENABLE);
}

#pragma vector=ITC_IRQ_TIM4_OVF
__interrupt void TIM4_IRQ_Handler(void)
{
  
}
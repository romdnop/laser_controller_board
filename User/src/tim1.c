#include "tim1.h"

//timer for 60Hz

volatile uint8_t tim1_mask = 0;

void TIM1_init(void)
{
   TIM1_DeInit();
   TIM1_TimeBaseInit(64, TIM1_COUNTERMODE_UP, 2082, 0);
   TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);

  /* TIM1 counter enable */
  TIM1_Cmd(ENABLE);

}



#pragma vector=0x0d
__interrupt void TIM1_IRqHandler(void)
{
  if(TIM1->SR1 & TIM1_SR1_UIF)
  {
    TIM1->SR1 &= ~TIM1_SR1_UIF;
    tim1_mask ^= 0x0F;
  }
}



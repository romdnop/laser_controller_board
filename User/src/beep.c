#include "beep.h"

void BEEP_StartShortBeep(Beep_StructTypeDef *beep)
{
  beep->waiting_cycles = 100;
  beep->cycles = &tim2_cycles_count;
  *beep->cycles = 0;
  beep->state = BEEP_RUN;
  TIM2_Start();
}


void BEEP_StartLongBeep(Beep_StructTypeDef *beep)
{
  beep->waiting_cycles = 400;
  beep->cycles = &tim2_cycles_count;
  *beep->cycles = 0;
  beep->state = BEEP_RUN;
  TIM2_Start();
}


void BEEP_Execute(Beep_StructTypeDef *beep)
{
  if(beep->state != BEEP_RUN)
  {
    return;
  }
  if(*beep->cycles < beep->waiting_cycles)
  {
    return;
  }
  beep->state = BEEP_IDLE;
  TIM2_Stop();
}

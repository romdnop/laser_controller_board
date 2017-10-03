#include "beep.h"

void BEEP_StartShortBeep(Beep_StructTypeDef *beep)
{
  beep->waiting_cycles = 100;
  beep->cycles = &tim2_cycles_count;
  *beep->cycles = 0;
  beep->zumPhase = 0;
  beep->state = BEEP_RUN;
  TIM2_Start();
}


void BEEP_StartLongBeep(Beep_StructTypeDef *beep)
{
  beep->waiting_cycles = 400;
  beep->cycles = &tim2_cycles_count;
  *beep->cycles = 0;
  beep->zumPhase = 0;
  beep->state = BEEP_RUN;
  TIM2_Start();
}


void BEEP_StartZumming(Beep_StructTypeDef *beep)
{
  beep->zumPhase = 1;
  beep->state = BEEP_ZUMMING;
  beep->waiting_cycles = 200;
  beep->cycles = &tim2_cycles_count;
  *beep->cycles = 0;
  //TIM2_Start();
}


void BEEP_StopZumming(Beep_StructTypeDef *beep)
{
  beep->state = BEEP_IDLE;
  TIM2_Stop();
}


void BEEP_Execute(Beep_StructTypeDef *beep)
{
  if(beep->state == BEEP_IDLE)
  {
    return;
  }
  if(beep->state == BEEP_RUN)
  {
      if(*beep->cycles < beep->waiting_cycles)
      {
        return;
      }
  }
  if(beep->state == BEEP_ZUMMING)
  {
    if(*beep->cycles < beep->waiting_cycles)
    {
      return;
    }
    *beep->cycles = 0;
    TIM2_Toggle();
    return;
  }
  beep->state = BEEP_IDLE;
  TIM2_Stop();
}

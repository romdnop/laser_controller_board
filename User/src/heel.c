#include "heel.h"
#include "gpio.h"

void HEEL_Reset(HEEL_StructTypeDef *heel)
{
  heel->state = HEEL_IDLE;
}

uint8_t HEEL_Execute(HEEL_StructTypeDef *heel, Beep_StructTypeDef *beep)
{
  switch(heel->state)
  {
    case HEEL_IDLE:
        if((HEELING_PORT->IDR & HEELING_PIN))
        {
          heel->state = HEEL_START;
          return 0;
        }
        //BEEP_StopZumming(beep);
        return 0;
    case HEEL_START:
      //start zumming
      BEEP_StartZumming(beep);
      heel->state = HEEL_WAIT;
      return 0;
    case HEEL_WAIT:
      if(!(HEELING_PORT->IDR & HEELING_PIN))
      {
        heel->state = HEEL_IDLE;
        //stop zumming
        BEEP_StopZumming(beep);
        return 0;
      }
      return 0;
  }
  return 0;
}
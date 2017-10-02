#ifndef _BEEP_H
#define _BEEP_H
#include "stm8s.h"
#include "tim2.h"
//Buzer use tim2 timer

typedef enum
{
  BEEP_RUN,
  BEEP_IDLE
}BEEP_State;

typedef struct
{
  uint16_t waiting_cycles;
  volatile uint16_t *cycles;
  BEEP_State state;
}Beep_StructTypeDef;

void BEEP_StartShortBeep(Beep_StructTypeDef *beep);
void BEEP_StartLongBeep(Beep_StructTypeDef *beep);
void BEEP_Execute(Beep_StructTypeDef *beep);

#endif
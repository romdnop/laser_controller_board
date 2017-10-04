#ifndef _HEEL_H
#define _HEEL_H
#include "stm8s.h"
#include "beep.h"
typedef enum
{
  HEEL_IDLE,
  HEEL_START,
  HEEL_WAIT
}HEEL_StateTypeDef;


typedef struct
{
  HEEL_StateTypeDef state;
}HEEL_StructTypeDef;

void HEEL_Reset(HEEL_StructTypeDef *heel);
uint8_t HEEL_Execute(HEEL_StructTypeDef *heel, Beep_StructTypeDef *beep);


#endif
#ifndef _BEEP_H
#define _BEEP_H
#include "stm8s.h"

//Buzer use tim2 timer


typedef struct
{
  uint8_t long_flag;
  uint8_t cycles;
}Beep_StructTypeDef;


#endif
#ifndef _COM_H
#define _COM_H
#include "stm8s.h"


void delay_ms(uint8_t ms);


typedef enum
{
  EEPROM_IDLE,
  EEPROM_UNLOCK,
  
}EEPROM_StateTypeDef;

typedef struct
{
  EEPROM_StateTypeDef state;
  uint8_t data;
}EEPROM_StructTypeDef;



#endif
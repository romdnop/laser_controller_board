#include "common.h"
#include "tim4.h"


void delay_ms(uint8_t ms){
  tim4_cycles_count = 0;
  while(tim4_cycles_count < ms);
}





/*
uint8_t EEPROM_Execute(EEPROM_StructTypeDef *eeprom)
{
  switch()
  {
    case EEPROM_IDLE:
        return 0;
    case EEPROM_UNLOCK:
        FLASH->DUKR = FLASH_RASS_KEY2;
        FLASH->DUKR = FLASH_RASS_KEY1;
        eeprom->state++;
        return 0;
    case 
  }
}

*/


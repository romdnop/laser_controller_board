#include "common.h"
#include "tim4.h"


void delay_ms(uint8_t ms){
  tim4_cycles_count = 0;
  while(tim4_cycles_count < ms);
}
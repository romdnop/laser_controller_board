#include "common.h"

void delay_ms(uint16_t ms){
    while(ms--){
        uint16_t i;
        for(i = 0; i < ms; i++){
            nop();
        }
    }
}
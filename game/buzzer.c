#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init(){
  timerAUpmode();
  P2SEL2 &= ~(BIT6|BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR |= BIT6;
  buzzer_off();
}

void buzzer_beep(){
  CCR0 = 2000;
  CCR1 = 500;
}

void buzzer_off(){
  CCR0 = 0;
  CCR1=0;
}

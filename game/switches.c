#include <msp430.h>
#include "switches.h"
#include "game.h"

static char switch_update_interrupt_sense(){
  char p2=P2IN;
  P2IES |= (p2 & SWITCHES);
  P2IES &= ~(p2 & SWITCHES)|SWITCHES;
  return p2;
}

void switch_init(){
  P2REN |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  P2IE |= SWITCHES;
  switch_update_interrupt_sense();
}

void switch_interrupt_handler(){
  char p2=switch_update_interrupt_sense();
  char sw = ~p2 & SWITCHES;
  for(int i=0; i<4;i++){
    if(sw & (1<<i)){
      game_whack(i);
      break;
    }
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}


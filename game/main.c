
#include <msp430.h>
#include <stdlib.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "buzzer.h"
#include "game.h"

void wdt_c_handler();

int main(){
  WDTCTL = WDTPW | WDTHOLD;
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();

  game_init();
  //random sequence
  srand(77);
  enableWDTInterrupts();
  or_sr(0x8);

  while(1){
    if(redrawScreen){
      redrawScreen=0;
      game_draw();
    }
    or_sr(0x10);
  }
}

//called from assy file
void wdt_c_handler(){
  static int count=0;
  if(++count >=125){
    game_update();
    redrawScreen=1;
    count=0;
  }
}

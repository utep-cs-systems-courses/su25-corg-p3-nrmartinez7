#include <stdlib.h>
#include <stdio.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "game.h"
#include "buzzer.h"

const Pos holes[NUM_HOLES] ={
  //top left hole
  {screenWidth/4, screenHeight/3},

  //top right hole
  {3*screenWidth/4, screenHeight/3},

  //bottom left hole
  {screenWidth/4, 2*screenHeight/3},

  //bottom right hole
  {3*screenWidth/4, 2*screenHeight/3}
};

int current_mole=-1;
int score=0;
char redrawScreen=1;

//draw filled circle (holes)
//midpoint cirlce algorithm
static void fillCircle(int cx, int cy, int r, u_int color){
  for(int dy=-r; dy<=r; dy++){
    for(int dx=-r; dx<=r; dx++){
      if(dx*dx+dy*dy <= r*r){
	drawPixel(cx+dx, cy+dy, color);
      }
    }
  }
}

//draw banner, holes, mole
void game_draw(){
  //banner
  char buf[16];
  sprintf(buf, "Score: %d", score);
  fillRectangle(0,0,screenWidth, 16, COLOR_WHITE);
  drawString5x7(4,4,buf, COLOR_BLACK, COLOR_WHITE);

  //holes
  for(int i=0; i<NUM_HOLES; i++){
    fillCircle(holes[i].col, holes[i].row, HOLE_RADIUS, COLOR_BLACK);
  }

  //mole
  if(current_mole >= 0){
    fillCircle(holes[current_mole].col,
	       holes[current_mole].row,
	       MOLE_RADIUS, COLOR_ORANGE);
  }
}

//clear, initialize state
void game_init(){
  clearScreen(COLOR_BLUE);
  score=0;
  current_mole=-1;
  redrawScreen=1;
}

//erase old mole, pick new hole, draw mole in new hole
void game_update(){
  //erase old mole
  if(current_mole >=0){
    fillCircle(holes[current_mole].col,
	       holes[current_mole].row,
	       HOLE_RADIUS, COLOR_BLACK);
  }

  //pick new hole and draw mole
  current_mole=rand() %NUM_HOLES;
  fillCircle(holes[current_mole].col,
	     holes[current_mole].row,
	     MOLE_RADIUS, COLOR_ORANGE);
}

//whacking themole
void game_whack(int i){
  if(i==current_mole){
    //mole is hit
    buzzer_beep();
    score++;
    //removes hole and redraws screen
    current_mole=-1;
    redrawScreen=1;
  }else{
    buzzer_off();
  }
}


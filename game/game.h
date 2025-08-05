#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include "lcdutils.h"

#define NUM_HOLES 4
#define HOLE_RADIUS 12
#define MOLE_RADIUS 10

//pos (position) struct that organizes col and row
typedef struct{
  short col, row;
}Pos;

//hole positions, states, and score
extern const Pos holes[NUM_HOLES];
extern int current_mole;
extern int score;
extern char redrawScreen;

//running game
void game_init();
void game_update();
void game_draw();
void game_whack(int i);

#endif 

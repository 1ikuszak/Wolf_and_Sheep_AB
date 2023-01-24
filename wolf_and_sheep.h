#include <stdbool.h>


#ifndef WOLF_AND_SHEEP
#define WOLF_AND_SHEEP

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

typedef enum{WOLF, SHEEP} side;


typedef struct 
{
  char start_filed, destined_field;
} Move;


typedef struct
{
  union
    {
      char __2D[BOARD_WIDTH][BOARD_HEIGHT];
      char __1D[BOARD_WIDTH * BOARD_HEIGHT];
    } field;

  side on_move;
  int wolf_pos;
  int wolf_moves;
  int sheep_moves;
  Move last_move;
  
} Board;



typedef struct 
{
  int search_depth;
  int leaf;
  int rated_branch;
  int number_of_moves;
  int last_print;
  int start;
  Move moves[];
} Statistic;



extern void display(Board *board);
extern Board start_layout;
extern Board makeMove(Board board, Move move);
extern Move *GenerateWolfMoves(Board *board);
extern Move *GenerateSheepMoves(Board *board);
extern bool checkIfLegal(Board *board, Move move);
extern bool WolfWinCheck (Board *board);
extern bool SheepWinCheck(Board *board);
extern bool WolfWinCheck (Board *board);
extern int positionRating(Board *board);
extern Board takeBack_2(Board *board);
extern Board takeBack(Board *board);


#endif
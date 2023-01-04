#ifndef WOLF_AND_SHEEP
#define WOLF_AND_SHEEP

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

typedef enum{WOLF, SHEEP} side;

typedef struct
{
  union
    {
      char __2D[BOARD_WIDTH][BOARD_HEIGHT];
      char __1D[BOARD_WIDTH * BOARD_HEIGHT];
    } field;

  side on_move;
  int wolf_pos;
  
} Board;


typedef struct 
{
  char start_filed, destined_field;
} Move;



extern void display(Board *board);
extern Board start_layout;
extern Board makeMove(Board board, Move move);
extern void GenerateWolfMoves(Board board);


#endif
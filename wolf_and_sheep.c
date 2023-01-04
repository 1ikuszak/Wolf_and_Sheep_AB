#include<stdio.h>
#include "wolf_and_sheep.h"


union 
{
    char __1D[BOARD_WIDTH * BOARD_HEIGHT][3];
    char __2D[BOARD_WIDTH][BOARD_HEIGHT][3];
} field_name = { "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
                 "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
                 "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
                 "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
                 "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
                 "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
                 "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
                 "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",};



Board start_layout = { .field.__1D = {
    ' ', 'W', ' ', ' ', ' ', ' ',' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ',
    'S', ' ', 'S', ' ', 'S', ' ','S', ' ',
    }, .on_move = WOLF};


void display(Board *board)
{
    printf("   +---+---+---+---+---+---+---+---+\n");

    for(int row = BOARD_HEIGHT; row > 0; row--)
    {
        printf(" %c | %c | %c | %c | %c | %c | %c | %c | %c |\n",
        '1' + row-1, board->field.__2D[row - 1][0], board->field.__2D[row -1][1],
        board->field.__2D[row -1][2],board->field.__2D[row -1][3],
        board->field.__2D[row -1][4],board->field.__2D[row -1][5],
        board->field.__2D[row -1][6],board->field.__2D[row -1][7]);
        printf("   +---+---+---+---+---+---+---+---+\n");
    }
    printf("     A   B   C   D   E   F   G   H  \n");

    if(board->on_move == WOLF)
      printf("\nruch wilka\n");
    if(board->on_move == SHEEP)
      printf("\nruch owcy\n");
}


Board makeMove(Board board, Move move)
{
    Board new_board = board;
    new_board.field.__1D[move.destined_field] = new_board.field.__1D[move.start_filed];
    new_board.field.__1D[move.start_filed] = ' ';
    new_board.on_move = new_board.on_move == WOLF ? SHEEP : WOLF;
    new_board.wolf_pos = move.destined_field;
    
    return new_board;
}


int isLeagalWolf(Move move)
{
    if (move.destined_field == move.start_filed + BOARD_WIDTH + 1)
        return 1;
    if (move.destined_field == move.start_filed + BOARD_WIDTH - 1)
        return 1;
    if (move.destined_field == move.start_filed - BOARD_WIDTH + 1)
        return 1;
    if (move.destined_field == move.start_filed - BOARD_WIDTH - 1)
        return 1;
    else
    {
        printf("ng");
        return 0;
    }

}


int isLeagalSheep(Move move)
{
    if (move.destined_field == move.start_filed - BOARD_WIDTH + 1)
        return 1;
    if (move.destined_field == move.start_filed - BOARD_WIDTH + 1)
        return 1;
    else
        return 0;
}


void GenerateWolfMoves(Board board)
{
    char possible_moves[4];

    if (board.wolf_pos)

    possible_moves[0] = (board.wolf_pos) + BOARD_WIDTH + 1;
    possible_moves[1] = (board.wolf_pos) + BOARD_WIDTH - 1;
    possible_moves[2] = (board.wolf_pos) - BOARD_WIDTH + 1;
    possible_moves[3] = (board.wolf_pos) - BOARD_WIDTH - 1;


    for (int i = 0; i < 4; i++)
    {
        printf("%d\n`", possible_moves[i]);
    }
}


void GenerateSheepMoves()
{

}
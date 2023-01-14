#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<time.h>



#include "wolf_and_sheep.h"


int MAX_WOLF_MOVES = 4;
int MAX_SHEEP_MOVES = 8;


Move possible_wolf_moves[4];
Move possible_sheep_moves[8];



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
    }, .on_move = WOLF, .wolf_pos = 1};


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

    if (new_board.on_move == WOLF)
    {
        new_board.wolf_pos = move.destined_field;
        new_board.on_move = SHEEP;
    }
    else
        new_board.on_move = WOLF;
    
    return new_board;
}



bool checkIfLegal(Board *board, Move move)
{
    int pos_1 = move.start_filed + BOARD_WIDTH + 1;
    int pos_2 = move.start_filed + BOARD_WIDTH - 1;
    int pos_3 = move.start_filed - BOARD_WIDTH + 1;
    int pos_4 = move.start_filed - BOARD_WIDTH - 1;

    switch (board->field.__1D[move.start_filed])
    {
    case 'W':
    {
        if (move.destined_field == pos_1 && pos_1 > 0 && board->field.__1D[pos_1] == ' ')
            return true;

        else if (move.destined_field == pos_2 && pos_2 > 0 && board->field.__1D[pos_2] == ' ')
            return true;

        else if (move.destined_field == pos_3 && pos_3 > 0 && board->field.__1D[pos_3] == ' ')
            return true;
        
        else if (move.destined_field == pos_4 && pos_4 > 0 && board->field.__1D[pos_4] == ' ')
            return true;

        else
        {
            printf("choose different destined field");
            return false;
        }
    }

    case 'S':
    {
        if (move.destined_field == pos_3 && pos_3 > 0 && board->field.__1D[pos_3] == ' ')
            return true;
        else if (move.destined_field == pos_4 && pos_4 > 0 && board->field.__1D[pos_4] == ' ')
            return true;
        else
        {
            printf("choose different destined field");
            return false;
        }
    }

    default:
        printf("wrong start field input");
        return false;
    }
}



void int_to_board_pos(int pos)
{
    int col =  (pos % BOARD_WIDTH);
    int row = (pos / BOARD_WIDTH) + 1;

    printf("\t%c%d", col + 'A', row);
}


Move *GenerateWolfMoves(Board *board)
{
    int counter = 0;

    int col =  board->wolf_pos % BOARD_WIDTH;
    int row = board->wolf_pos / BOARD_WIDTH;

    // lewy gorny
    int pos_1 = board->wolf_pos + BOARD_WIDTH - 1;
    // prawy gorny
    int pos_2 = board->wolf_pos + BOARD_WIDTH + 1;
    // prawy dolny
    int pos_3 = board->wolf_pos - BOARD_WIDTH + 1;
    // lewy dolny
    int pos_4 = board->wolf_pos - BOARD_WIDTH - 1;
 

    if (row != BOARD_HEIGHT - 1)
    {
        if (pos_1 > 0 && board->field.__1D[pos_1] == ' ' && col != 0)
        {
            possible_wolf_moves[counter].destined_field = pos_1 ;
            counter ++;
        }
        if (pos_2> 0  && board->field.__1D[pos_2] == ' ' && col != BOARD_WIDTH - 1)
        {
            possible_wolf_moves[counter].destined_field = pos_2;
            counter ++;
        }
    }
    if (row != 0)
    {
        if (pos_3 > 0  && board->field.__1D[pos_3] == ' ')
        {
            possible_wolf_moves[counter].destined_field = pos_3;
            counter ++;
        }
        if (pos_4 > 0  && board->field.__1D[pos_4] == ' ')
        {
            possible_wolf_moves[counter].destined_field = pos_4;
            counter ++;
        }
    }

    // ustawienie pola poczatkowego
    for (int i = 0; i < counter; i++)
    {
        possible_wolf_moves[i].start_filed = board->wolf_pos;
    }
    

    printf("ruchy:\n");
    for (int i = 0; i < counter; i++)
    {
        printf("|%d| field: %d -> %d", i, possible_wolf_moves[i].start_filed, possible_wolf_moves[i].destined_field);
        int_to_board_pos(possible_wolf_moves[i].destined_field);
        printf("\n");
    }

    board->wolf_moves = counter;
    return(possible_wolf_moves);
}



Move *GenerateSheepMoves(Board *board)
{
    int temp_pos;
    int counter = 0;

    for(int col = 0; col < BOARD_WIDTH; col++)
    {
        for(int row = 0; row < BOARD_HEIGHT; row++)
        {
            if(board->field.__2D[row][col] == 'S')
            {   
                // sprawdzamy czy owce maja miejsce na ruch do przodu
                if (row < BOARD_WIDTH -1);
                {   
                    // sprawdzamy czy owca jest na prawej granicy i czy docelowe pole jest wolne
                    if (col != BOARD_WIDTH - 1)
                    {
                        // sprawdzamy czy pole jest wolne
                        if (board->field.__2D[row - 1][col + 1] != 'S' && board->field.__2D[row - 1][col + 1] != 'W')
                        {
                            // dodajemy obiekt (Move) do listy []
                            possible_sheep_moves[counter].start_filed = BOARD_WIDTH * row + col,
                            possible_sheep_moves[counter].destined_field = BOARD_WIDTH * (row-1) + col + 1;
                            printf("|%d| field: %d -> %d\n", counter, possible_sheep_moves[counter].start_filed, possible_sheep_moves[counter].destined_field);
                            counter ++;
                        }
                    }
                    // sprawdzamy czy owca jest na lewej granicy i czy docelowe pole jest wolne
                    if(col != 0)
                    {
                        // sprawdzamy czy pole jest wolne
                        if (board->field.__2D[row - 1][col - 1] != 'S' && board->field.__2D[row - 1][col - 1] != 'W')
                        {
                            // dodajemy obiekt (Move) do listy []
                            possible_sheep_moves[counter].start_filed = BOARD_WIDTH * row + col,
                            possible_sheep_moves[counter].destined_field = BOARD_WIDTH * (row-1) + col - 1;
                            printf("|%d| field: %d -> %d\n", counter, possible_sheep_moves[counter].start_filed, possible_sheep_moves[counter].destined_field);
                            counter ++;
                        }
                    }
                }
            }
        }
    }
    board->sheep_moves = counter;

    return (possible_sheep_moves);
}


bool WolfWinCheck (Board *board)
{
    if(board->field.__1D[board->wolf_pos] >= (BOARD_HEIGHT -1) * BOARD_WIDTH)
        return true;
    
    return false;
}

bool SheepWinCheck(Board *board)
{
    if (GenerateSheepMoves(board) == 0)
        return true;
    
    return false;
}


int positionRating(Board *board)
{
    int rating = 0;
    switch (board->on_move)
    {
    case WOLF:
    {
        rating = (board->wolf_pos / BOARD_WIDTH) + 1;
        break;
    }
    case SHEEP:
    {
        rating = 5 - board->wolf_moves;
        break;
    }
    default:
        {
            printf("rating went wrong");
            break;
        }
    }
    
    return(rating);
}

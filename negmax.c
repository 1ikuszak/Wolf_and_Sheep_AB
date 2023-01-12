#include<stdio.h>
#include<time.h>
#include "negmax.h"


int negmax(Board *board, int depth, int alpha, int beta, Statistic *stats)
{
    if(!depth)
    {
        stats->rated_branch++;
        return positionRating(board);
    }
    Board *temp_board = board;
    Move *legall;
    int moves = 0;
    //Board board1 = &board;
    if(board->on_move == WOLF)
    {
        moves = board->wolf_moves;
        legall = GenerateWolfMoves(&board);
    }

    if(board->on_move == SHEEP)
    {
        moves = board->sheep_moves;
        legall = GenerateSheepMoves(&board);
    }
    stats->knots_w_generated_moves++;
    int rating = -10000, temp_rating;

    
    for(int i = 0; i < moves; i++)
    {
        printf("hello %d\n", i);
        //if (flaga_stopu) break;

        if(((clock() - stats->last_print) >(10000 + (rand()/100))))
        {
            printf("info nodes %ld time %ld nps %ld\n", stats->rated_branch + stats->knots_w_generated_moves, (clock() - stats->start)/1000, CLOCKS_PER_SEC / (clock() - stats->start));
            stats->last_print = clock();
        }

        makeMove(temp_board, legall[i]);
        temp_rating = -negmax(temp_board, depth - 1, -beta, -alpha, stats);

        if(temp_rating > rating)
            rating = temp_rating;
        if(rating > alpha)
            alpha = rating;
        if(alpha >= beta)
            break;
    }
    printf("ocena %d ", rating);
    return(rating);
}
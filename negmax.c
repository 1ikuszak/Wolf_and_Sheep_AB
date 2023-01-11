#include<stdio.h>
#include "wolf_and_sheep.h";


int negmax(Board *board, int depth, int alpha, int beta, Statistic* stats)
{
    if(!depth)
    {
        stats->rated_branch++;
        return positionRating(board);
    }

    Move legall[100];
    int moves = 0;
    if(board->on_move == WOLF)
        moves = board->wolf_moves;
    if(board->on_move == SHEEP)
        moves = board->sheep_moves;
    int rating = -10000, temp_rating;
    
    for(int i = 0; i < moves; i++)
    {
        // if (flaga stopu) break;

        if(((clock() - stats->last_print) >(10000 + (rand()/100))))
        {
            printf("info nodes %ld time %ld nps %ld\n", stats->rated_branch + stats->knots_w_generated_moves, (clock() - stats->start)/1000, CLOCKS_PER_SEC / (clock() - stats->start));
            // CLOCKS_PER_SEC / (clock() - stats->start);
            stats->last_print = clock();
        }

        stats->moves[stats->number_of_moves++] = legall[i];

        makeMove(board, legall[i]);
    }
}
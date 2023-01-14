#include<stdio.h>
#include<time.h>
#include "negamax.h"


// function negamax(node, depth, alfa, beta, color) is
//     if depth = 0 or node is a terminal node then
//         return colors x the heuristic value of node
    
//     childNodes := generateMoves(node)
//     childNodes := orderMoves(childNodes)
    
//     values := -niesk
//     foreach child in childNodes do
//         value := max(value, -negmax(child, depth, -1, -beta, -alfa, -color))
//         a := max(alfa, value)
//         if alfa >= Beta then
//             break (* cut-off *)
    
//     return value


int negamax(Board *board, int depth, int alpha, int beta, Statistic *stats)
{
    if(depth == 0)
    {
        stats->rated_branch++;
        return positionRating(board);
    }

    Board *temp_board = board;
    Move *legall_moves;
    int moves = 0;

    //Board board1 = &board;
    if(board->on_move == WOLF)
    {
        legall_moves = GenerateWolfMoves(board);
        moves = board->wolf_moves;
    }

    if(board->on_move == SHEEP)
    {
        legall_moves = GenerateSheepMoves(board);
        moves = board->sheep_moves;
    }

    stats->knots_w_generated_moves++;
    printf("knots_w_generated_moves: %d\n", stats->knots_w_generated_moves);
    int rating = -10000, temp_rating;

    printf("moves: %d\n", moves);

    for(int i = 0; i < moves; i++)
    {
        // printf("hello %d\n", i);
        // //if (flaga_stopu) break;

        if(((clock() - stats->last_print) >(10000 + (rand()/100))))
        {
            printf("info nodes %ld time %ld nps %ld\n", stats->rated_branch + stats->knots_w_generated_moves, (clock() - stats->start)/1000, CLOCKS_PER_SEC / (clock() - stats->start));
            stats->last_print = clock();
        }
        
        display(board);
        
        *temp_board = makeMove(*board, legall_moves[i]);
        temp_rating = -negamax(temp_board, depth - 1, -beta, -alpha, stats);

        // alfa beta prouning
        if(temp_rating > rating)
            rating = temp_rating;
        if(rating > alpha)
            alpha = rating;
        if(alpha >= beta)
            break;
    }
    printf("ocena %d\n", rating);
    return(rating);
}
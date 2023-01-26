#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include "wolf_and_sheep.h"
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

int NegaMax(Board *board, int depth, int alpha, int beta, Statistic *stats)
{
    if(depth == 0)
    {
        stats->leaf++;
        // printf("depth 0 leaf: %d \n", stats->leaf);
        return positionRating(board);
    }

    int score = -10000, current_score;
    Move *legall_moves;
    Board *copy_board = malloc(sizeof(board)*1000);


    int moves;
    if(board->on_move == WOLF)
    {
        legall_moves = GenerateWolfMoves(board);
        moves = board->wolf_moves;
        // printf("analizuje wilka, %d\n", moves);

    }
    if(board->on_move == SHEEP)
    {
        legall_moves = GenerateSheepMoves(board);
        moves = board->sheep_moves;
        // printf("analizuje owce, %d\n", moves);
    }

    for(int i = 0; i < moves; i++)
    {
        *copy_board = makeMove(*board, legall_moves[i]);
        current_score = -NegaMax(copy_board, depth - 1, -beta, -alpha, stats);

        stats->number_of_moves ++;
        stats->leaf++;
        // printf("leaf: %d \t", stats->leaf);

        // alfa beta
        if(current_score > score)
        {
            score = current_score;
            stats->best_move = legall_moves[i];
        }
        if(score > alpha)
            alpha = score;
        if(alpha >= beta)
            break;
    }    
    // printf("ocena: %d najlepszy ruch %d -> %d\n",score, stats->best_move.start_filed, stats->best_move.destined_field);
    return(score);
}

#include<stdio.h>
#include<time.h>
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
        return positionRating(board);
    }

    if(stats->search_depth == depth)
        stats->start = clock();
    
    int score = -10000, current_score;
    Move *legall_moves;
    Move best_move;
    int moves;
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


    for(int i = 0; i < moves; i++)
    {
        // Board copy = *board;
        stats->moves[stats->number_of_moves] = legall_moves[i];
        
        // wykonaj symulacyjne ruchy, ruch
        makeMove(*board, legall_moves[i]);
        current_score = -NegaMax(board, depth - 1, -beta, -alpha, stats);
        // cofnij ruch 
        // znikaja figury
        takeBack_2(board);
        // display(board);


        // alfa beta 
        if(current_score > score)
            score = current_score;
            best_move = legall_moves[i];
        if(score > alpha)
            alpha = score;
        if(alpha >= beta)
            break;
    }
    printf("ocena: %d najlepszy ruch %d -> %d\n",score, best_move.start_filed, best_move.destined_field);
    display(board);

    return(score);
}

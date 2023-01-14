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


// int negamax(Board *board, int depth, int alpha, int beta, Statistic *stats)
// {
//     if(depth == 0)
//     {
//         stats->leaf++;
//         printf("position ranking: %d\n", positionRating(board));
//         return positionRating(board);
//     }

//     Board *temp_board = board;
//     Move *legall_moves;
//     int moves;

//     if(board->on_move == WOLF)
//     {
//         legall_moves = GenerateWolfMoves(board);
//         moves = board->wolf_moves;
//     }

//     if(board->on_move == SHEEP)
//     {
//         legall_moves = GenerateSheepMoves(board);
//         moves = board->sheep_moves;
//     }

//     stats->leaf++;
//     printf("leaf: %d\n", stats->leaf);
//     int rating = -10000, temp_rating;


//     for(int i = 0; i < moves; i++)
//     {
//         // //if (flaga_stopu) break;
//         if(((clock() - stats->last_print) >(10000 + (rand()/100))))
//         {
//             printf("info nodes %ld time %ld nps %ld\n", stats->rated_branch + stats->leaf, (clock() - stats->start)/1000, CLOCKS_PER_SEC / (clock() - stats->start));
//             stats->last_print = clock();
//         }

//         *temp_board = makeMove(*board, legall_moves[i]);
//         temp_rating = -negamax(temp_board, depth - 1, -beta, -alpha, stats);
//         display(board);

//         // alfa beta 
//         if(temp_rating > rating)
//             rating = temp_rating;
//         if(rating > alpha)
//             alpha = rating;
//         if(alpha >= beta)
//             break;
//     }
//     printf("finalowa ocena %d\n", rating);
//     return(rating);
// }


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
        // zegar
        if(((clock() - stats->last_print) >(10000 + (rand()/100))))
        {
            printf("info nodes %ld time %ld nps %ld\n", stats->rated_branch + stats->leaf, (clock() - stats->start)/1000, CLOCKS_PER_SEC / (clock() - stats->start));
            stats->last_print = clock();
        }

        Board copy = *board;
        stats->moves[stats->number_of_moves] = legall_moves[i];
        
        // wykonaj symulacyjne ruchy, ruch
        makeMove(*board, legall_moves[i]);
        current_score = -negamax(board, depth - 1, -beta, -alpha, stats);
        // cofnij ruch
        // takeBack(board);

        // alfa beta 
        if(current_score > score)
            score = current_score;
            best_move = legall_moves[i];
        if(score > alpha)
            alpha = score;
        if(alpha >= beta)
            break;
    }
    display(board);
    printf("finalowa ocena %d\n", score);
    printf("najlpeszy ruch %d -> %d\n", best_move.start_filed, best_move.destined_field);

    return(score);
}


// void takeBack(Board *board)
// {
//     board->field.__1D[board->last_move.start_filed] = board->field.__1D[board->last_move.destined_field];
//     board->field.__1D[board->last_move.destined_field] = ' ';

//     return board;
// }
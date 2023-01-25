// // Board takeBack_2(Board *board)
// // {
    
// //     Board new_board = makeMove(*board, (Move) {.destined_field = board->field.__1D[board->last_move.start_filed], 
// //     .start_filed = ""});

//     switch (board->on_move)
//     {
//     case WOLF:
//     {
//         new_board.on_move = SHEEP;
//         break;
//     }
//     case SHEEP:
//     {
//         new_board.on_move = WOLF;
//         break;
//     }

//     default:
//         break;
//     }

// //     return new_board;
    
// // }

// // Board takeBack_2(Board *board)
// // {
// //     makeMove(*board, (Move) {.destined_field = board->field.__1D[board->last_move.start_filed], .start_filed = board->field.__1D[board->last_move.destined_field]});
// // }



// // Board takeBack_4(Board *board, Statistic stats)
// // {
// //     makeMove(*board, (Move) {.destined_field = board->field.__1D[stats.moves[-1].start_filed], .start_filed = board->field.__1D[board->last_move.destined_field]});

// //     switch (board->on_move)
// //     {
// //     case WOLF:
// //     {
// //         board->on_move = SHEEP;
// //     }
// //     case SHEEP:
// //     {
// //         board->on_move = WOLF;
// //     }

// //     default:
// //         break;
// //     }
// // }
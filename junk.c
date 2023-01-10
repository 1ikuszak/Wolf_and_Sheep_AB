// void GenerateSheepMoves(Board *board)
// {
//     for(int col = 0; col < BOARD_WIDTH; col++)
//       {
//         for(int row = 0; row < BOARD_HEIGHT; row++)
//         {
//           if(board->field.__2D[row][col] == 'S')
//           {
//             printf("SHEEP %c%c: ", col + 1 + '0' + 48, row + 1 + '0');
//             for(int col1 = 0; col1 < BOARD_WIDTH; col1++)
//             {
//               for(int row1 = 0; row1 < BOARD_HEIGHT; row1++)
//               {
//                 if(checkIfLegall(board, (Move) {.start_filed = board->field.__2D[row][col], .destined_field = board->field.__2D[row1][col1]}, col, row, col1, row1) == 1)
//                 {
//                   possible_moves[counter] = (Move) {.start_filed = board->field.__2D[row][col], .destined_field = board->field.__2D[row1][col1]};
//                   counter++;
//                   //printf("%c%c ", col1 + 1 +'0'+ 48, row1 + 1 +'0');
//                 }
//               }
//             }
//             printf("\n");
//           }
//         }
//       }
// }
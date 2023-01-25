#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "wolf_and_sheep.h"
#include "negamax.h"


int flaga_stopu = 0;
Move mozliwe_ruchy[100];
Statistic stats = (Statistic) {.leaf=0, .number_of_moves=0, .rated_positions=0};


void silnik() {}

void main(void) {

  pthread_t watek_silnika;
  Board board;
  
  // bufor na dane wejsciowe
  char bufor[1024];
  int dlugosc_bufora;

  if (pthread_create(&watek_silnika, NULL, (void *)silnik, NULL)) {
    printf("info string error: engine couldn't start it's thread\n");
    return;
  }

  for (printf("info string engine started\n");; scanf("\n")) {
    scanf("%[^\n]", bufor);
    dlugosc_bufora = strlen(bufor);

    if (strstr(bufor, "quit") == bufor && dlugosc_bufora == 4) {
      flaga_stopu = 1;
      break;
    }

    if (strstr(bufor, "uci") == bufor && dlugosc_bufora == 3)
      printf("id name enige 1.0\nid author Dejno 1ikuszak\nuciok\n");

    else if (strstr(bufor, "isready") == bufor && dlugosc_bufora == 7)
      printf("readyok\n");

    else if (strstr(bufor, "!wypisz") == bufor && dlugosc_bufora == 7)
      display(&board); 
    
    else if (strstr(bufor, "!nowa") == bufor && dlugosc_bufora == 5)
      board = start_layout;

    else if (strstr(bufor, "!ruch") == bufor && dlugosc_bufora == 11)
    {
      if (checkIfLegal(&board, (Move) {.start_filed = (bufor[7] - '1') * 8 + bufor[6] - 'a',
      .destined_field = (bufor[10] - '1') * 8 + bufor[9] - 'a'}))
      {
        board = makeMove(board, (Move) {.start_filed = (bufor[7] - '1') * 8 + bufor[6] - 'a',
        .destined_field = (bufor[10] - '1') * 8 + bufor[9] - 'a'});
        display(&board); 
      }
    }
    else if (strstr(bufor, "!wilk") == bufor && dlugosc_bufora == 5)
      GenerateWolfMoves(&board);
    
    else if (strstr(bufor, "!owca") == bufor && dlugosc_bufora == 5)
      GenerateSheepMoves(&board);

    else if (strstr(bufor, "!negamax") == bufor && dlugosc_bufora == 8)
    {
      NegaMax(&board, 3, -50000, 50000, &stats);
      printf("%d -> %d", stats.best_move.start_filed, stats.best_move.destined_field);
      // reset negamax
      stats.leaf = 0;
      stats.number_of_moves = 0;
      stats.rated_positions = 0;
    }
    else if (strstr(bufor, "!back") == bufor && dlugosc_bufora == 5)
    {
      board = takeBack(&board);
      display(&board);
    }
    else if(strstr(bufor, "!play") == bufor && dlugosc_bufora == 5)
    {
      for(printf("gra rozpoczeta\n");; scanf("\n"))
      {
        scanf("%[^\n]", bufor);
        dlugosc_bufora = strlen(bufor);
        display(&board);
        if (strstr(bufor, "!ruch") == bufor && dlugosc_bufora == 11)
        {
          if (checkIfLegal(&board, (Move) {.start_filed = (bufor[7] - '1') * 8 + bufor[6] - 'a',
          .destined_field = (bufor[10] - '1') * 8 + bufor[9] - 'a'}))
          {
            board = makeMove(board, (Move) {.start_filed = (bufor[7] - '1') * 8 + bufor[6] - 'a',
            .destined_field = (bufor[10] - '1') * 8 + bufor[9] - 'a'}); 
          }
          NegaMax(&board, 5, -50000, 50000, &stats);
          board = makeMove(board, stats.best_move);
          display(&board);
        }
        
        else if (strstr(bufor, "quit") == bufor && dlugosc_bufora == 4) 
        {
          flaga_stopu = 1;
          break;
        }   
      } 
    }
  }

  pthread_join(watek_silnika, NULL);

}



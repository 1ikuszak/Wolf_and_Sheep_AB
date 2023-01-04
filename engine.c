#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wolf_and_sheep.h"


int flaga_stopu = 0;
Move mozliwe_ruchy[100];

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
      printf("id name Entropia 1.0\nid author Donica\nuciok\n");

    else if (strstr(bufor, "isready") == bufor && dlugosc_bufora == 7)
      printf("readyok\n");

    else if (strstr(bufor, "!wypisz") == bufor && dlugosc_bufora == 7)
      display(&board); 
    
    else if (strstr(bufor, "!nowa") == bufor && dlugosc_bufora == 5)
      board = start_layout;

    else if (strstr(bufor, "!ruch") == bufor && dlugosc_bufora == 11)
      board = makeMove(board, (Move) {.start_filed = (bufor[7] - '1') * 8 + bufor[6] - 'a',
      .destined_field = (bufor[10] - '1') * 8 + bufor[9] - 'a'});
    
    else if (strstr(bufor, "!generuj") == bufor && dlugosc_bufora == 8)
      GenerateWolfMoves(board);
  }

  pthread_join(watek_silnika, NULL);

}




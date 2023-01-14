#include <stdio.h>
#include "wolf_and_sheep.h"


#ifndef NEGAMAX
#define NEGAMAX

extern int NegaMax(Board *board, int depth, int alpha, int beta, Statistic *stats);

#endif
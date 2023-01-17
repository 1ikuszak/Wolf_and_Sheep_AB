#include <stdio.h>

void main()
{
    int width = 8;
    int pos = 24;
    int col = pos%width;

    printf("%d\n", col);
}
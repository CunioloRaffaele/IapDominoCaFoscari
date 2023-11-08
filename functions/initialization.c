#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void generate_player_deck (int *playerTiles, int arrayDimensions) {
    for (int counter = 0; counter < arrayDimensions; counter++) {
        *(playerTiles+counter) = 0;
    }
}

void generate_tiles_composition (int array[20][2]) {
    int it= 0;
    for (int c = 1; c <= 6; c++) {
        for (int d = c; d <= 6; d++) {
            array [it][0] = c;
            array [it][1] = d;
            it = it+1;
        }
    }
}
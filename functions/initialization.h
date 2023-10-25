#include <stdio.h>

void initialization (int *playerTiles, int arrayDimensions) {
    for (int counter = 0; counter < arrayDimensions; counter++) {
        *(playerTiles+counter) = 0;
    }
}
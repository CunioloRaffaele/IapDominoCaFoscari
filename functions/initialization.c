#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int** alloc_player_deck_memory (int src_size) {
    int **generatedMalloc;
    generatedMalloc = (int**) malloc(sizeof(int*) * src_size);      // allochiamo la memoria per x int* (che contengono i puntatori agli interi dell'array)
    for (int i = 0; i < src_size; i ++){
        generatedMalloc[i] = (int*) malloc(2 * sizeof(int));
    }
    return generatedMalloc;
}

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
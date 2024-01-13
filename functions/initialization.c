#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../functions.h"

int** allocPlayerDeckMemory (int src_size) {
    int **generatedMalloc;
    generatedMalloc = (int**) malloc(sizeof(int*) * src_size);      // allochiamo la memoria per x int* (che contengono i puntatori agli interi dell'array)
    for (size_t i = 0; i < src_size; i ++){
        generatedMalloc[i] = (int*) malloc(2 * sizeof(int));
    }
    return generatedMalloc;
}

void generatePlayerDeck (int gameSet[21][2], int **deck, int arrayDimensions) {
    srand ( time(NULL) );
    for (int counter = 0; counter < arrayDimensions; counter++) {
        // Generiamo un numero randomico tra 0 9 per decidere se mettere una tessera speciale o una normale
        // (0 - 6) -> tessera normale
        // (7 - 9) -> tessera speciale 7 = [11 | 11] 8 = [12 | 21] 9 = [0 | 0]
        int random = rand() % 10;
        if (random <= 6) {
            // Generiamo un numero randomico tra 0 e 21
            int randomTile = rand() % 22;
            deck[counter][0] = gameSet[randomTile][0];
            deck[counter][1] = gameSet[randomTile][1];
        }else if (random == 7) {
            deck[counter][0] = 11;
            deck[counter][1] = 11;
        } else if (random == 8) {
            deck[counter][0] = 12;
            deck[counter][1] = 21;
        } else if (random == 9) {
            deck[counter][0] = 0;
            deck[counter][1] = 0;
        }
    }
}

void generateTilesComposition (int array[21][2]) {
    int it= 0;
    for (int c = 1; c <= 6; c++) {
        for (int d = c; d <= 6; d++) {
            array [it][0] = c;
            array [it][1] = d;
            it = it+1;
        }
    }
}

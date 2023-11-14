#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "initialization.c"

bool is2dArrayEmpty(int** array, int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 2; j++) {
            if (array[i][j] != 0) {
                return false;  // Restituisce falso se trova un elemento diverso da zero
            }
        }
    }
    return true;  // Ritorna vero se non trova elementi diversi da zero
}

int* processAI (int** deck, int deckDimension, int indexOfStartingTile) {
    // Creiamo una malloc contenente gli indici delle tessere da giocare in ordine
    // Gli indici negativi indicano che la tessera va girata
    // Questa malloc deve essere liberata dal chiamante della funzione
    int numbersOfElementsIndexInOrder = 0;
    int* indexInOrder = (int*) malloc (sizeof(int) * deckDimension);
    if (indexInOrder == NULL) {
        exit(1);
    }

    // Creiamo una copia privata della malloc contenente il deck in modo da poter
    // rimuovere le tessere valutate senza intervenire sull'array originale.
    // Questa malloc va liberata alla fine della funzione.
    int** deckCopy = alloc_player_deck_memory(deckDimension);

    // Copiamo i valori di deck in deckCopy
    for (int i = 0; i < deckDimension; i++) {
        deckCopy[i][0] = deck[i][0];
        deckCopy[i][1] = deck[i][1];
    }

    // Il primo index da salvare è quello della tessera iniziale
    indexInOrder[0] = indexOfStartingTile;
    // Rimuoviamo la tessera iniziale dal deck
    deckCopy[indexOfStartingTile][0] = 0;
    deckCopy[indexOfStartingTile][1] = 0;
    // Aggiorniamo il counter di elementi in ordine
    numbersOfElementsIndexInOrder++;

    while (is2dArrayEmpty(** deckCopy, deckDimension)) {
        // Salviamo la seconda faccia dell'ultima tessera valutata
        int latestCard1Face = deckCopy[indexInOrder[numbersOfElementsIndexInOrder - 1]][1];
        // Confronta la seconda faccia dell'ultima tessera con le altre tessere in deckCopy
        for (int rowCounter = 0; rowCounter < deckDimension; rowCounter++) {
            if (deckCopy[rowCounter][0] == latestCard1Face) {
                // Se la tessera è compatibile la aggiungiamo all'array indexInOrder
                indexInOrder[numbersOfElementsIndexInOrder] = rowCounter;
                // Rimuoviamo la tessera dal deck
                deckCopy[rowCounter][0] = 0;
                deckCopy[rowCounter][1] = 0;
                // Aggiorniamo il counter di elementi in ordine
                numbersOfElementsIndexInOrder++;
            } else if (deckCopy[rowCounter][1] == latestCard1Face) {
                // Se la tessera è compatibile la aggiungiamo all'array indexInOrder invertendola (aggiungendo - all'indice)
                indexInOrder[numbersOfElementsIndexInOrder] = -rowCounter;
                // Rimuoviamo la tessera dal deck
                deckCopy[rowCounter][0] = 0;
                deckCopy[rowCounter][1] = 0;
                // Aggiorniamo il counter di elementi in ordine
                numbersOfElementsIndexInOrder++;
            }
        }
    }



    // Free della memoria allocata all'array deckCopy
    for (int i = 0; i < deckDimension; i++) {
        free (deckCopy[i]);
    }
    free (deckCopy);
    return indexInOrder;
}

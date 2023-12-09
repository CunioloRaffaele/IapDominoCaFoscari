#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

// Si potrebbe rimuovere le tessere valutate dall'array di copia spostando le tessere successive di una posizione in avanti e riallocando l'array,
// ma questo causerebbe gli indici dell'array di copia a cambiare e quindi non sarebbe più possibile utilizzare l'array originale per stampare le tessere.
// Per questo motivo è stato scelto di non rimuovere le tessere valutate dall'array di copia bensì di sostituirle con un valore arbitrario '666'.

// Nella V2 vengono implementate le carte speciali e la funzione di AI viene modificata per gestirle.

bool is2dArrayEmpty(int** array, int rows) {
    int numberOfEmptyElements = 0;
    for (int i = 0; i < rows; i++) {
        if ((array[i][1] == 666 || array[i][0] == 666)) {
            numberOfEmptyElements++;
        }
    }
    if(numberOfEmptyElements == rows) {
        return true;
    } else {
        return false;
    }
}

int getIndexOfWildcard (int** deck, int deckDimension, int wildcard0, int wildcard1) {
    for (int i = 0; i < deckDimension; i++) {
        if (deck[i][0] == wildcard0 || deck[i][1] == wildcard1) {
            return i;
        }
    }
    return -1;
}

// Questa funzione serve per applicare gli effetti delle carte speciali sull'array.
// Viene restituito un nuovo array che contiene le tessere del giocatore con le carte speciali applicate.
int** arrayParser (int **deck, int deckDimension, int *indexInOrder, int numbersOfElementsIndexInOrder) {
    int** unparsedDeck = alloc_player_deck_memory(numbersOfElementsIndexInOrder);
    int** parsedDeck =   alloc_player_deck_memory(numbersOfElementsIndexInOrder);
    // Copiamo i valori di deck in unparsedDeck con indexInOrder
    for (int i = 0; i < numbersOfElementsIndexInOrder; i++) {
        unparsedDeck[i][0] = deck[indexInOrder[i]][0];
        unparsedDeck[i][1] = deck[indexInOrder[i]][1];
    }
    // Copiamo i valori di unparsedDeck in parsedDeck e modifichiamoli in base alle tessere speciali
    for (int counterDeckPosition = 0; counterDeckPosition < deckDimension; counterDeckPosition++) {

        // Gestione tessera speciale [11 | 11] (tutte le tessere precedenti vengono incrementate di 1 e la tessera speciale viene sostituita con la seconda faccia della precedente)
        if (unparsedDeck[counterDeckPosition][0] == 11 && unparsedDeck[counterDeckPosition][1] == 11) {
            // Incrementiamo tutte le tessere precedenti di 1
            for (int j = 0; j < counterDeckPosition; j++) {
                if (parsedDeck[j][0] < 6) {
                    parsedDeck[j][0] = parsedDeck[j][0] + 1;
                } else {
                    parsedDeck[j][0] = 1;
                } if (parsedDeck[j][1] < 6) {
                    parsedDeck[j][1] = parsedDeck[j][1] + 1;
                } else {
                    parsedDeck[j][1] = 1;
                }
            }
            // Copiamo la tessera speciale [11 | 11] in parsedDeck sostituendo il suo valore con la cifra della tessera precedente
            int previousCardSecondFace = parsedDeck[counterDeckPosition - 1][1];
            parsedDeck[counterDeckPosition][0] = previousCardSecondFace;
            parsedDeck[counterDeckPosition][1] = previousCardSecondFace;
        }

        // Gestione della tessera speciale [12 | 21] (copia “a specchio” la tessera adiacente)
        if (unparsedDeck[counterDeckPosition][0] == 12 && unparsedDeck[counterDeckPosition][1] == 21) {
            // Copiamo la tessera speciale [12 | 21] in parsedDeck sostituendo il suo valore con la tessera adiacente
            int previousCardFirstFace = parsedDeck[counterDeckPosition - 1][0];
            int previousCardSecondFace = parsedDeck[counterDeckPosition - 1][1];
            parsedDeck[counterDeckPosition][0] = previousCardSecondFace;
            parsedDeck[counterDeckPosition][1] = previousCardFirstFace;
        }

        // Gestione delle altre tessere
        if (unparsedDeck[counterDeckPosition][0] != 11 && unparsedDeck[counterDeckPosition][1] != 11 && unparsedDeck[counterDeckPosition][0] != 12 && unparsedDeck[counterDeckPosition][1] != 21) {
            parsedDeck[counterDeckPosition][0] = unparsedDeck[counterDeckPosition][0];
            parsedDeck[counterDeckPosition][1] = unparsedDeck[counterDeckPosition][1];
        }
    }
    // Free della memoria allocata all'array unparsedDeck
    for (int i = 0; i < numbersOfElementsIndexInOrder; i++) {
        free (unparsedDeck[i]);
    }
    free (unparsedDeck);
    return parsedDeck;
}

// Ottieni la somma di un array (ovviamente bisogna passare a questa funzione l'array già parsato)
int getSumOfArray (int** array, int arrayDimension) {
    int sum = 0;
    for (int i = 0; i < arrayDimension; i++) {
        sum = sum + array[i][0];
        sum = sum + array[i][1];
    }
    return sum;
}

int* processAI (int** deck, int deckDimension, int indexOfStartingTile, int *numbersOfElementsIndexInOrder) {
    // Creiamo una malloc contenente gli indici delle tessere da giocare in ordine
    // Gli indici negativi indicano che la tessera va girata
    // Questa malloc deve essere liberata dal chiamante della funzione
    *numbersOfElementsIndexInOrder = 0;
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
    deckCopy[indexOfStartingTile][0] = 666;
    deckCopy[indexOfStartingTile][1] = 666;
    // Aggiorniamo il counter di elementi in ordine
    *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;

    while (!is2dArrayEmpty(deckCopy, deckDimension)) {
        // Confronta la seconda faccia dell'ultima tessera con le altre tessere in deckCopy
        for (int rowCounter = 0; rowCounter < deckDimension; rowCounter++) {
            // Salviamo la seconda faccia dell'ultima tessera valutata
            int indexOfLatestCard = indexInOrder[*numbersOfElementsIndexInOrder - 1];
            // Gestiamo il caso in cui l'ultima tessera valutata è stata girata (quindi il caso in cui l'indice è negativo)
            int latestCard1Face;
            if (indexOfLatestCard < 0) {
                indexOfLatestCard = -indexOfLatestCard;
                // Dobbiamo considerare la prima faccia della tessera
                latestCard1Face = deck[indexOfLatestCard][0];
            } else {
                // Dobbiamo considerare la seconda faccia della tessera
                latestCard1Face = deck[indexOfLatestCard][1];
            }
            if (deckCopy[rowCounter][0] == latestCard1Face) {
                // Se la tessera è compatibile la aggiungiamo all'array indexInOrder
                indexInOrder[*numbersOfElementsIndexInOrder] = rowCounter;
                // Rimuoviamo la tessera dal deck
                deckCopy[rowCounter][0] = 666;
                deckCopy[rowCounter][1] = 666;
                // Aggiorniamo il counter di elementi in ordine
                *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;
            } else if (deckCopy[rowCounter][1] == latestCard1Face) {
                // Se la tessera è compatibile la aggiungiamo all'array indexInOrder invertendola (aggiungendo - all'indice)
                indexInOrder[*numbersOfElementsIndexInOrder] = -rowCounter;
                // Rimuoviamo la tessera dal deck
                deckCopy[rowCounter][0] = 666;
                deckCopy[rowCounter][1] = 666;
                // Aggiorniamo il counter di elementi in ordine
                *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;
            } else {
                // Se la tessera non è un match con la precedente faccia rimuovo deckCopy[rowCounter][0] e deckCopy[rowCounter][1]
                deckCopy[rowCounter][0] = 666;
                deckCopy[rowCounter][1] = 666;
            }
        }
    }

    // Free della memoria allocata all'array deckCopy
    for (int i = 0; i < deckDimension; i++) {
        free (deckCopy[i]);
    }
    free (deckCopy);

    // Ridimensioniamo la malloc IndexInOrder in modo che contenga solo gli n elementi indicati da *numbersOfElementsIndexInOrder
    indexInOrder = (int*) realloc (indexInOrder, sizeof(int) * *numbersOfElementsIndexInOrder);
    if (indexInOrder == NULL) {
        exit(1);
    }

    // Ritorniamo l'array contenente gli indici in ordine dell'array deck passato in argomento alla funzione
    return indexInOrder;
}

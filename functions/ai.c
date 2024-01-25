#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../functions.h"

bool verifyCompatibility4 (int prec, int succ) {
    if (prec == succ) {
        return true;
    } else if ( succ == 11 || succ == 12 || succ == 0 || prec == 0 || prec == 21 || prec == 11) {
        return true;
    } else {
        return false;
    }
}

// Si potrebbe rimuovere le tessere valutate dall'array di copia spostando le tessere successive di una posizione in avanti e riallocando l'array,
// ma questo causerebbe gli indici dell'array di copia a cambiare e quindi non sarebbe più possibile utilizzare l'array originale per stampare le tessere.
// Per questo motivo è stato scelto di non rimuovere le tessere valutate dall'array di copia bensì di sostituirle con un valore arbitrario '666'.

// Nella V2 vengono implementate le carte speciali e la funzione di AI viene modificata per gestirle.

bool is2dArrayEmpty(int **array, int rows)
{
    int numberOfEmptyElements = 0;
    for (int i = 0; i < rows; i++)
    {
        if ((array[i][1] == 666 || array[i][0] == 666))
        {
            numberOfEmptyElements++;
        }
    }
    if (numberOfEmptyElements == rows)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int getIndexOfWildcard(int **deck, int deckDimension, int wildcard0, int wildcard1)
{
    for (int i = 0; i < deckDimension; i++)
    {
        if ((deck[i][0] == wildcard0) && (deck[i][1] == wildcard1))
        {
            return i;
        }
    }
    return -1;
}

// Questa funzione serve per applicare gli effetti delle carte speciali sull'array.
// Viene restituito un nuovo array che contiene le tessere del giocatore con le carte speciali applicate.
int **arrayParser(int **deck, int *indexInOrder, int numbersOfElementsIndexInOrder)
{
    int **unparsedDeck = allocPlayerDeckMemory(numbersOfElementsIndexInOrder);
    int **parsedDeck = allocPlayerDeckMemory(numbersOfElementsIndexInOrder);
    // Copiamo i valori di deck in unparsedDeck con indexInOrder
    for (int i = 0; i < numbersOfElementsIndexInOrder; i++)
    {
        if (indexInOrder[i] < 0)
        {
            unparsedDeck[i][0] = deck[-indexInOrder[i]][1];
            unparsedDeck[i][1] = deck[-indexInOrder[i]][0];
        }
        else
        {
            unparsedDeck[i][0] = deck[indexInOrder[i]][0];
            unparsedDeck[i][1] = deck[indexInOrder[i]][1];
        }
    }
    // Copiamo i valori di unparsedDeck in parsedDeck e modifichiamoli in base alle tessere speciali
    for (int counterDeckPosition = 0; counterDeckPosition < numbersOfElementsIndexInOrder; counterDeckPosition++)
    {

        // Gestione tessera speciale [11 | 11] (tutte le tessere precedenti vengono incrementate di 1 e la tessera speciale viene sostituita con la seconda faccia della precedente)
        if (unparsedDeck[counterDeckPosition][0] == 11 && unparsedDeck[counterDeckPosition][1] == 11)
        {
            // Incrementiamo tutte le tessere precedenti di 1
            for (int j = 0; j < counterDeckPosition; j++)
            {
                if (parsedDeck[j][0] < 6)
                {
                    parsedDeck[j][0] = parsedDeck[j][0] + 1;
                }
                else
                {
                    parsedDeck[j][0] = 1;
                }
                if (parsedDeck[j][1] < 6)
                {
                    parsedDeck[j][1] = parsedDeck[j][1] + 1;
                }
                else
                {
                    parsedDeck[j][1] = 1;
                }
            }
            // Copiamo la tessera speciale [11 | 11] in parsedDeck sostituendo il suo valore con la cifra della tessera precedente
            int previousCardSecondFace = 0;
            if (counterDeckPosition != 0)
            {
                previousCardSecondFace = parsedDeck[counterDeckPosition - 1][1];
            }
            parsedDeck[counterDeckPosition][0] = previousCardSecondFace;
            parsedDeck[counterDeckPosition][1] = previousCardSecondFace;
        }

        // Gestione della tessera speciale [12 | 21] (copia “a specchio” la tessera adiacente)
        if (unparsedDeck[counterDeckPosition][0] == 12 && unparsedDeck[counterDeckPosition][1] == 21)
        {
            // Copiamo la tessera speciale [12 | 21] in parsedDeck sostituendo il suo valore con la tessera adiacente
            int previousCardFirstFace = 0;
            int previousCardSecondFace = 0;
            if (counterDeckPosition != 0)
            {
                previousCardFirstFace = parsedDeck[counterDeckPosition - 1][0];
                previousCardSecondFace = parsedDeck[counterDeckPosition - 1][1];
            }
            parsedDeck[counterDeckPosition][0] = previousCardSecondFace;
            parsedDeck[counterDeckPosition][1] = previousCardFirstFace;
        }

        // Gestione delle altre tessere
        if (unparsedDeck[counterDeckPosition][0] != 11 && unparsedDeck[counterDeckPosition][1] != 11 && unparsedDeck[counterDeckPosition][0] != 12 && unparsedDeck[counterDeckPosition][1] != 21)
        {
            parsedDeck[counterDeckPosition][0] = unparsedDeck[counterDeckPosition][0];
            parsedDeck[counterDeckPosition][1] = unparsedDeck[counterDeckPosition][1];
        }
    }
    // Free della memoria allocata all'array unparsedDeck
    for (int i = 0; i < numbersOfElementsIndexInOrder; i++)
    {
        free(unparsedDeck[i]);
    }
    free(unparsedDeck);
    return parsedDeck;
}

// Ottieni la somma di un array (ovviamente bisogna passare a questa funzione l'array già parsato)
int getSumOfArray(int **array, int arrayDimension)
{
    int sum = 0;
    for (int i = 0; i < arrayDimension; i++)
    {
        sum = sum + array[i][0];
        sum = sum + array[i][1];
    }
    return sum;
}

int *processAI(int **deck, int deckDimension, int indexOfStartingTile, int *numbersOfElementsIndexInOrder)
{
    // Creiamo una malloc contenente gli indici delle tessere da giocare in ordine
    // Gli indici negativi indicano che la tessera va girata
    // Questa malloc deve essere liberata dal chiamante della funzione
    *numbersOfElementsIndexInOrder = 0;
    int *indexInOrder = (int *)malloc(sizeof(int) * deckDimension);
    if (indexInOrder == NULL)
    {
        exit(1);
    }

    // Creiamo una copia privata della malloc contenente il deck in modo da poter
    // rimuovere le tessere valutate senza intervenire sull'array originale.
    // Questa malloc va liberata alla fine della funzione.
    int **deckCopy = allocPlayerDeckMemory(deckDimension);

    // Copiamo i valori di deck in deckCopy

    for (int i = 0; i < deckDimension; i++)
    {
        deckCopy[i][0] = deck[i][0];
        deckCopy[i][1] = deck[i][1];
    }

    // Il primo index da salvare è quello della tessera iniziale
    indexInOrder[0] = indexOfStartingTile;
    // Rimuoviamo la tessera iniziale dal deck
    deckCopy[indexOfStartingTile][0] = 666;
    deckCopy[indexOfStartingTile][1] = 666;
    // Verifichiamo se abbiamo tessere speciali disponibili
    // Aggiorniamo il counter di elementi in ordine
    *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;
    while (!is2dArrayEmpty(deckCopy, deckDimension))
    {
        // Confronta la seconda faccia dell'ultima tessera con le altre tessere in deckCopy
        for (int rowCounter = 1; rowCounter < deckDimension; rowCounter++)
        {
            // Salviamo la seconda faccia dell'ultima tessera valutata
            int indexOfLatestCard = indexInOrder[*numbersOfElementsIndexInOrder - 1];
            // Gestiamo il caso in cui l'ultima tessera valutata è stata girata (quindi il caso in cui l'indice è negativo)
            int latestCard1Face;
            if (indexOfLatestCard < 0)
            {
                // Dobbiamo considerare la prima faccia della tessera
                // Qui non serve fare il parsing perchè una tessera flippata non può essere una tessera speciale.
                latestCard1Face = deck[-indexOfLatestCard][0];
            }
            else
            {
                // Dobbiamo considerare la seconda faccia della tessera
                int **temp = arrayParser(deck, indexInOrder, *numbersOfElementsIndexInOrder);
                latestCard1Face = temp[*numbersOfElementsIndexInOrder - 1][1];
            }
            int index00 = getIndexOfWildcard(deckCopy, deckDimension, 0, 0);
            int index1111 = getIndexOfWildcard(deckCopy, deckDimension, 11, 11);
            int index1221 = getIndexOfWildcard(deckCopy, deckDimension, 12, 21);
            int sumOf00 = 0;
            int sumOf1111 = 0;
            int sumOf1221 = 0;
            int sumOfMatch = 0;
            int maxSum = 0;
            int indexOfMaxSum = 0;
            if (deckCopy[rowCounter][0] != 666 && deckCopy[rowCounter][1] != 666)
            {
                if (latestCard1Face == 0)
                {
                    indexInOrder[*numbersOfElementsIndexInOrder] = rowCounter;
                    *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;
                    // Rimuoviamo la tessera dal deck
                    deckCopy[rowCounter][0] = 666;
                    deckCopy[rowCounter][1] = 666;
                }
                else if (deckCopy[rowCounter][0] == latestCard1Face)
                {
                    // Se la tessera è compatibile abbiamo 2 opzioni:
                    // - la aggiungiamo all'array indexInOrder
                    // - valutiamo la possibilità di aggiungere all'array indexInOrder una tessera speciale se dipsonibile
                    if (index00 > 0)
                    {
                        indexInOrder[*numbersOfElementsIndexInOrder] = index00;
                        int **temp = arrayParser(deck, indexInOrder, *numbersOfElementsIndexInOrder + 1);
                        sumOf00 = getSumOfArray(temp, *numbersOfElementsIndexInOrder + 1);
                        for (int i = 0; i < *numbersOfElementsIndexInOrder + 1; i++)
                        {
                            free(temp[i]);
                        }
                        free(temp);
                        if (sumOf00 > maxSum)
                        {
                            maxSum = sumOf00;
                            indexOfMaxSum = index00;
                        }
                    }
                    if (index1111 > 0)
                    {
                        indexInOrder[*numbersOfElementsIndexInOrder] = index1111;
                        int **temp = arrayParser(deck, indexInOrder, *numbersOfElementsIndexInOrder + 1);
                        sumOf1111 = getSumOfArray(temp, *numbersOfElementsIndexInOrder + 1);
                        for (int i = 0; i < *numbersOfElementsIndexInOrder + 1; i++)
                        {
                            free(temp[i]);
                        }
                        free(temp);
                        if (sumOf1111 > maxSum)
                        {
                            maxSum = sumOf1111;
                            indexOfMaxSum = index1111;
                        }
                    }
                    if (index1221 > 0)
                    {
                        indexInOrder[*numbersOfElementsIndexInOrder] = index1221;
                        int **temp = arrayParser(deck, indexInOrder, *numbersOfElementsIndexInOrder + 1);
                        sumOf1221 = getSumOfArray(temp, *numbersOfElementsIndexInOrder + 1);
                        for (int i = 0; i < *numbersOfElementsIndexInOrder + 1; i++)
                        {
                            free(temp[i]);
                        }
                        free(temp);
                        if (sumOf1221 > maxSum)
                        {
                            maxSum = sumOf1221;
                            indexOfMaxSum = index1221;
                        }
                    }
                    indexInOrder[*numbersOfElementsIndexInOrder] = rowCounter;
                    int **temp = arrayParser(deck, indexInOrder, *numbersOfElementsIndexInOrder + 1);
                    sumOfMatch = getSumOfArray(temp, *numbersOfElementsIndexInOrder + 1);
                    for (int i = 0; i < *numbersOfElementsIndexInOrder + 1; i++)
                    {
                        free(temp[i]);
                    }
                    free(temp);
                    if (sumOfMatch > maxSum)
                    {
                        maxSum = sumOfMatch;
                        indexOfMaxSum = rowCounter;
                    }

                    indexInOrder[*numbersOfElementsIndexInOrder] = indexOfMaxSum;
                    // Rimuoviamo la tessera dal deck
                    deckCopy[indexOfMaxSum][0] = 666;
                    deckCopy[indexOfMaxSum][1] = 666;
                    // Aggiorniamo il counter di elementi in ordine
                    *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;
                }
                else if (deckCopy[rowCounter][1] == latestCard1Face)
                {
                    // Se la tessera è compatibile abbiamo 2 opzioni:
                    // - la aggiungiamo all'array indexInOrder
                    // - valutiamo la possibilità di aggiungere all'array indexInOrder una tessera speciale se dipsonibile
                    if (index00 > 0)
                    {
                        indexInOrder[*numbersOfElementsIndexInOrder] = index00;
                        int **temp = arrayParser(deck, indexInOrder, *numbersOfElementsIndexInOrder + 1);
                        sumOf00 = getSumOfArray(temp, *numbersOfElementsIndexInOrder + 1);
                        for (int i = 0; i < *numbersOfElementsIndexInOrder + 1; i++)
                        {
                            free(temp[i]);
                        }
                        free(temp);
                        if (sumOf00 > maxSum)
                        {
                            maxSum = sumOf00;
                            indexOfMaxSum = -index00;
                        }
                    }
                    if (index1111 > 0)
                    {
                        indexInOrder[*numbersOfElementsIndexInOrder] = index1111;
                        int **temp = arrayParser(deck, indexInOrder, *numbersOfElementsIndexInOrder + 1);
                        sumOf1111 = getSumOfArray(temp, *numbersOfElementsIndexInOrder + 1);
                        for (int i = 0; i < *numbersOfElementsIndexInOrder + 1; i++)
                        {
                            free(temp[i]);
                        }
                        free(temp);
                        if (sumOf1111 > maxSum)
                        {
                            maxSum = sumOf1111;
                            indexOfMaxSum = -index1111;
                        }
                    }
                    if (index1221 > 0)
                    {
                        indexInOrder[*numbersOfElementsIndexInOrder] = index1221;
                        int **temp = arrayParser(deck, indexInOrder, *numbersOfElementsIndexInOrder + 1);
                        sumOf1221 = getSumOfArray(temp, *numbersOfElementsIndexInOrder + 1);
                        for (int i = 0; i < *numbersOfElementsIndexInOrder + 1; i++)
                        {
                            free(temp[i]);
                        }
                        free(temp);
                        if (sumOf1221 > maxSum)
                        {
                            maxSum = sumOf1221;
                            indexOfMaxSum = -index1221;
                        }
                    }
                    indexInOrder[*numbersOfElementsIndexInOrder] = rowCounter;
                    int **temp = arrayParser(deck, indexInOrder, *numbersOfElementsIndexInOrder + 1);
                    sumOfMatch = getSumOfArray(temp, *numbersOfElementsIndexInOrder + 1);
                    for (int i = 0; i < *numbersOfElementsIndexInOrder + 1; i++)
                    {
                        free(temp[i]);
                    }
                    free(temp);
                    if (sumOfMatch > maxSum)
                    {
                        maxSum = sumOfMatch;
                        indexOfMaxSum = rowCounter;
                    }

                    indexInOrder[*numbersOfElementsIndexInOrder] = -indexOfMaxSum;
                    // Rimuoviamo la tessera dal deck
                    deckCopy[indexOfMaxSum][0] = 666;
                    deckCopy[indexOfMaxSum][1] = 666;
                    // Aggiorniamo il counter di elementi in ordine
                    *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;
                }
                else
                {
                    // Gestire il caso in cui non ci sono tessere compatibili
                    if (index00 > 0)
                    {
                        indexInOrder[*numbersOfElementsIndexInOrder] = index00;
                        *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;
                        // Rimuoviamo la tessera dal deck
                        deckCopy[index00][0] = 666;
                        deckCopy[index00][1] = 666;
                    }
                    else if (index1111 > 0)
                    {

                        indexInOrder[*numbersOfElementsIndexInOrder] = index1111;
                        *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;
                        deckCopy[index1111][0] = 666;
                        deckCopy[index1111][1] = 666;
                    }
                    else if (index1221 > 0)
                    {
                        indexInOrder[*numbersOfElementsIndexInOrder] = index1221;
                        *numbersOfElementsIndexInOrder = *numbersOfElementsIndexInOrder + 1;
                        deckCopy[index1221][0] = 666;
                        deckCopy[index1221][1] = 666;
                    }
                    else
                    {
                        // Se la tessera non è un match con la precedente faccia rimuovo deckCopy[rowCounter][0] e deckCopy[rowCounter][1]
                        deckCopy[rowCounter][0] = 666;
                        deckCopy[rowCounter][1] = 666;
                    }
                }
            }
        }
    }

    // Free della memoria allocata all'array deckCopy
    for (int i = 0; i < deckDimension; i++)
    {
        free(deckCopy[i]);
    }
    free(deckCopy);

    // Ridimensioniamo la malloc IndexInOrder in modo che contenga solo gli n elementi indicati da *numbersOfElementsIndexInOrder
    indexInOrder = (int *)realloc(indexInOrder, sizeof(int) * *numbersOfElementsIndexInOrder);
    if (indexInOrder == NULL)
    {
        exit(1);
    }

    return indexInOrder;
}

int aiEvaluation(int **deck, int deckDimension)
{
    int numbersOfElementsIndexInOrder;
    int maxSum = 0;
    int result = 0;
    for (int counter = 0; counter < deckDimension; counter++)
    {
        printf("Counter %d\n", counter);
        int *partialResult = processAI(deck, deckDimension, counter, &numbersOfElementsIndexInOrder);
        int **parsedArray = arrayParser(deck, partialResult, deckDimension);
        int partialSum = getSumOfArray(parsedArray, numbersOfElementsIndexInOrder);
        if (maxSum < partialSum)
        {
            maxSum = partialSum;
            result = counter;
        }
    }
    return result;
}

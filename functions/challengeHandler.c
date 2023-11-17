#include <stdio.h>
#include <stdbool.h>

//Questa funzione, preso l'array contenentele gli indici delle tiles ordinante, cerca la tile corrispondente nel deck e le stampa nel corretto ordine
void printCardsForChallenge(int** playerDeck, int* AiResult, int processAIDimension) {
    bool isFirst = true;
    for (int i = 0; i < processAIDimension; i++) {
        if (AiResult[i] < 0) {
            int index = -AiResult[i];
            if (isFirst) {
                printf("S ");
                printf("%d %d ", playerDeck[index][1], playerDeck[index][0]);
                isFirst = false;
            } else {
                printf("R ");
                printf("%d %d ", playerDeck[index][1], playerDeck[AiResult[i]][0]);
            }
        } else {
            int index = AiResult[i];
            if (isFirst) {
                printf("S ");
                printf("%d %d ", playerDeck[index][1], playerDeck[index][0]);
                isFirst = false;
            } else {
                printf("R ");
                printf("%d %d ", playerDeck[index][0], playerDeck[index][1]);
            }
        }
    }

}
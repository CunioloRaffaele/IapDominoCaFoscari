#include <stdio.h>
#include <stdbool.h>
#include "../fragments.h"

extern int** playerDeck;
extern int playerDeckDimension;

void fragment2 (bool animation, int gameSet[21][2]) {
    spawnScreenWithTitle("OTTIENI TILE", animation);
    colorzz(2);
    printf("| 1      -  Ottieni tile\n");
    printf("| Altro  -  Torna al menu precedente\n\n\n");
    int option = getch();
    switch (option)
    {
    case ASCII_1:
        jump:
        printf("Inserisci il numero di tiles che vuoi ottenere (array generato con malloc quindi fai la dimensione che vuoi): ");
        scanf("%d", &playerDeckDimension);
        if (playerDeckDimension <= 0) {
            colorzz(1);
            printf("Non puoi inserire un numero negativo o 0.\n");
            colorzz(2);
            goto jump;
        } else {
            fflush(stdin);   // Pulisce il buffer di input per evitare che scanf legga caratteri non voluti tipo enter
            playerDeck = allocPlayerDeckMemory(playerDeckDimension);
            generatePlayerDeck(gameSet, playerDeck, playerDeckDimension);
            printf("Tiles generate con successo!\n");
            for (int counter = 0; counter < playerDeckDimension; counter ++) {
                printf("%d %d\n", playerDeck[counter][0], playerDeck[counter][1]);
            }
            menuUi();
        }
        break;
    default:
        menuUi();
    }
    colorzz(0);
}

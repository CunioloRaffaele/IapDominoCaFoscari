#include <stdio.h>
#include <stdbool.h>

void fragment2 (int **playerDeck,  bool animation) {
    spawn_screen_with_title("OTTIENI TILE", animation);
    colorzz(2);
    printf("| 1      -  Ottieni tile\n");
    printf("| Altro  -  Torna al menu precedente\n\n\n");
    int option = getch();
    switch (option)
    {
    case ASCII_1:
        jump:
        printf("Inserisci il numero di tiles che vuoi ottenere (array generato con malloc quindi fai la dimensione che vuoi): ");
        int deckDimension;
        scanf("%d", &deckDimension);
        if (deckDimension <= 0) {
            colorzz(1);
            printf("Non puoi inserire un numero negativo o 0.\n");
            colorzz(2);
            goto jump;
        } else {
            playerDeck = alloc_player_deck_memory (deckDimension);
            fflush(stdin);   // Pulisce il buffer di input per evitare che scanf legga caratteri non voluti tipo enter
            // TODO: Aggiungere la funzione che genera le tiles da assegnare al player randomicamente
            //       Mettere la funzione in functions/initialization.c
            menuUi();
        }
        break;
    default:
        menuUi();
    }
    colorzz(0);
}
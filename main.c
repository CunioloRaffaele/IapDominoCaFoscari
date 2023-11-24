// 901146 903407 902939 902406

// Compila il programma con "make run"

#include <stdio.h>
#include <string.h>
#include "functions.h"

// Creiamo un array multidimensionale per contenere le 21 tessere possibili ciascuna con una coppia di numeri da 1 a 6.
// L'array contiene 20 tessere che hanno ciascuna due facce (top bottom nella funzione 'spawn_tile')
// Se vuoi conoscere la due facce di tessera devi printare gameSet [indice] [0] e gameSet [indice] [1] 
int gameSet [20][2];
// Puntatore di memoria all'array multidimensionale contenente le tessere del giocatore
int **playerDeck;

void menuUi () {
    spawn_screen_with_title("MENU");
    int menuOption;
    colorzz(2);
    printf("| 1      -  Visualizza i possibili tiles che ti potrebbero essere asegnati\n");
    printf("| 2      -  Ottieni un numero N di tiles\n");
    printf("| 3      -  Visualizza le tue tiles\n");
    printf("| Altro  -  Esci\n");
    printf("\n\n Seleziona un'opzione tra le presentate: ");
    scanf("%d", &menuOption);
    switch (menuOption)
    {
    case 1:
        spawn_screen_with_title("21 TESSERE");
        
        for (int counter = 0; counter <= 3; counter ++) {
            spawn_tile(gameSet[counter][0], gameSet[counter][1], 18*counter);
        }
        sleep(10);
        menuUi();
        break;
    case 2:
        spawn_screen_with_title("OTTIENI TILES");
        break;
    case 3:
        spawn_screen_with_title("I MIEI TILES");
        break;
    default:
        break;
    }
    //generate_player_deck(playerTiles, 21);
    colorzz(0);
}

void challengeMode () {
    // Creazione dell'array contenente i tiles del player e inserimento dei dati.
    int deckDimension = 0;
    scanf("%d", & deckDimension);
    int** playerDeck = alloc_player_deck_memory (deckDimension);
    for (int counter = 0; counter < deckDimension; counter ++) {
        scanf("%d %d", &playerDeck[counter][0], &playerDeck[counter][1]);
    }
    int processAIDimension; // Questa variabile viene passarta come puntatore e conterrà la dimensione dell'array di output della funzione AiResult()
    int* AiResult = processAI(playerDeck, deckDimension, 0, &processAIDimension);

    printCardsForChallenge(playerDeck, AiResult, processAIDimension);

    // Free della memoria allocata all'array contenente il risultato dell'ai
    free (AiResult);
    // Free della memoria allocata all'array contenente i tiles del player
    for (int i = 0; i < deckDimension; i++) {
        free (playerDeck[i]);
    }
    free (playerDeck);
    exit(0);
}
    

int main(int argc, char* argv[]) {
    // Avvio
    for (int i = 0; i< argc; i++) {
        if ((strcmp((argv[i]), "--challenge")) == 0) {
            challengeMode();
        }
    }
    clear_console();
    introMessage();
    getchar();
    clear_console();

    // Preparazione variabili necessarie
    generate_tiles_composition(gameSet);

    // Menu
    menuUi();

    clear_console();
    introMessage();
    printf("\n\nGrazie per aver usato Domino\n\n");
    return 0;
}
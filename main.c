// 901146 903407 902406

// Compila il programma con "make run"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include "fragments.h"

// Creiamo un array multidimensionale per contenere le 21 tessere possibili ciascuna con una coppia di numeri da 1 a 6.
// L'array contiene 20 tessere che hanno ciascuna due facce (top bottom nella funzione 'spawnTile')
// Se vuoi conoscere la due facce di tessera devi printare gameSet [indice] [0] e gameSet [indice] [1] 
int gameSet [21][2];
// Puntatore di memoria all'array multidimensionale contenente le tessere del giocatore
int **playerDeck;
int playerDeckDimension = 0;

void menuUi (void) {
    spawnScreenWithTitle("MENU", true);
    int menuOption;
    colorzz(2);
    printf("| 1      -  Visualizza i possibili tiles che ti potrebbero essere asegnati \n            (compresi quelli speciali)\n");
    if (playerDeck == NULL) {
        printf("| 2      -  Ottieni un numero N di tiles\n");
        colorzz(1);
        printf("Le opzioni seguenti non sono attualmente disponibili\nChiama il programma con la flag --challenge o genera un deck con opzione 2.\n");
    } else {
        colorzz(1);
        printf("| 2      -  Ottieni un numero N di tiles\nOpzione 2 non disponibile in quanto sono già state assegnate le tiles al giocatore.\n");
        colorzz(2);
    }
    printf("| 3      -  Visualizza le tue tiles\n");
    printf("| 4      -  Gioca a Domino\n");
    printf("| 5      -  Gioca a 2D Domino\n\n");
    colorzz(2);
    printf("| Altro  -  Esci\n");
    printf("\n\n Seleziona un'opzione tra le presentate digitando il numero corrispondente");
    //scanf("%d", &menuOption);
    menuOption = getch();
    switch (menuOption)
    {
    case ASCII_1:
        fragment1(gameSet, 0, 0, true);
        break;
    case ASCII_2:
        if (playerDeck == NULL) {
            fragment2(true, gameSet);
        }
        break;
    case ASCII_3:
        if (playerDeck == NULL) {
            menuUi();
        }else {
            fragment3(playerDeck, 0, 0, true, playerDeckDimension);
        }
        break;
    case ASCII_4:
        if (playerDeck == NULL) {
            menuUi();
        }else {}
        break;
    case ASCII_5:
        if (playerDeck == NULL) {
            menuUi();
        }else {}
        break;
    default:
        break;
    }
    //generatePlayerDeck(playerTiles, 21);
    colorzz(0);
}

void challengeMode (void) {
    // Creazione dell'array contenente i tiles del player e inserimento dei dati.
    scanf("%d", & playerDeckDimension);
    int** playerDeck = allocPlayerDeckMemory (playerDeckDimension);
    for (int counter = 0; counter < playerDeckDimension; counter ++) {
        scanf("%d %d", &playerDeck[counter][0], &playerDeck[counter][1]);
    }
    //int bestStartingTile = aiEvaluation(playerDeck, playerDeckDimension);
    int processAIDimension; // Questa variabile viene passarta come puntatore e conterrà la dimensione dell'array di output della funzione AiResult()
    int* AiResult = processAI(playerDeck, playerDeckDimension, 0, &processAIDimension);

    printCardsForChallenge(playerDeck, AiResult, processAIDimension);

    // Free della memoria allocata all'array contenente il risultato dell'ai
    free (AiResult);
    // Free della memoria allocata all'array contenente i tiles del player
    for (int i = 0; i < playerDeckDimension; i++) {
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
    clearConsole();
    introMessage();
    getchar();
    clearConsole();

    // Preparazione variabili necessarie
    generateTilesComposition(gameSet);

    // Menu
    menuUi();
/*
    clearConsole();
    introMessage();
    printf("\n\nGrazie per aver usato Domino\n\n");*/
    return 0;
}

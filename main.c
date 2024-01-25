// 901146 903407 902406

/**
* @file main.c
* @author Barison Alberto 901146, Cuniolo Raffaele 903407, Veggis Francesco 902406
* @mainpage main C Domino Iap 2024
* @section intro_sec Introduzione
*
* Questo programma in C implementa una versione del gioco "Domino" con una serie di funzionalità che si adattano sia al gameplay standard che a modallità più complesse come il gameplay automatico e il domino su due dimensioni. Il programma, nel menù principale, include opzioni per visualizzare le tessere, ottenere tessere, giocare al Domino standard e giocare al Domino 2D. Inoltre è stata inclusa una modalità di debug dell'algoritmo di gampeplay automatico richiamabile con "--challenge".
* Il progetto è open source (https://github.com/CunioloRaffaele/IapDominoCaFoscari.git) con licenza MIT.
*
* @section install_sec Compilazione
* @subsection step1 Step 1: Installa gcc o clang
* @subsection step2 Step 2: Clona il repository con gh repo clone CunioloRaffaele/IapDominoCaFoscari
* @subsection step3 Step 3: Esegui il comando: gcc -O2 -std=c99 --pedantic *.c ./fragments/ *.c ./functions/ *.c -o iap
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include "fragments.h"

/**
Creiamo un array multidimensionale per contenere le 21 tessere possibili ciascuna con una coppia di numeri da 1 a 6.
L'array contiene 20 tessere che hanno ciascuna due facce (top bottom nella funzione 'spawnTile')
Se vuoi conoscere la due facce di tessera devi printare gameSet [indice] [0] e gameSet [indice] [1]
*/
int gameSet [21][2];
/**
Puntatore di memoria all'array multidimensionale contenente le tessere del giocatore (nell'orgine generato casualmente... Vanno ordinate per indice, senza variare playerDeck).
*/
int **playerDeck;
/**
Dimensione di **playerDeck
*/
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
            showAlert("Questa opzione è disponibile solo dopo aver generato un deck di tiles.");
            menuUi();
        }else {
            fragment3(playerDeck, 0, 0, true, playerDeckDimension);
        }
        break;
    case ASCII_4:
        if (playerDeck == NULL) {
            showAlert("Questa opzione è disponibile solo dopo aver generato un deck di tiles.");
            menuUi();
        }else {
            fragment4(playerDeck, 0, 0, true, playerDeckDimension, NULL);
        }
        break;
    case ASCII_5:
        if (playerDeck == NULL) {
            showAlert("Questa opzione è disponibile solo dopo aver generato un deck di tiles.");
            menuUi();
        }else {
            fragment5(playerDeck, playerDeckDimension);
        }
        break;
    default:
        break;
    }
    //generatePlayerDeck(playerTiles, 21);
    colorzz(4);
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
        // The return value from strcmp is 0 if the two strings are equal, less than 0 if str1 compares less than str2 , and greater than 0 if str1 compares greater than str2
        if ((strcmp((argv[i]), "--challenge")) == 0) {
            challengeMode();
        }
        if ((strcmp((argv[i]), "--debugging")) == 0) {
            spawnScreenWithTitle("Debugging status", false);
            playerDeckDimension = 4;
            playerDeck = allocPlayerDeckMemory(playerDeckDimension);
            generateTilesComposition(gameSet);
            generatePlayerDeck(gameSet, playerDeck, playerDeckDimension);
            printf("Tiles generate con successo!\n");
            for (int counter = 0; counter < playerDeckDimension; counter ++) {
                printf("%d %d\n", playerDeck[counter][0], playerDeck[counter][1]);
            }
            printf("Mosse AI\n");
            int processAIDimension; // Questa variabile viene passarta come puntatore e conterrà la dimensione dell'array di output della funzione AiResult()
            int* AiResult = processAI(playerDeck, playerDeckDimension, 0, &processAIDimension);
            printf("AI dimension = %d\n", processAIDimension);
            printCardsForChallenge(playerDeck, AiResult, processAIDimension);
            getchar();
            clearConsole();
            menuUi();
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

    clearConsole();
    exitMessage();
    return 0;
}

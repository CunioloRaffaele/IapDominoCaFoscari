// Compila il programma con "make run"

#include <stdio.h>
#include "functions.h"

// Creiamo un array multidimensionale per contenere le 21 tessere possibili ciascuna con una coppia di numeri da 1 a 6.
int gameSet [20][2];
// Creiamo un array contenente l'indice dell'array gameSet contenente le tessere in possesso del player.
int playerTiles [21];

void start () {
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
        for (int counter = 0; counter <= 20; counter ++) {
            printf("(%d , ", gameSet [counter][0]);
            printf("%d) \n", gameSet [counter][1]);
            spawn_tile(gameSet[counter][0], gameSet[counter][1]);
        }
        sleep(10);
        start();
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
    

int main() {
    // Avvio
    clear_console();
    introMessage();
    getchar();
    clear_console();

    // Preparazione variabili necessarie
    generate_tiles_composition(gameSet);

    // Menu
    start();

    clear_console();
    introMessage();
    printf("\n\nGrazie per aver usato Domino\n\n");
    return 0;
}
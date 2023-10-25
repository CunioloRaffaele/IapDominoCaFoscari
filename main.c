// Compila il programma con "make run"

#include <stdio.h>
#include "functions.h"

// Creiamo un array multidimensionale per contenere le 21 tessere possibili ciascuna con una coppia di numeri da 1 a 6.
int gameSet [6][6];
// Creiamo un array contenente l'indice dell'array gameSet contenente le tessere in possesso del player.
int playerTiles [21];
    
int main() {
    colorzz(3);
    printf("----------------------------------------------------------\n");
    printf("------------- Benvenuto nel programma domino -------------\n");
    printf("----------------------------------------------------------\n");
    printf("-------------------     Credits:     ---------------------\n");
    printf("--------------------     903407     ----------------------\n"); 
    printf("--------------------     901146     ----------------------\n"); 
    printf("--------------------     902939     ----------------------\n"); 
    printf("--------------------     902406     ----------------------\n");
    printf("----------------------------------------------------------\n");
    printf("-------------   Università Ca’ Foscari   -----------------\n");
    printf("----------------------------------------------------------\n");
    colorzz(0);
    
    initialization(playerTiles, 21);


    return 0;
}
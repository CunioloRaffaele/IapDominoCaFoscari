#include <stdio.h>
#include <stdbool.h>
#include "../fragments.h"

void fragment1(int gameSet[20][2], int startingTileIndex, int selectedTileIndex, bool animation) {
    spawn_screen_with_title("21 TESSERE", animation);
    colorzz(2);
    printf("| A      -  Scorri le tiles a sinistra (una alla volta)\n");
    printf("| D      -  Scorri le tiles a destra (una alla volta)\n");
    printf("| Altro  -  Torna al menu precedente\n\n\n");
    colorzz(0);

    // Controllo di quante tiles stanno orizzontalmente nel terminale.
    // Una tile occupa 18 caratteri (18 colonne)
    int tilesPerScreen = screen_col() / 18;
    int columnToSpawn = 0;
    for (int counter = startingTileIndex; counter < tilesPerScreen+ startingTileIndex; counter ++) {
        spawn_tile(gameSet[counter][0], gameSet[counter][1], 18*columnToSpawn, selectedTileIndex == counter);
        columnToSpawn++;
    }
    printf("\033[12B\n");
    //printf("%d %d\n\n", startingTileIndex, startingTileIndex + tilesPerScreen);
    printf("In game potrai usare altre tre tessere speciali:\n\n");
    printf("[0|0]     può essere accostata a qualunque altra tessera. Esempio: [1|2][0|0][5|6]\n");
    printf("[11|11]   somma 1 a tutte le cifre di tutte le tessere sul piano di gioco tranne il 6\n          che diventa 1. La tessera può essere posizionata in qualunque posizione e \n          le sue cifre vegono sostituite con la cifra adiacente dopo averla incrementata di 1. \n          Esempio: [1|6][6|3][11|11] diventa [2|1][1|4][4|4]\n");
    printf("[12|21]   copia “a specchio” la tessera adiacente. La tessera può essere posizionata in \n          qualunque posizione e le sue cifre vegono sostituite con le cifre della tessera \n          adiacente in ordine inverso. Esempio: [1|2][2|3][12|21] diventa [1|2][2|3][3|2]\n");

    int input = getch();
    switch (input)
    {
    case ASCII_A:
        if (startingTileIndex ==  0) {
            if ((selectedTileIndex - 1) >= 0) {
                selectedTileIndex --;
            }
            fragment1(gameSet, 0, selectedTileIndex, false);
        } else {
            fragment1(gameSet, startingTileIndex - 1, selectedTileIndex - 1, false);
        }
        break;
    case ASCII_D:
        if ((startingTileIndex + tilesPerScreen) >=  21) {
            if ((selectedTileIndex + 1) < 21) {
                selectedTileIndex ++;
            }
            fragment1(gameSet, 21 - tilesPerScreen, selectedTileIndex, false);
        } else {
            fragment1(gameSet, startingTileIndex + 1, startingTileIndex + 1, false);
        }
        break;
    default:
        menuUi();
        break;
    }
}

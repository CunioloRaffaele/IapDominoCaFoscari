#include <stdio.h>
#include <stdbool.h>

void fragment1(int gameSet[20][2], int startingTile) {
    spawn_screen_with_title("21 TESSERE", false);
    colorzz(2);
    printf("| A      -  Scorri le tiles a sinistra\n");
    printf("| D      -  Scorri le tiles a destra\n");
    printf("| Altro  -  Torna al menu precedente\n\n\n");
    colorzz(0);

    // Controllo di quante tiles stanno orizzontalmente nel terminale.
    // Una tile occupa 18 caratteri (18 colonne)
    int tilesPerScreen = screen_col() / 18;
    for (int counter = startingTile; counter < tilesPerScreen; counter ++) {
        spawn_tile(gameSet[counter][0], gameSet[counter][1], 18*counter, false);
    }
    printf("\n");

    int input = getch();
    switch (input)
    {
    case ASCII_A:
        if ((startingTile - tilesPerScreen) < 0) {
            fragment1(gameSet, 0);
        } else {
            fragment1(gameSet, startingTile - tilesPerScreen);
        }
        printf("CiaoA\n");
        break;
    case ASCII_D:
        fragment1(gameSet, startingTile + tilesPerScreen);
        printf("CiaoD\n");
        break;
    default:
    printf("Ciao\n");
        break;
    }
}

#include <stdio.h>
#include <stdbool.h>

#include "../functions.h"

void spawnTile (int top, int bottom, int column, bool isSelected) {
   if (isSelected) {
        colorzz(1);
    }
    printf("\n\033[%dC", column);
    printf("        //\\     \n\033[%dC", column);
    printf("       //  \\    \n\033[%dC", column);
    if (top > 9){
        printf("      // ");
    } else {
        printf("      //  ");
    }
    printf("%d", top);
    printf(" \\   \n\033[%dC", column);
    printf("     //\\    /   \n\033[%dC", column);
    printf("    //  \\  /    \n\033[%dC", column);
    printf("   //    \\/     \n\033[%dC", column);
    if (bottom > 9) {
        printf("   \\ ");
    } else {
        printf("   \\  ");
    }
    printf("%d", bottom);
    printf("  /       \n\033[%dC", column);
    printf("    \\   /        \n\033[%dC", column);
    printf("     \\ /         \n\033[%dC", column);
    printf("\033[10A"); // Sposta il cursore alla riga di partenza della stampa (10 caratteri piu' in alto));
    if (isSelected) {
        colorzz(0);
    }
}

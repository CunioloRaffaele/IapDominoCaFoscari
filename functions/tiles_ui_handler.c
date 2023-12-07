#include <stdio.h>
#include <stdbool.h>

void spawn_tile (int top, int bottom, int column, bool isSelected) {
   if (isSelected) {
        colorzz(1);
    }
    printf("\n\033[%dC", column);
    printf("        //\\     \n\033[%dC", column);
    printf("       //  \\    \n\033[%dC", column);
    printf("      //  ");
    printf("%d", top);
    printf(" \\   \n\033[%dC", column);
    printf("     //\\    /   \n\033[%dC", column);
    printf("    //  \\  /    \n\033[%dC", column);
    printf("   //    \\/     \n\033[%dC", column);
    printf("   \\  ");
    printf("%d", bottom);
    printf("  /       \n\033[%dC", column);
    printf("    \\   /        \n\033[%dC", column);
    printf("     \\ /         \n\033[%dC", column);
    printf("\033[10A"); // Sposta il cursore alla riga di partenza della stampa (10 caratteri piu' in alto));
    if (isSelected) {
        colorzz(0);
    }
}
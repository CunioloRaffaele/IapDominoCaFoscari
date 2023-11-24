#include <stdio.h>

void spawn_tile (int top, int bottom, int column) {
    /*
    char asciiArtString1[] =    "\n\033[%dC" 
                                "        //\\     \n\033[%dC" 
                                "       //  \\    \n\033[%dC" 
                                "      //  ";
    char asciiArtString2[] =    " \\   \n\033[%dC" 
                                "     //\\    /   \n\033[%dC" 
                                "    //  \\  /    \n\033[%dC" 
                                "   //    \\/     \n\033[%dC" 
                                "   \\  ";
    char asciiArtString3[] =    "  /       \n\033[%dC" 
                                "    \\   /        \n\033[%dC" 
                                "     \\ /         \n\033[%dC";

    printf("%s%d%s%d%s", asciiArtString1, top, asciiArtString2, bottom, asciiArtString3);
    */

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
}
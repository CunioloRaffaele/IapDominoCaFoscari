#include <stdio.h>

#include "../functions.h"

void introMessage(void)
{
    /*char asciiArtString[] =
        "             88                                88                          \n"
        "             88                                88                          \n"
        "             88                                                            \n"
        "     ,adPPYb,88  ,adPPYba,  88,dPYba,,adPYba,  88 8b,dPPYba,   ,adPPYba,   \n"
        "    a8      Y88 a8       8a 88P     88      8a 88 88P      8a a8       8a  \n"
        "    8b       88 8b       d8 88      88      88 88 88       88 8b       d8  \n"
        "     8a,   ,d88   8a,   ,a8 88      88      88 88 88       88 8a,     ,a8   \n"
        "        8bbdPY8    YbbdP88  88      88      88 88 88       88    PYbbdP    \n";*/
    colorzz(3);
    printCentered("      -------------------------------------------------------------      ");
    printCentered("      -------------- Benvenuto nel programma domino ---------------      ");
    printCentered("      -------------------------------------------------------------      ");
    printCentered("      ----------------------     Credits:     ---------------------      ");
    printCentered("      -----------------   901146 Barison Alberto   ----------------      ");
    printCentered("      ----------------   903407 Cuniolo Raffaele   ----------------      ");
    printCentered("      ----------------   902406 Veggis Francesco   ----------------      ");
    printCentered("      -------------------------------------------------------------      ");
    printCentered("      ------------ Universita\' Ca' Foscari  2023-2024 -------------      ");
    printCentered("      -------------------------------------------------------------      ");
    printCentered("             github.com/CunioloRaffaele/IapDominoCaFoscari.git           ");
    printCentered("       -------------------------------------------------------------      \n");
    printf("\n");
    //printf("%s", asciiArtString);
    printCentered("          88                                88                          ");
    printCentered("          88                                88                          ");
    printCentered("          88                                                            ");
    printCentered("  ,adPPYb,88  ,adPPYba,  88,dPYba,,adPYba,  88 8b,dPPYba,   ,adPPYba,   ");
    printCentered(" a8      Y88 a8       8a 88P     88      8a 88 88P      8a a8       8a  ");
    printCentered(" 8b       88 8b       d8 88      88      88 88 88       88 8b       d8  ");
    printCentered("   8a,   ,d88   8a,   ,a8 88      88      88 88 88       88 8a,     ,a8   ");
    printCentered("     8bbdPY8    YbbdP88  88      88      88 88 88       88    PYbbdP    ");
    printf("\n");
    printCentered("      -------------------------------------------------------------      ");
    printCentered("      --------------   Premi ENTER per cominciare   ---------------      ");
    printCentered("      --------------------------- v1 ------------------------------      ");
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)  // Windows
    printCentered("      Si suggerisce di non usare questo programma su cmd di Windows      ");
    printCentered("                    ma di eseguirlo con PowerShell.                      ");
#endif
    printf("\n\n");
    colorzz(0);
}

void exitMessage(void) {
    printf("\n\n\n\n");
    colorzz(3);
    printCentered("          88                                88                          ");
    printCentered("          88                                88                          ");
    printCentered("          88                                                            ");
    printCentered("  ,adPPYb,88  ,adPPYba,  88,dPYba,,adPYba,  88 8b,dPPYba,   ,adPPYba,   ");
    printCentered(" a8      Y88 a8       8a 88P     88      8a 88 88P      8a a8       8a  ");
    printCentered(" 8b       88 8b       d8 88      88      88 88 88       88 8b       d8  ");
    printCentered("   8a,   ,d88   8a,   ,a8 88      88      88 88 88       88 8a,     ,a8   ");
    printCentered("     8bbdPY8    YbbdP88  88      88      88 88 88       88    PYbbdP    ");
    printf("\n");
    printCentered("      -------------------------------------------------------------      ");
    printCentered("      ------------ Universita\' Ca' Foscari  2023-2024 -------------      ");
    printCentered("      -------------------------------------------------------------      ");
    printCentered("             github.com/CunioloRaffaele/IapDominoCaFoscari.git           ");
    printCentered("       -------------------------------------------------------------      \n");
    colorzz(2);
    printCentered("Grazie per aver usato Domino\n\n");
}

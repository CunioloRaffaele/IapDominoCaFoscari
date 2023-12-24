#include <stdio.h>

#include "../functions.h"

void introMessage(void)
{
    char asciiArtString[] =
        "           88                                88                          \n"
        "           88                                88                          \n"
        "           88                                                            \n"
        "   ,adPPYb,88  ,adPPYba,  88,dPYba,,adPYba,  88 8b,dPPYba,   ,adPPYba,   \n"
        "  a8      Y88 a8       8a 88P     88      8a 88 88P      8a a8       8a  \n"
        "  8b       88 8b       d8 88      88      88 88 88       88 8b       d8  \n"
        "   8a,   ,d88   8a,   ,a8 88      88      88 88 88       88 8a,     ,a8   \n"
        "      8bbdPY8    YbbdP88  88      88      88 88 88       88    PYbbdP    \n";
    colorzz(3);
    printf("      -------------------------------------------------------------      \n");
    printf("      -------------- Benvenuto nel programma domino ---------------      \n");
    printf("      -------------------------------------------------------------      \n");
    printf("      ----------------------     Credits:     ---------------------      \n");
    printf("      -----------------   901146 Barison Alberto   ----------------      \n");
    printf("      ----------------   903407 Cuniolo Raffaele   ----------------      \n");
    printf("      ----------------   902406 Veggis Francesco   ----------------      \n");
    printf("      -------------------------------------------------------------      \n");
    printf("      ------------ Universita\' Ca' Foscari  2023-2024 -------------      \n");
    printf("      -------------------------------------------------------------      \n");
    printf("             github.com/CunioloRaffaele/IapDominoCaFoscari.git           \n");
    printf("      -------------------------------------------------------------      \n\n");
    printf("%s", asciiArtString);
    printf("\n");
    printf("      -------------------------------------------------------------      \n");
    printf("      --------------   Premi ENTER per cominciare   ---------------      \n");
    printf("      -------------------------------------------------------------      \n");
    printf("      Si suggerisce di non usare questo programma su cmd di Windows      \n");
    printf("                         esegui con PowerShell                           \n");
    colorzz(0);
}

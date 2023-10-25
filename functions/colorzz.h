#include <stdio.h>

void colorzz (int color) {

    #ifdef _WIN32
        printf("");
    #else
        switch (color)
        {
        case 0:
            printf("\033[0m\n");
            break;
        case 1:
            printf("\033[31m\n");
            break;
        case 2:
            printf("\033[32m\n");
            break;
        case 3:
            printf("\033[34m\n");
            break;
        case 4:
            printf("\033[37m\n");
            break;
        default:
            break;
        }
    #endif
}
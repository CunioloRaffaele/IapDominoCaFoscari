#include <stdio.h>

void spawn_tile (int top, int bottom) {
    char asciiArtString1[] = "\n" "        //\\     \n" "       //  \\    \n" "      //  ";
    char asciiArtString2[] = " \\   \n" "     //\\    /   \n" "    //  \\  /    \n" "   //    \\/     \n" "   \\  ";
    char asciiArtString3[] = "  /       \n" "    \\   /        \n" "     \\ /         \n";
    printf("%s%d%s%d%s", asciiArtString1, top, asciiArtString2, bottom, asciiArtString3);
}
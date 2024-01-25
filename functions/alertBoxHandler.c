#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <windows.h> // Windows
#endif
#include "../functions.h"

void showAlert (char text[]) {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)  // Windows    
        int test = MessageBoxA(NULL, text, "Domino", 0);
    #elif __APPLE__                                                                 // MacOs
        char str1[] = "osascript -e 'tell app \"Terminal\" to display dialog \"";
        char str2[] = "\"'";
        char result[strlen(str1) + strlen(str2) + strlen(text)];
        strcpy(result, str1);
        strcat(result, text);
        strcat(result, str2);
        system(result);
    #elif  __linux__ || __unix__                                                    // Linux
        // https://stackoverflow.com/questions/41225711/wsl-run-linux-from-windows-without-spawning-a-cmd-window
        // https://www.commandlinux.com/man-page/man1/xmessage.1.html
        char str1[] = "DISPLAY=:0 xmessage '";
        char str2[] = "\"'";
        char result[strlen(str1) + strlen(str2) + strlen(text)];
        strcpy(result, str1);
        strcat(result, text);
        strcat(result, str2);
        system(result);

    #endif
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../functions.h"

void show_alert (char text[]) {
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
        // TODO
    #endif
}

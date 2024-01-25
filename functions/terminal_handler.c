#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)  // Windows
    #include <windows.h>
    #include <conio.h>
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
#elif __APPLE__ || __linux__ || __unix__                                        // MacOs + Linux
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <termios.h>
#endif

#include "../functions.h"

int getch(void) {

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)  // Windows
        return _getch();
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    #elif __APPLE__ || __linux__ || __unix__                                        // MacOs + Linux
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        return ch;
    #endif
}

void colorzz(int color) {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // Windows
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        /* Save current attributes */
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        switch (color) {
        case 0: // Restore to original color attribute
            // SetConsoleTextAttribute(hConsole, saved_attributes);
            // Commentato per bug nella colorazione ma non rimosso per evitare problemi
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        case 1:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            break;
        case 2:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            break;
        case 3:
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            break;
        case 4:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        default:
            break;
        }
    #elif  __APPLE__ || __linux__ || __unix__ // MacOs + Linux
        switch (color) {
        case 0:
            printf("\033[0m");
            break;
        case 1:
            printf("\033[31m");
            break;
        case 2:
            printf("\033[32m");
            break;
        case 3:
            printf("\033[34m");
            break;
        case 4:
            printf("\033[37m");
            break;
        default:
            break;
        }
    #endif
}

void clearConsole(void) {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)  // Windows
        system("cls");
    #elif __APPLE__ || __linux__ || __unix__                                        // MacOs + Linux
        printf("\033[H\033[2J\033[3J"); // This tells the terminal to move the cursor to the top left corner (\e[H), clear the screen (\e[2J), and clear the scrollback buffer (\e[3J).
        // printf("\e[H\e[2J\e[3J");    // Using \033 instead of \e for ISO-standards compliance
    #endif
}

int screenRow(void) {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // Windows
        ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        if (ret) {
            return csbi.dwSize.Y;
        }
    #elif __APPLE__ || __linux__ || __unix__ // MacOs + Linux
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_row;
    #endif
        return 0;
}

int screenCol(void) {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // Windows
        ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        if (ret) {
            return csbi.dwSize.X;
        }
    #elif __APPLE__ || __linux__ || __unix__ // MacOs + Linux
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    #endif
        return 0;
}

void spawnScreenWithTitle(char title[], bool animation) {
    int col = screenCol();
    int row = screenRow();
    int title_len = strlen(title);
    clearConsole();
    colorzz(3);
    if (animation) {
        for (int t = 0; t < 5; t++) {
            for (int c = 0; c < row; c++) {
                for (int d = 0; d < col; d++) {
                    switch (t) {
                    case 0:
                        printf("!");
                        break;
                    case 1:
                        printf("-");
                        break;
                    case 2:
                        printf(":");
                        break;
                    case 3:
                        printf("?");
                        break;
                    case 4:
                        printf("=");
                        break;
                    default:
                        break;
                    }
                }
                printf("\n");
            }
            usleep(80000);
            clearConsole();
        }
    }
    for (int c = 0; c < col; c++) {
        printf("-");
    }
    printf("\n");
    for (int c = 0; c < ((col / 2) - (title_len / 2) - 1); c++) {
        printf("-");
    }
    printf(" %s ", title);
    for (int c = 0; c < ((col / 2) - (title_len / 2) - 1); c++) {
        printf("-");
    }
    printf("\n");
    for (int c = 0; c < col; c++) {
        printf("-");
    }
    printf("\n");
    colorzz(0);
}

void printCentered (char text[]) {
    int col = screenCol();
    int difference = col - strlen(text);
    for (int counter = 0; counter < difference / 2; counter ++) {
        printf(" ");
    }
    printf("%s\n", text);
}

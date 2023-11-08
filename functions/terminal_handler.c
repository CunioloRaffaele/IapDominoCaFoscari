#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // Windows
#include <windows.h>

CONSOLE_SCREEN_BUFFER_INFO csbi;
int ret;

#elif __APPLE__ || __linux__ || __unix__ // MacOs + Linux
#include <sys/ioctl.h>
#endif

void colorzz(int color)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // Windows
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    switch (color)
    {
    case 0: // Restore to original color attribute
        SetConsoleTextAttribute(hConsole, saved_attributes);
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
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
        break;
    default:
        break;
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

#elif __APPLE__ || __linux__ || __unix__ // MacOs + Linux
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

void clear_console()
{
    printf("\e[H\e[2J\e[3J"); // This tells the terminal to move the cursor to the top left corner (\e[H), clear the screen (\e[2J), and clear the scrollback buffer (\e[3J).
}

int screen_row()
{
    int size = 0;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // Windows
    ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    if (ret)
    {
        return csbi.dwSize.Y;
    }

#elif __APPLE__ || __linux__ || __unix__ // MacOs + Linux
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    size = w.ws_row;
#endif
    return size;
}

int screen_col()
{
    int size = 0;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // Windows
    ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    if (ret)
    {
        return csbi.dwSize.X;
    }

#elif __APPLE__ || __linux__ || __unix__ // MacOs + Linux
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    size = w.ws_col;
#endif
    return size;
}

void spawn_screen_with_title(char title[])
{
    int col = screen_col();
    int row = screen_row();
    int title_len = strlen(title);
    colorzz(3);
    for (int t = 0; t < 5; t++)
    {
        for (int c = 0; c < row; c++)
        {
            for (int d = 0; d < col; d++)
            {
                switch (t)
                {
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
        clear_console();
    }
    for (int c = 0; c < col; c++)
    {
        printf("-");
    }
    printf("\n");
    for (int c = 0; c < ((col / 2) - (title_len / 2) - 1); c++)
    {
        printf("-");
    }
    printf(" %s ", title);
    for (int c = 0; c < ((col / 2) - (title_len / 2) - 2); c++)
    {
        printf("-");
    }
    printf("\n");
    for (int c = 0; c < col; c++)
    {
        printf("-");
    }
    printf("\n");
    colorzz(0);
}
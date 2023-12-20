#include <stdio.h>
#include <stdbool.h>
#include "../fragments.h"

extern int **gameSet;

void generateVarieblas(int **playerDeck, int *playerDeckDimension, int ***played, int *directioncard)
{
    **played = alloc_player_deck_memory(*playerDeckDimension);
    *directioncard = (int *)malloc(sizeof(int) * *playerDeckDimension);
    **playerDeck = alloc_player_deck_memory(*playerDeckDimension);
    generate_player_deck(gameSet, &playerDeck, *playerDeckDimension);
}

void fragment5()
{
    int **playerDeck;
    int **played;
    int *directioncard;
    int playerDeckDimension = 0;
    int choose;
    scanf("%d", &playerDeckDimension);
    generateVarieblas(playerDeck, playerDeckDimension, played, directioncard);
jump:
    printf("Fai la tua mossa: \n");
    printf("1 | Visualizza tessere:  \n",
           "2 | Posiziona tessera:  \n");

    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        for (size_t i = 0; i < playerDeckDimension; i++)
        {
            printf("[%d", playerDeck[i][0], "|%d", playerDeck[i][1], "]\n");
        }

        break;
    case 2:
        if (played[0][0] == 0)
        {
            printf("Nessuna carta ancora giocata: \n");
            goto jump;
        }
        else
        {
            printf("Gia giocate: \n");
            for (size_t i = 0; i < playerDeckDimension; i++)
            {
                if (played[i][0] != 0)
                {
                    if (directioncard[i] == 0)
                    {
                    }
                    else
                    {
                    }

                    printf("[%d", played[i][0], "|%d", played[i][1], "]\n");
                }
            }
            printf("1 | Posiziona tessera verticale:  \n",
                   "2 | Posiziona tessera orizzontale:  \n");
            scanf("%d", &choose);
        }

        break;

    default:
        break;
    }
}

void addCard(int indexCard, int **playerdeck, int **played, int direction, int *cardplayed, int *playerDeckDimension)
{

    if (played[0][0] == playerdeck[indexCard][0])
    {
        for (size_t i = *cardplayed; i > 0; i--)
        {
            played[i + 1][0] = played[i][0];
            played[i + 1][1] = played[i][1];
        }
        played[0][0] = playerdeck[indexCard][1];
        played[0][1] = playerdeck[indexCard][0];
        for (size_t i = indexCard; i < *playerDeckDimension; i++)
        {
            playerdeck[i][0] = playerdeck[i + 1][0];
            playerdeck[i][1] = playerdeck[i + 1][1];
        }
        *playerDeckDimension--;
        *cardplayed++;
    }
    else if (played[0][0] == playerdeck[indexCard][1])
    {
        for (size_t i = cardplayed; i > 0; i--)
        {
            played[i + 1][0] = played[i][0];
            played[i + 1][1] = played[i][1];
        }
        played[0][0] = playerdeck[indexCard][0];
        played[0][1] = playerdeck[indexCard][1];
        for (size_t i = indexCard; i < *playerDeckDimension; i++)
        {
            playerdeck[i][0] = playerdeck[i + 1][0];
            playerdeck[i][1] = playerdeck[i + 1][1];
        }
        *playerDeckDimension--;
        *cardplayed++;
    }
    else if (played[*cardplayed][1] == playerdeck[indexCard][0])
    {

        played[0][0] = playerdeck[indexCard][0];
        played[0][1] = playerdeck[indexCard][1];
        for (size_t i = indexCard; i < *playerDeckDimension; i++)
        {
            playerdeck[i][0] = playerdeck[i + 1][0];
            playerdeck[i][1] = playerdeck[i + 1][1];
        }
        *playerDeckDimension--;
        *cardplayed++;
    }
    else if (played[*cardplayed][0] == playerdeck[indexCard][1])
    {
        played[0][0] = playerdeck[indexCard][1];
        played[0][1] = playerdeck[indexCard][0];
        for (size_t i = indexCard; i < *playerDeckDimension; i++)
        {
            playerdeck[i][0] = playerdeck[i + 1][0];
            playerdeck[i][1] = playerdeck[i + 1][1];
        }
        *playerDeckDimension--;
        *cardplayed++;
    }
}

void verticalMove()
{
}

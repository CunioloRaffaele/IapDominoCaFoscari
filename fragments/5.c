#include <stdio.h>
#include <stdbool.h>
#include "../fragments.h"

extern int **gameSet;

void generateVarieblas(int **playerDeck, int *playerDeckDimension, int ***orizzontal, int **dimension, int **vertical)
{
    **orizzontal = alloc_player_deck_memory(*playerDeckDimension);
    **dimension = (int *)malloc(sizeof(int) * *playerDeckDimension);
    **vertical = (int *)malloc(sizeof(int) * *playerDeckDimension);
    **playerDeck = alloc_player_deck_memory(*playerDeckDimension);
    generate_player_deck(gameSet, &playerDeck, *playerDeckDimension);
}

void fragment5()
{
    int **playerDeck;
    int **orizzontal;
    int *directioncard;
    int **vertical;
    int **dimension;
    int playerDeckDimension = 0;
    int choose;
    scanf("%d", &playerDeckDimension);
    generateVarieblas(playerDeck, playerDeckDimension, orizzontal,dimension,vertical);
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
        if (orizzontal[0][0] == 0)
        {
            printf("Nessuna carta ancora giocata: \n");
            goto jump;
        }
        else
        {
            printf("Gia giocate: \n");
            for (size_t i = 0; i < playerDeckDimension; i++)
            {
                if (orizzontal[i][0] != 0)
                {
                    if (directioncard[i] == 0)
                    {
                    }
                    else
                    {
                    }

                    printf("[%d", orizzontal[i][0], "|%d", orizzontal[i][1], "]\n");
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

void orizzontalCard(int indexCard, int **playerdeck, int **orizzontal, int *cardplayed, int *playerDeckDimension)
{

    if (orizzontal[0][0] == playerdeck[indexCard][0])
    {
        for (size_t i = *cardplayed; i > 0; i--)
        {
            orizzontal[i + 1][0] = orizzontal[i][0];
            orizzontal[i + 1][1] = orizzontal[i][1];
        }
        orizzontal[0][0] = playerdeck[indexCard][1];
        orizzontal[0][1] = playerdeck[indexCard][0];
        for (size_t i = indexCard; i < *playerDeckDimension; i++)
        {
            playerdeck[i][0] = playerdeck[i + 1][0];
            playerdeck[i][1] = playerdeck[i + 1][1];
        }
        *playerDeckDimension--;
        *cardplayed++;
    }
    else if (orizzontal[0][0] == playerdeck[indexCard][1])
    {
        for (size_t i = cardplayed; i > 0; i--)
        {
            orizzontal[i + 1][0] = orizzontal[i][0];
            orizzontal[i + 1][1] = orizzontal[i][1];
        }
        orizzontal[0][0] = playerdeck[indexCard][0];
        orizzontal[0][1] = playerdeck[indexCard][1];
        for (size_t i = indexCard; i < *playerDeckDimension; i++)
        {
            playerdeck[i][0] = playerdeck[i + 1][0];
            playerdeck[i][1] = playerdeck[i + 1][1];
        }
        *playerDeckDimension--;
        *cardplayed++;
    }
    else if (orizzontal[*cardplayed][1] == playerdeck[indexCard][0])
    {

        orizzontal[0][0] = playerdeck[indexCard][0];
        orizzontal[0][1] = playerdeck[indexCard][1];
        for (size_t i = indexCard; i < *playerDeckDimension; i++)
        {
            playerdeck[i][0] = playerdeck[i + 1][0];
            playerdeck[i][1] = playerdeck[i + 1][1];
        }
        *playerDeckDimension--;
        *cardplayed++;
    }
    else if (orizzontal[*cardplayed][0] == playerdeck[indexCard][1])
    {
        orizzontal[0][0] = playerdeck[indexCard][1];
        orizzontal[0][1] = playerdeck[indexCard][0];
        for (size_t i = indexCard; i < *playerDeckDimension; i++)
        {
            playerdeck[i][0] = playerdeck[i + 1][0];
            playerdeck[i][1] = playerdeck[i + 1][1];
        }
        *playerDeckDimension--;
        *cardplayed++;
    }
}

void verticalCard(int indexCard, int **playerdeck, int **orizzontal, int *cardplayed, int *playerDeckDimension)
{
    if (orizzontal[0][0] == playerdeck[indexCard][0])
    {
        
    }
    else
    {
        /* code */
    }
    
}

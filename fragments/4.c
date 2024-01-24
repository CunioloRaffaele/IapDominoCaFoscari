#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../fragments.h"

int **newPD;
int* AiResult;

struct gameNodeLin {
    int index;
    int top;                    // Semplifichiamo includendo nella struct anche le due facce della tessera per non rendere
    int bottom;                 // necessario un parser (come è stato fatto nella funzione ai). Le modifiche alla lista vengono
    gameNodeLinList *next;      // fatte direttamente all'aggiunta di una nuova tessera.
};

void free_list_it(gameNodeLinList *l) {
    while (l) {
        gameNodeLinList *next = l->next;
        free(l);
        l = next;
    }
}

bool verifyCompatibility4 (int prec, int succ) {
    if (prec == succ) {
        return true;
    } else if ( succ == 11 || succ == 12 || succ == 0 || prec == 0 || prec == 21 || prec == 11) {
        return true;
    } else {
        return false;
    }
}

void addTileToList4 (int ** playerDeck, int selectedTileIndex, bool isFlipped, gameNodeLinList *testa) {
    // Variabile temporanea per scorrere la lista "testa"
    // (in teoria non servirebbe visto che stiamo usando una copia del puntatore originale ma sono le 2 di notte e quindi rimarrà così...)
    gameNodeLinList * copyOfTesta = testa;
    // Testa esistente, quindi scorro la lista e aggiungo la nuova tessera alla fine.
    while (copyOfTesta -> next) {
        // Verifico che la tessera selezionata non sia già stata messa nella lista
        if (copyOfTesta -> index == selectedTileIndex || copyOfTesta -> index == -selectedTileIndex){
            showAlert("Tessera già utilizzata. Non è possibile usare la stessa tessera più di una volta.");
            return;
        }
        copyOfTesta = copyOfTesta -> next;
    }
    // Verifico che la tessera selezionata non sia già stata messa nell'ultimo nodo della lista
    if (copyOfTesta -> index == selectedTileIndex || copyOfTesta -> index == -selectedTileIndex){
        showAlert("Tessera già utilizzata. Non è possibile usare la stessa tessera più di una volta.");
        return;
    }
    // Verifico che la tessera selezionata sia compatibile con quella precedente
    if (verifyCompatibility4(copyOfTesta -> bottom, playerDeck[selectedTileIndex][isFlipped])){
        gameNodeLinList * newNode = (gameNodeLinList*)malloc(sizeof (gameNodeLinList));
        if (playerDeck[selectedTileIndex][0] == 0 && playerDeck[selectedTileIndex][1] == 0) {
            // Caso tessera [0 0]
            newNode -> index = selectedTileIndex;
            newNode -> top = 0;
            newNode -> bottom = 0;
        } else if (playerDeck[selectedTileIndex][0] == 11 && playerDeck[selectedTileIndex][1] == 11) {
            // Caso tessera [11 11]
            // Cambiamo valori tessere precedenti top ++, bottom ++ if (6) 1
            gameNodeLinList * copyOfTestaParser = testa;
            int latestBottom = 0;
            while (copyOfTestaParser) {
                if (copyOfTestaParser -> top == 6) {
                    copyOfTestaParser -> top = 1;
                } else {
                    copyOfTestaParser -> top =  copyOfTestaParser -> top + 1;
                }
                if (copyOfTestaParser -> bottom == 6) {
                    copyOfTestaParser -> bottom = 1;
                } else {
                    copyOfTestaParser -> bottom = copyOfTestaParser -> bottom + 1;
                }
                latestBottom = copyOfTestaParser -> bottom;
                copyOfTestaParser = copyOfTestaParser -> next;
            }
            newNode -> top = latestBottom;
            newNode -> bottom = latestBottom;
            newNode -> index = selectedTileIndex;
        } else if (playerDeck[selectedTileIndex][0] == 12 && playerDeck[selectedTileIndex][1] == 21) {
            // Caso tessera [12 21]
            // invertiamo valori tessera precedente.
            gameNodeLinList * copyOfTestaParser = testa;
            while (copyOfTestaParser -> next) {
                copyOfTestaParser = copyOfTestaParser -> next ;
            }
            newNode -> index = selectedTileIndex;
            newNode -> top = copyOfTestaParser -> bottom;
            newNode -> bottom = copyOfTestaParser -> top;
        } else {
            newNode -> index = selectedTileIndex;
            if (!isFlipped) {
                newNode -> top = playerDeck[selectedTileIndex][0];
                newNode -> bottom = playerDeck[selectedTileIndex][1];
            }else {
                newNode -> top = playerDeck[selectedTileIndex][1];
                newNode -> bottom = playerDeck[selectedTileIndex][0];
            }
        }
        copyOfTesta -> next = newNode;
        return;
    } else {
        showAlert("Mossa non permessa.");
        return;
    }
}

int scoreCalculator (gameNodeLinList * testa) {
    int score = 0;
    while (testa) {
        score = score + testa -> top;
        score = score + testa -> bottom;
        testa = testa -> next;
    }
    return score;
}

void fragment4(int **playerDeck, int startingTileIndex, int selectedTileIndex, bool animation, int playerDeckDimension, gameNodeLinList *testa) {
    spawnScreenWithTitle("DOMINO LINEARE", animation);
    /*if (screenRow() <= 50) {
        showAlert("La dimensione del terminale non è adeguata per contenere tutti gli elementi di gioco (almeno 90 righe x 50 colonne). Ingrandisci il terminale e ritenta");
        menuUi();
    }*/

    colorzz(2);
    printf("| A      -  Scorri le tiles a sinistra (una alla volta)\n");
    printf("| D      -  Scorri le tiles a destra (una alla volta)\n");
    printf("| W      -  Piazza la tessera colorata di rosso\n");
    printf("| S      -  Piazza la tessera colorata di rosso e girala\n");
    printf("| SPACE  -  Chiedi aiuto all'Ai\n");
    printf("| Altro  -  Torna al menu precedente\n\n\n");
    printCentered("Tiles a tua disposizione:");
    colorzz(0);

    // Controllo di quante tiles stanno orizzontalmente nel terminale.
    // Una tile occupa 18 caratteri (18 colonne)
    int tilesPerScreen = screenCol() / 18;
    int columnToSpawn = 0;
    for (int counter = startingTileIndex; counter < tilesPerScreen + startingTileIndex; counter ++) {
        if (counter < playerDeckDimension + startingTileIndex){
            gameNodeLinList * copyOfTesta = testa;
            bool hasBeenUsed = false;
            while (copyOfTesta) {
                if (copyOfTesta -> index == counter || copyOfTesta -> index == -counter) {
                    hasBeenUsed = true;
                }
                copyOfTesta = copyOfTesta -> next;
            }
            if (hasBeenUsed) {
                spawnTile(playerDeck[counter][0], playerDeck[counter][1], 18*columnToSpawn, 3);
            } else {
                spawnTile(playerDeck[counter][0], playerDeck[counter][1], 18*columnToSpawn, selectedTileIndex == counter);
            }
            columnToSpawn++;
        } else {
            break;
        }
    }
    printf("\033[12B\n");
    /*printf("DEBUG:\nTiles selezionata = %d \nTiles = [%d | %d]\n", selectedTileIndex, playerDeck[selectedTileIndex][0], playerDeck[selectedTileIndex][1]);
    colorzz(2);
    printf("| Q      -  Scorri le tiles a sinistra (una alla volta)\n");
    printf("| E      -  Scorri le tiles a destra (una alla volta)\n\n\n");*/

    if (!testa) {
        printCentered("Tavolo vuoto... Inizia a piazzare le tessere selezionando quella desiderata.");
    } else {
        printCentered("Tiles da te ordinate:");
    }
    colorzz(0);

    // Variabile temporanea per scorrere la lista "testa"
    /*gameNodeLinList * copyOfTesta = testa;
    if (testa) {
        int columnToSpawnPlayerTable = 0;
        while (copyOfTesta) {
            if (columnToSpawnPlayerTable > tilesPerScreen) {
                break;
            }
            if (copyOfTesta -> index >= 0) {
                spawnTile(playerDeck[copyOfTesta -> index][0], playerDeck[copyOfTesta -> index][1], 18*columnToSpawnPlayerTable, false);
                columnToSpawnPlayerTable++;
            }
            copyOfTesta = copyOfTesta-> next;
        }
    }*/
    gameNodeLinList * copyOfTestaDebug = testa;
    if (copyOfTestaDebug) {
        while (copyOfTestaDebug) {
            printf("[%d %d]  ", copyOfTestaDebug -> top, copyOfTestaDebug -> bottom);
            copyOfTestaDebug = copyOfTestaDebug -> next;
        }
    }

    printf("\n\nPunteggio: %d", scoreCalculator(testa));


    // LOGICA INPUT
    int input = getch();
    switch (input)
    {
        case ASCII_A:
            if (startingTileIndex ==  0) {
                if ((selectedTileIndex - 1) >= 0) {
                    selectedTileIndex --;
                }
                fragment4(playerDeck, 0, selectedTileIndex, false, playerDeckDimension, testa);
            } else {
                fragment4(playerDeck, startingTileIndex - 1, selectedTileIndex - 1, false, playerDeckDimension, testa);
            }
            break;
        case ASCII_D:
            if ((startingTileIndex + tilesPerScreen) >= playerDeckDimension) {
                if ((selectedTileIndex + 1) < playerDeckDimension) {
                    selectedTileIndex ++;
                }
                if ((playerDeckDimension - tilesPerScreen) <= 0) {
                    fragment4(playerDeck, startingTileIndex, selectedTileIndex, false, playerDeckDimension, testa);
                } else {
                    fragment4(playerDeck, playerDeckDimension - tilesPerScreen, selectedTileIndex, false, playerDeckDimension, testa);
                }
            } else {
                fragment4(playerDeck, startingTileIndex + 1, startingTileIndex + 1, false, playerDeckDimension, testa);
            }
            break;
        case ASCII_W:
            // Se volessimo aggiungere in testa dovremmo passare il puntatore del puntatore, dunque lo facciamo estermente da addTileToList4
            if (!testa) {
                // Tavolo vuoto. Bisogna creare una testa e popolarla con la tessera scelta.
                if (playerDeck[selectedTileIndex][0] == 11 || playerDeck[selectedTileIndex][0] == 12 || playerDeck[selectedTileIndex][0] == 0) {
                    showAlert("Mossa non permessa.");
                } else {
                    testa = (gameNodeLinList *) malloc(sizeof(gameNodeLinList));
                    testa->index = selectedTileIndex;
                    testa->top = playerDeck[selectedTileIndex][0];
                    testa->bottom = playerDeck[selectedTileIndex][1];
                    fragment4(playerDeck, startingTileIndex, startingTileIndex, false, playerDeckDimension, testa);
                }
            } else {
                addTileToList4(playerDeck, selectedTileIndex, false, testa);
                fragment4(playerDeck, startingTileIndex, startingTileIndex, false, playerDeckDimension, testa);
            }
            fragment4(playerDeck, startingTileIndex, startingTileIndex, false, playerDeckDimension, testa);
            break;
        case ASCII_S:
            if (!testa) {
                // Tavolo vuoto. Bisogna creare una testa e popolarla con la tessera scelta invertita.
                if (playerDeck[selectedTileIndex][0] == 11 || playerDeck[selectedTileIndex][0] == 12 || playerDeck[selectedTileIndex][0] == 0) {
                    showAlert("Mossa non permessa.");
                } else {
                    testa = (gameNodeLinList*)malloc(sizeof (gameNodeLinList));
                    testa -> index = -selectedTileIndex;
                    testa -> top = playerDeck[selectedTileIndex][1];
                    testa -> bottom = playerDeck[selectedTileIndex][0];
                    fragment4(playerDeck, startingTileIndex, startingTileIndex, false, playerDeckDimension, testa);
                }
            } else {
                // Testa esistente, quindi scorro la lista e aggiungo la nuova tessera invertita alla fine.
                addTileToList4(playerDeck, selectedTileIndex, true, testa);
                fragment4(playerDeck, startingTileIndex, startingTileIndex, false, playerDeckDimension, testa);
            }
            fragment4(playerDeck, startingTileIndex, startingTileIndex, false, playerDeckDimension, testa);
            break;
        case ASCII_Space:
            // Creazione nuovo deck che possa essere parsato da ai (uguale a playerdeck ma con 666 al posto delle tessere già usate)
            newPD = allocPlayerDeckMemory(playerDeckDimension);
            for (int c = 0; c < playerDeckDimension; c++) {
                gameNodeLinList * copyOfTesta = testa;
                bool hasBeenUsed = false;
                while (copyOfTesta) {
                    if (copyOfTesta -> index == c || copyOfTesta -> index == -c) {
                        hasBeenUsed = true;
                        break;
                    }
                    copyOfTesta = copyOfTesta -> next;
                }
                if (hasBeenUsed){
                    newPD[c][0] = 666;
                    newPD[c][1] = 666;
                } else {
                    newPD[c][0] = playerDeck [c][0];
                    newPD[c][1] = playerDeck [c][1];
                }
            }
            // ripristinare l'ultima tessera selezionata, punto di partenza per l'AI
            gameNodeLinList * copyOfTesta = testa;
            while (copyOfTesta -> next) {
                copyOfTesta = copyOfTesta -> next;
            }
            newPD[copyOfTesta->index][0] = copyOfTesta -> top;
            newPD[copyOfTesta->index][1] = copyOfTesta -> bottom;

            int processAIDimension; // Questa variabile viene passarta come puntatore e conterrà la dimensione dell'array di output della funzione AiResult()
            AiResult = processAI(newPD, playerDeckDimension, copyOfTesta -> index, &processAIDimension);
            printf("%d", processAIDimension);
            if (processAIDimension >= 1) {
                // index della seconda mossa
                int indexOfNextStep = AiResult[1];
                if (indexOfNextStep >= 0){
                    addTileToList4(playerDeck, indexOfNextStep, false, testa);
                }else {
                    addTileToList4(playerDeck, -indexOfNextStep, true, testa);
                }
            } else {
                showAlert("L'ai non può aiutarti in questo caso :(");
            }
            fragment4(playerDeck, startingTileIndex, startingTileIndex, false, playerDeckDimension, testa);
            break;
        default:
            menuUi();
            // TODO free di tutte le variabili temporanee
            break;
    }
}

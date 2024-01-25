#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../fragments.h"

struct gameNode2DLin {
    int column;
    int top;
    int bottom;
    bool whatFaceToMatch;
    gameNode2DLinList *next;
};

// Array contenente i puntatori di memoria alle liste di tessere già piazzate (ogni riga ha una lista di tessere)
gameNode2DLinList* rowPointers [5];

int maxOrizzontalSpan = 0;
int verticalSpan = 5;

gameNode2DLinList* generate2DNode(int column, int top, int bottom, bool isReversed, bool whatFaceToMatch, int indexToRemove, int **playerDeck) {
    playerDeck[indexToRemove][0] = 666;
    playerDeck[indexToRemove][1] = 666;
    gameNode2DLinList *newNode = malloc(sizeof(gameNode2DLinList));
    if(isReversed){
        newNode -> bottom = top;
        newNode -> top = bottom;
    }else{
        newNode -> top = top;
        newNode -> bottom = bottom;
    }
    newNode -> whatFaceToMatch = whatFaceToMatch;
    newNode -> column = column;
    newNode -> next = NULL;
    return newNode;
}

bool isSlotOccupied(int column, int row, int isVertical) { //Verifica che la posizione sia occupata
    gameNode2DLinList *rowPointerTemp = rowPointers[row];
    bool isOcc = false;
    while(rowPointerTemp){
        if(rowPointerTemp -> column == column){
            isOcc = true;
        }
        rowPointerTemp = rowPointerTemp -> next;
    }
    if(isOcc && isVertical && row + 1 < verticalSpan){
        rowPointerTemp = rowPointers[row + 1];
        while(rowPointerTemp){
            if(rowPointerTemp -> column == column){
                return true;
            }
            rowPointerTemp = rowPointerTemp -> next;
        }
    }
    return isOcc;
}

// Questa funzione modifica playerdeck e cambia le tessere già usate con 666.
void fragment5(int **playerDeck,int playerDeckDimension) {
    colorzz(0);
    clearConsole();

    // Stampa del deck generato al fragment 2
    for (int c = 0; c < playerDeckDimension; c ++) {
        if (playerDeck[c][0] != 666) {
            printf(" %d:[%d %d] ", c, playerDeck[c][0], playerDeck[c][1]);
        }
    }
    
    // Stampa degli indici superiori della tabella fino al maxOrizzontalSpan, che è il numero di righe che sono state popolate finora
    printf("\n\n");
    printf("    ");
    for (int counter = 0; counter <= maxOrizzontalSpan; counter ++) {
        printf("   %d     ", counter);
    }
    printf("\n");
    // Stampa riga per riga della tabella
    for (int row = 0; row < verticalSpan; row ++) {
        printf ("%d: ", row);
        gameNode2DLinList *rowPointerTemp = rowPointers[row];
        for (int column = 0; column <= verticalSpan; column ++) {
            if (rowPointerTemp && rowPointerTemp -> column == column) {
                if (rowPointerTemp -> top > 9) {
                    printf(" [%d %d] ", rowPointerTemp -> top, rowPointerTemp -> bottom);
                } else {
                    printf("  [%d %d]  ", rowPointerTemp -> top, rowPointerTemp -> bottom);
                }
                rowPointerTemp = rowPointerTemp -> next;
            } else {
                printf("         ");
            }
        }
        printf("\n\n");
        /*gameNode2DLinList *rowPointerTemp = rowPointers[row];
        // Scorrimento della lista (che contiene le tessere già piazzate riga per riga)
        while(rowPointerTemp){
            if (rowPointerTemp -> next){
                int differenceInSpace = (rowPointerTemp -> next -> column) - (rowPointerTemp -> column);
                for (int counter = 1; counter < differenceInSpace; counter ++) {
                    printf("         ");
                }
            }
            if (rowPointerTemp -> top > 9) {
                printf(" [%d %d] ", rowPointerTemp -> top, rowPointerTemp -> bottom);
            } else {
                printf("  [%d %d]  ", rowPointerTemp -> top, rowPointerTemp -> bottom);
            }
            rowPointerTemp = rowPointerTemp -> next;
        }
        printf("\n\n");*/
    }

    // Richiesta valori da utente
    int indexSelected;
    int isReversed;
    int isVertical = 0;
    int rowSelected;
    int columnSelected;
    printf("\n\nChe tessera vuoi piazzare? Inserisci l'index: ");
    scanf("%d", & indexSelected);
    if (playerDeck[indexSelected][0] == 666) {
        showAlert("Hai già usato questa tessera!");
        fragment5(playerDeck, playerDeckDimension);
    }
    printf("\n\nVuoi piazzare la tessera al contrario? (1 = si, 0 = no): ");
    scanf("%d", & isReversed);
    if (isReversed != 0 && isReversed != 1) {
        showAlert("Hai inserito un valore non valido!");
        fragment5(playerDeck, playerDeckDimension);
    }
    printf("\n\nVuoi piazzare la tessera in verticale? (1 = si, 0 = no): ");
    scanf("%d", & isVertical);
    if (isVertical != 0 && isVertical != 1) {
        showAlert("Hai inserito un valore non valido!");
        fragment5(playerDeck, playerDeckDimension);
    }
    printf("\n\nIn quale riga vuoi piazzare la tessera? (0-4): ");
    scanf("%d", & rowSelected);
    printf("\n\nIn quale colonna vuoi piazzare la tessera?: ");
    scanf("%d", & columnSelected);
    if (columnSelected > maxOrizzontalSpan + 1) {
        showAlert("Non puoi piazzare la tessera in questa posizione! Popola prima le colonne precedenti.");
        fragment5(playerDeck, playerDeckDimension);
    }
    // Fine richiesta valori da utente

    if (rowSelected - 1 >= 0 && !rowPointers[rowSelected -1]) {
        showAlert("Non puoi piazzare la tessera in questa posizione! Popola prima le righe precedenti.");
    } else {
        if (columnSelected >= maxOrizzontalSpan) {
            maxOrizzontalSpan = columnSelected;
        }
        if(rowPointers[rowSelected] == NULL){
            // Se la testa di una determinata linea non esiste, la creo e la popolo
            rowPointers[rowSelected] = generate2DNode(columnSelected, playerDeck[indexSelected][0], playerDeck[indexSelected][1], isReversed, 1,indexSelected, playerDeck);
        } else {
            // Verifico che la posizione sia libera
            if (isSlotOccupied(columnSelected, rowSelected, isVertical)) {
                showAlert("Non puoi piazzare la tessera in questa posizione! La posizione è già occupata.");
                fragment5(playerDeck, playerDeckDimension);
            }
            // Hadling della posizione verticale
            if (isVertical){
                // Scorro la riga sopra e piazzo la tessera verticale alla fine
                gameNode2DLinList *rowPointerTemp = rowPointers[rowSelected];
                while(rowPointerTemp -> next){
                    rowPointerTemp = rowPointerTemp -> next;
                }
                int previousTop = playerDeck[indexSelected][0];
                int previousBottom = playerDeck[indexSelected][1];
                rowPointerTemp -> next = generate2DNode(columnSelected, playerDeck[indexSelected][0], playerDeck[indexSelected][1], isReversed, 0,indexSelected, playerDeck);
                // Scorro la riga sotto e piazzo la tessera verticale alla fine
                rowPointerTemp = rowPointers[rowSelected + 1];
                if (rowPointerTemp == NULL) {
                    rowPointers[rowSelected + 1] = generate2DNode(columnSelected, previousTop, previousBottom, isReversed, 1,indexSelected, playerDeck);
                }else {
                    while(rowPointerTemp -> next){
                        rowPointerTemp = rowPointerTemp -> next;
                        }
                        rowPointerTemp -> next = generate2DNode(columnSelected, previousTop, previousBottom, isReversed, 1,indexSelected, playerDeck);
                }
            } else {
                // Se la testa è già stata creata e non è girata, scorro la lista fino alla fine e aggiungo la nuova tessera
                gameNode2DLinList *rowPointerTemp = rowPointers[rowSelected];
                while(rowPointerTemp -> next){
                    rowPointerTemp = rowPointerTemp -> next;
                }
                rowPointerTemp -> next = generate2DNode(columnSelected, playerDeck[indexSelected][0], playerDeck[indexSelected][1], isReversed, 1,indexSelected, playerDeck);
            }


            
        }
    }

    if(indexSelected >= 0) {
        fragment5(playerDeck, playerDeckDimension);
    }
}

#include <stdio.h>

//Questa funzione, preso l'array bidimensionale indice - indice card, cerca la card corrispondente nel deck e le stampa nel corretto ordine
void printCards(int** deck, int** orderedDeck, int orderedDeckDimension) {
    //Loop attraversio orderDeck
    int lastIndex = -1;
    
    for (int i = 0; i < orderedDeckDimension; i++) {
        if(lastIndex==-1){
            printf("S");
            printf("%d %d", deck[orderedDeckDimension[i][1]][0], deck[orderedDeckDimension[i][1]][1]);
            lastIndex = orderedDeckDimension[i][1];
        }else if(i<lastIndex){
            printf("R");
            printf("%d %d",deck[orderedDeckDimension[i][1]][0], deck[orderedDeckDimension[i][1]][1]);
            lastIndex = orderedDeckDimension[i][1];
        }else
        {
            printf("L");
            printf("%d %d", deck[orderedDeckDimension[i][1]][0], deck[orderedDeckDimension[i][1]][1]);
            lastIndex = orderedDeckDimension[i][1];
        }
        
    }

}
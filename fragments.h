#ifndef __FRAGMENTS_H__
#define __FRAGMENTS_H__
#include "functions.h"

/**
* Questa schermata mostra all'utente le possibili tessere che potrebbero capitare nel mazzo.
@param array gameset
@param int indice tessera iniziale
@param int indice tessera selezionata
@param bool animazione da applicare a spawnScreenWithTitle
*/
void fragment1(int[21][2], int, int, bool);

/**
* Questa schermata permette all'utente di generare un deck di N tessere casuali. 
* @param array gameset
* @param bool animazione da applicare a spawnScreenWithTitle
*/
void fragment2(bool, int[21][2]);

// fragment3 (array, indice tessera iniziale, indice tessera selezionata, animazione da applicare a spawnScreenWithTitle, dimensione dell'array)
void fragment3(int**, int, int, bool, int);

typedef struct gameNodeLin gameNodeLinList;
void fragment4(int**, int, int, bool, int, gameNodeLinList *);

typedef struct gameNode2DLin gameNode2DLinList;
void fragment5(int**, int);

#endif

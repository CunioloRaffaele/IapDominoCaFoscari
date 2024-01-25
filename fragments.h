#ifndef __FRAGMENTS_H__
#define __FRAGMENTS_H__
#include "functions.h"

// fragment1 (array, indice tessera iniziale, indice tessera selezionata, animazione da applicare a spawnScreenWithTitle)
void fragment1(int[21][2], int, int, bool);

// fragment2 (array bidimensionale, animazione da applicare a spawnScreenWithTitle)
void fragment2(bool, int[21][2]);

// fragment3 (array, indice tessera iniziale, indice tessera selezionata, animazione da applicare a spawnScreenWithTitle, dimensione dell'array)
void fragment3(int**, int, int, bool, int);

typedef struct gameNodeLin gameNodeLinList;

void fragment4(int**, int, int, bool, int, gameNodeLinList *);

#endif
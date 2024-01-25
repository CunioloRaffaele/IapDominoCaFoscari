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

/**
* Questa schermata permette all'utente di visualizzare le tessere generate.
* @param array gameset
* @param int indice tessera iniziale
* @param int indice tessera selezionata
* @param bool animazione da applicare a spawnScreenWithTitle
* @param int dimensione dell'array
*/
void fragment3(int**, int, int, bool, int);

/**
 * Questa schermata permette all'utente di giocare a Domino.
 * @param array gameset
 * @param int indice tessera iniziale
 * @param int indice tessera selezionata
 * @param bool animazione da applicare a spawnScreenWithTitle
 * @param int dimensione dell'array
 * @param gameNodeLinList lista di nodi contenente le tessere giocate
 */
typedef struct gameNodeLin gameNodeLinList;
void fragment4(int**, int, int, bool, int, gameNodeLinList *);

/**
 * Questa schermata permette all'utente di giocare a 2D Domino.
 * ATTENZIONE questa schermata modifica il deck del giocatore, quindi non è possibile tornare indietro.
 * @param array gameset
 * @param int dimensione dell'array
 */
typedef struct gameNode2DLin gameNode2DLinList;
void fragment5(int**, int);

#endif

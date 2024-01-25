#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
/**
* @file main.h
* @author Cuniolo Raffaele 903407
* @brief Insieme delle funzioni utili per il programma
*/
#include <stdbool.h>

#define ASCII_Space 32
#define ASCII_1 49
#define ASCII_2 50
#define ASCII_3 51
#define ASCII_4 52
#define ASCII_5 53
#define ASCII_6 54
#define ASCII_7 55
#define ASCII_8 56
#define ASCII_9 57
#define ASCII_0 48
#define ASCII_A 97
#define ASCII_D 100
#define ASCII_Q 113
#define ASCII_E 101
#define ASCII_W 119
#define ASCII_S 115
#define ASCII_Esc 27

/**
* Questa funzione mostra la "grafica testuale" di avvio programma.
*/
void introMessage (void);

/**
* Questa funzione mostra la "grafica testuale" di chiusura programma.
*/
void exitMessage (void);

/**
* Questa funzione mostra la schermata di menu presente appena viene avviato il programma.
*/
void menuUi (void);

/**
* Questa funzione genera set di tessere (anche speciali) che possono essere usate dal player. La funzione va chiamata solo dopo generateTilesComposition().
* @param array gameset
* @param int** array di destinazione
* @param int dimensione array di destinazione
*/
void generatePlayerDeck (int [21][2], int**, int);

/**
* Seleziona il colore del testo del terminale (0 reset - 1 rosso - 2 verde - 3 blu - 4 bianco).
* ATTENZIONE VA USATO PRIMA DEL PRINTF DA STAMPARE E DOPO VA RESETTATO CON 0.
* @param int Codice colore
*/
void colorzz (int);

/**
* Elimina l'intero contenuto della console.
*/
void clearConsole (void);

/**
* Ritorna dimensione terminale (row)
* @return row Dimensione del terminale all'instante in cui viene eseguita la funzione.
*/
int screenRow (void);

/**
* Ritorna dimensione terminale (col)
* @return col Dimensione del terminale all'instante in cui viene eseguita la funzione.
*/
int screenCol (void);

/**
* Printa tanti spazi quanto servono per centrare il testo orizzontalmente e poi stampa il testo.
* @param stringa Stringa da centrare nella finestra del terminale.
*/
void printCentered (char[]);

/**
* Questa funzione disabilita la modalità canonica e la modalità echo del terminale, consentendo al programma di leggere un singolo carattere senza attendere un newline e senza visualizzare il carattere sul terminale.
* Su Unix-like tilizza la libreria termios.h per modificare temporaneamente gli attributi del terminale.
* Su Windows utilizza la funzione getch() della libreria conio.h
* Nel file functions.h ci sono le costanti dei valori ascii da usare nel programma.
* @return int valore ascii del carattere letto.
*/
int getch (void);

/**
* Crea la schermata con un titolo e sposta il cursore alla coordinata corretta.
* @param char Stringa
* @param bool Attivazione o disattivazione dell'animazione. L'animazione va disattivata quando si fa il refresh di una schermata e va attivata quando si cambia schermata.
*/
void spawnScreenWithTitle (char[], bool);

/**
* Genera una tile ascii art e la posizione in una coordinata nel terminale.
* Una tile è composta da due numeri (top e bottom) e una colonna di posizionamento.
* La tile occupa 18 colonne (18 caratteri su ogni riga)
* Al termine dell'esecuzione il cursore (collocato nel posto in cui sarebbe da stampare una nuova tile)  va  mandato a capo con \n
* @param int Numero top
* @param int Numero Bottom
* @param int Colonna nella quale stampare
* @param int Stato della tessera (selezionata = rosso o no = altro colore) (per semplicità viene usato come booleano quindi le tessere selezionate sono tutte di colore rosso)
*/
void spawnTile (int, int, int, int);

/**
* Genera 21 tessere, ciascuna con una coppia di numeri da 1 a 6.
* @param int Numero array di destinazione che va dichiarato come globale
*/
void generateTilesComposition (int[21][2]);

/**
* Data la dimensione dell'array viene preparata una porzione di memoria che contenga l'array bidimensionale (tiles del player nell'indice 0 e 1).
* La memoria allocata va adeguatamente liberata dal chiamante.
* ATTENZIONE: Viene usato un meccanismo di doppia indirezione: puntatori di puntatori. La free va fatta su righe e colonne.
* @param int Dimensione colonne (ogni colonna ha sempre e solo 2 spazi che sono le due facce delle tiles).
* @return int** Matrice
*/
int** allocPlayerDeckMemory (int);

/**
* Funzione che processa i tiles del player (Ai).
* ATTENZIONE: Il chiamante deve liberare adeguatamente la memoria dopo l'utilizzo
* @param int** Array tessere da valutare
* @param int Dimensione array tessere da valutare
* @param int Indice tessera iniziale
* @param int* Puntatore a variabile che conterrà la dimensione dell'array di output
* @return int* Array contenente gli indici in ordine. Se un indice è negativo significa che la tessera corrispondente va girata.
*/
int* processAI (int**, int, int, int*);

/**
* Funzione che trova la miglire tessera da posizionare all'inizio della partita
* @param int** Array tessere da valutare
* @param int Dimensione array tessere da valutare
* @return int Indice tessera da posizionare. Se un indice è negativo significa che la tessera corrispondente va girata.
*/
int aiEvaluation (int**, int);

/**
* Creazione di un popup nativo di OS
* @param char[] Stringa da visualizzare nel popup
*/
void showAlert (char[]);

/**
* Verifica copatibbilità tra due tessere (anche speciale)
* @param int Faccia precedente
* @param int Faccia successiva
*/
bool verifyCompatibility4 (int, int);

// LE SEGUENTI SONO FUNZIONI CHE VANNO USATE SOLO QUANDO IL PROGRAMMA VIENE LANCIATO CON IL PARAMETRO --challenge

/**
* Questa funzione, preso l'array contenentele gli indici delle tiles ordinante, cerca la tile corrispondente nel deck e le stampa nel corretto ordine.
* La stampa viene effettuata con il formato richiesto nel file "progetto.pdf"
* @param int** Deck del giocatore
* @param int* Array risultato Ai
* @param int Dimensione array risultato ai
*/
void printCardsForChallenge (int **, int*, int);

#endif

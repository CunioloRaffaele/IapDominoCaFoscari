#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include <stdbool.h>

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
#define ASCII_Esc 27


void introMessage (void);                                   // Questa funzione mostra la "grafica testuale" di avvio programma.
                                                            // Funzione implementata per rendere più leggibile il main().

void menuUi (void);                                             // Questa funzione mostra la schermata di menu.
                                                            // Funzione implementata per rendere più leggibile il main().
// generate_player_deck (gameset, array, dimensione array)
void generate_player_deck (int [21][2], int**, int);        // Crea set di tessere.

// colorzz (codice colore)
void colorzz (int);                                         // Seleziona il colore del terminale (0 reset - 1 rosso - 2 verde - 3 blu - 4 bianco). 
                                                            // ATTENZIONE VA USATO PRIMA DEL PRINTF DA STAMPARE E DOPO VA RESETTATO CON 0.
                                                            // Non funziona su Windows (stampa solo carattere vuoto) ma solo su Macos e Linux.
void clear_console (void);                                  // Elimina l'intero contenuto della console.

int screen_row (void);                                      // Ritorna dimensione terminale (row)

int screen_col (void);                                      // Ritorna dimensione terminale (col)

int getch (void);                                           // Questa funzione disabilita la modalità canonica e la modalità echo del terminale, consentendo
                                                            // al programma di leggere un singolo carattere senza attendere un newline e senza
                                                            // visualizzare il carattere sul terminale. 
                                                            // Su Unix-like tilizza la libreria termios.h per modificare temporaneamente gli attributi del terminale.
                                                            // Su Windows utilizza la funzione getch() della libreria conio.h
                                                            // Viene ritornato il valore ascii del carattere letto.
                                                            // Nella funzioni ci sono le costanti dei valori ascii da usare nel programma.

// spawn_screen_with_title (titolo, animation)
void spawn_screen_with_title (char[], bool);                // Crea la schermata con un titolo sovrastante e sposta il cursore alla coordinata corretta

// spawn_tile (numero top, numero bottom, colonna, is selected)
void spawn_tile (int, int, int, bool);                      // Genera una tile ascii art e la posizione in una coordinata nel terminale.
                                                            // una tile è composta da due numeri (top e bottom) e una colonna di posizionamento.
                                                            // La tile occupa 18 colonne (18 caratteri su ogni riga)
                                                            // Al termine dell'esecuzione il cursore (collocato nel posto in cui sarebbe da stampare una nuova tile)  va  mandato a capo con \n

// generate_tiles_composition (array)           
void generate_tiles_composition (int[21][2]);               // Genera 21 tessere, ciascuna con una coppia di numeri da 1 a 6.

// alloc_player_deck_memory (dimensione array)
int** alloc_player_deck_memory (int);                       // Data la dimensione dell'array viene preparata una porzione di memoria che contenga 
                                                            // l'array bidimensionale (tiles del player nell'indice 0 e 1)
                                                            // RICORDARSI di liberare adeguatamente la memoria dopo l'utilizzo e prima di terminare il programma.

// processAI (array, dimensione array, indice tessera iniziale, puntatore a variabile che conterrà la dimensione dell'array di output)
int* processAI (int**, int, int, int*);                     // Funzione che processa i tiles del player e restituisce un array contenente gli indici in ordine.
                                                            // RICORDARSI di liberare adeguatamente la memoria dopo l'utilizzo e prima di terminare il programma.

// AiEvaluation (array, dimensione array)
int AiEvaluation (int**, int);

// show_alert (stringa da visualizzare nel popup)
void show_alert (char[]);                                   // Creazione di un popup nativo di OS

// LE SEGUENTI SONO FUNZIONI CHE VANNO USATE SOLO QUANDO IL PROGRAMMA VIENE LANCIATO CON IL PARAMETRO --challenge

// is2dArrayEmpty (array playerDeck, array risultato Ai, int dimensione array risultato ai)
void printCardsForChallenge (int **, int*, int);            // Questa funzione, preso l'array contenente gli indici delle tiles ordinate, cerca la tile corrispondente 
                                                            // nel deck e le stampa nel corretto ordine

#endif

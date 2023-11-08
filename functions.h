#include <stdio.h>

#include "functions/initialization.c"
#include "functions/terminal_handler.c"
#include "functions/intro_message.c"
#include "functions/tiles_generator.c"

void introMessage ();                                       // Questa funzione mostra la "grafica testuale" di avvio programma.
                                                            // Funzione implementata per rendere più leggibile il main().
// generate_player_deck (array, dimensione array)
void generate_player_deck (int*, int);                            // Questa funzione contiene tutte le procedure da effettuare all'avvio del programma.
                                                            // Crea set di tessere e porta a 0 l'array di tessere del giocatore.

// colorzz (codice colore)
void colorzz (int);                                         // Seleziona il colore del terminale (0 reset - 1 rosso - 2 verde - 3 blu - 4 bianco). 
                                                            // ATTENZIONE VA USATO PRIMA DEL PRINTF DA STAMPARE E DOPO VA RESETTATO CON 0.
                                                            // Non funziona su Windows (stampa solo carattere vuoto) ma solo su Macos e Linux.
void clear_console ();                                      // Elimina l'intero contenuto della console.

int screen_row ();                                          // Ritorna dimensione terminale (row)

int screen_col ();                                          // Ritorna dimensione terminale (col)

// spawn_screen_with_title (titolo)
void spawn_screen_with_title (char[]);                      // Crea la schermata con un titolo sovrastante e sposta il cursore alla coordinata corretta

// spawn_tile (numero top, numero bottom)
void spawn_tile (int, int);                                 // Genera una tile ascii art.

// generate_tiles_composition (array)
void generate_tiles_composition (int[20][2]);               // Genera 21 tessere, ciascuna con una coppia di numeri da 1 a 6.
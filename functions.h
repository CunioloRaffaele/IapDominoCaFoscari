#include <stdio.h>

#include "functions/initialization.h"
#include "functions/colorzz.h"

// initialization (array, dimensione array)
void initialization (int*, int);                            // Questa funzione contiene tutte le procedure da effettuare all'avvio del programma.
                                                            // Crea set di tessere e porta a 0 l'array di tessere del giocatore.
// colorzz (codice colore)
void colorzz (int);                                         // Seleziona il colore del terminale (0 reset - 1 rosso - 2 verde - 3 blu - 4 bianco). 
                                                            // ATTENZIONE VA USATO PRIMA DEL PRINTF DA STAMPARE E DOPO VA RESETTATO CON 0.
                                                            // Non funziona su Windows (stampa solo carattere vuoto) ma solo su Macos e Linux.

# IapDominoCaFoscari Progetto di gruppo 2023/2024

> [!NOTE]
> Come richiesto dal docente, in sede d'esame, verrà presentata anche la seguente relazione relativa a 
> 1. Descrizione della **struttura del progetto** 
> 2. **Organizzazione del lavoro** tra i componenti del gruppo
> 3. Principali **diﬀicoltà** incontrate

<p align="center" width="100%">
<img width="500" hight="500" alt="Screenshot 2023-12-07 at 16 55 31" src="https://github.com/CunioloRaffaele/IapDominoCaFoscari/assets/64699933/e55f727a-3c23-4b7f-ba2e-7c69fe52948f">
<img alt="Screenshot 2023-12-15 at 10 11 57" src="https://github.com/CunioloRaffaele/IapDominoCaFoscari/assets/64699933/e9f87b3e-d3da-4d6a-bab7-e54fdddb5ccc">
</p>

# Compilazione
Il codice deve compilare con il comando
```sh
gcc -O2 -std=c99 --pedantic *.c -o iap.exe
```
Sarà inoltre possibile invocare l'eseguibile con il parametro, che abilita  abilita la consegna per le challenge
```sh
.\iap.exe --challenge
```
# 1. Descrizione della struttura del progetto

## Panoramica

Questo programma in C implementa un versatile gioco del Domino con una serie di funzionalità che si adattano sia al gameplay standard che alle sfide avanzate. Il gioco include opzioni per visualizzare le tessere, ottenere tessere, giocare al Domino standard, giocare al Domino 2D e una modalità sfida dedicata. La modalità sfida fornisce una valutazione del mazzo di tessere del giocatore e suggerisce la miglior tessera di partenza.

## Inizio

Per compilare ed eseguire il programma, utilizza il seguente comando:

```
make run
```


Questo comando presuppone che le dipendenze e i file necessari siano presenti.

## Funzionalità

### 1. Visualizzazione delle Tessere

Scegli l'opzione 1 nel menu principale per visualizzare le tessere possibili. Questo include la visualizzazione delle varie tessere standard e di tessere speciali presenti nel set di gioco.

### 2. Ottenere tessere

Se il mazzo non è ancora assegnato (NULL), seleziona l'opzione 2 nel menu principale per ottenere un numero specifico (N) di tessere. Questa funzione serve per configurare il mazzo del giocatore.

### 3. Visualizza le tue Tessere

Scegli l'opzione 3 per visualizzare le tessere attualmente assegnate al giocatore. Questa opzione è disponibile solo se il giocatore dispone di un mazzo di tessere valido.

### 4. Gioca al Domino

Seleziona l'opzione 4 per avviare una partita standard di Domino. Questa opzione guiderà i giocatori attraverso il processo di gioco.

### 5. Gioca al Domino 2D

Scegli l'opzione 5 per giocare a una variante del gioco nota come Domino 2D. Questa variante permette di posizionare le tessere in maniera verticale, agli estremi del piano di gioco facendo "crescere" il domino verso il basso. 

### Uscita dal Programma

Seleziona qualsiasi altro tasto per uscire dal programma in modo ordinato.

## Modalità Sfida

Per entrare nella modalità sfida, esegui il programma con il flag --challenge. La modalità sfida comporta una configurazione più avanzata in cui il giocatore inserisce le dimensioni e i dettagli del proprio mazzo di tessere. Il programma fornisce quindi una valutazione dell'IA e suggerisce la miglior tessera di partenza in base al mazzo del giocatore.

```
./domino --challenge
```

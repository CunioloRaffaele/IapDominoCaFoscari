# IapDominoCaFoscari Progetto di gruppo 2023/2024

> [!NOTE]
> Come richiesto dal docente, in sede d'esame, verrà presentata anche la seguente relazione relativa a 
> 1. Descrizione della **struttura del progetto** 
> 2. **Organizzazione del lavoro** tra i componenti del gruppo
> 3. Principali **diﬀicoltà** incontrate

<p align="center" width="100%">
  <img width="1212" alt="projImageGitHub" src="https://github.com/CunioloRaffaele/IapDominoCaFoscari/assets/64699933/66111570-92c4-4882-833d-e44da926f7f8">
</p>

# Compilazione
Download del repository pubblico
```sh
git clone https://github.com/CunioloRaffaele/IapDominoCaFoscari.git
```
Il codice deve compilare con il comando (ma il progetto è configurato anche con CMakeList.txt)
```sh
gcc -O2 -std=c99 --pedantic *.c ./fragments/*.c ./functions/*.c -o iap
```
Sarà inoltre possibile invocare l'eseguibile con il parametro, che abilita  abilita la consegna per le challenge
```sh
./iap --challenge
```
# Descrizione e struttura del progetto
Questo programma in C implementa una versione del gioco "Domino" con una serie di funzionalità che si adattano sia al gameplay standard che a modallità più complesse come il gameplay automatico e il domino su due dimensioni. Il programma, nel menù principale, include opzioni per visualizzare le tessere, ottenere tessere, giocare al Domino standard e giocare al Domino 2D. Inoltre è stata inclusa una modalità di debug dell'algoritmo di gampeplay automatico richiamabile con "--challenge".
* I vari menù sono stati implementati con la logica dei "fragments" ispirata allo sviluppo Android. Ogni menù, infatti, definisce e gestisce il proprio layout, ha un proprio ciclo di vita e può gestire i propri eventi di input fino alla sua chiusura.
* I componenti grafici e le parti logiche riutilizzabili sono definiti nella cartella "functions". Tutti i componenti platform-specific sono stati sviluppati e testati singolarmente in un momento iniziale, per essere poi incapsulati in singole funzioni facilmente riutilizzabili. <br>Il programma è compatibile con Windows, MacOs e Linux (con X window system).
* Si è deciso di non usare librerie esterne, se non quelle fornite dall'Os come <sys/ioctl.h> <unistd.h> <termios.h> <windows.h> <conio.h>

## Funzionalità

### 1. Visualizzazione delle Tessere

>Selezionare l'opzione 1 nel menu principale per visualizzare l'elenco delle possibili tessere che potrebbero capitare nel mazzo. Questo include la visualizzazione delle varie tessere standard e di tessere speciali presenti nel set di gioco.

### 2. Ottenere tessere

>Se il mazzo non è ancora stato generato, selezionare l'opzione 2 nel menu principale per ottenere un numero specifico (N) di tessere random.

### 3. Visualizza le tue Tessere

>Selezionare l'opzione 3 per visualizzare le tessere attualmente assegnate. Questa opzione è disponibile solo se il giocatore dispone di un mazzo di tessere valido.

### 4. Gioca al Domino

>Selezionare l'opzione 4 per avviare una partita standard di Domino. Questa opzione potrà anche guidare i giocatori attraverso il processo di gioco suggerendo mosse e calcolando l'attuale punteggio di gioco.


### 5. Gioca al Domino 2D

>Selezionare l'opzione 5 per giocare a una variante del gioco nota come "Domino 2D". Questa variante permette di posizionare le tessere in maniera orizzontale e verticale su un tavolo di gioco X x Y. 

# Organizzazione lavoro di gruppo
### Software Utilizzati:
* VS Code (per le sessioni di debug in collaborazione)
* Discord (per le sessioni di debug in collaborazione)
* JetBrain CLion (per lo sviluppo autonomo)
* GitHub (per hosting e controllo delle versioni del codice sorgente)
### Organizzazione iniziale e divisione del lavoro tra i componenti del gruppo:
La fase iniziale del progetto, concernente la sua pianificazione, ha coinvolto una discussione dettagliata finalizzata alla definizione degli obiettivi, dei requisiti e degli strumenti da impiegare.
<br>In una fase successiva, sempre concernente al momento di pianificazione iniziale, sono state implementate le funzioni necessarie, le quali ciascun membro avrebbe successivamente utilizzato per integrare le funzionalità di propria competenza.
<br>Il team ha adottato un approccio basato su branch utilizzando la piattaforma GitHub. Ciascun membro ha operato su un branch separato, facilitando così una gestione strutturata e isolata delle diverse componenti del codice.
<br>A intervalli settimanali sono stati condotti incontri di verifica e test al fine di risolvere eventuali problematiche legate alla fusione delle nuove sezioni di codice e per verificare il conseguimento delle Milestone stabilite.

##### Barison Alberto:
* Conduzione di verifiche e test specifici per funzioni Windows (e WSL).
* Design della versione iniziale della Ai (domino lineare senza tessere speciali).
* Design e implementazione domino 2D.
* Design e implementazione dell'Ai in grado di trovare la migliore tessera da giocare a inizio partita.
##### Cuniolo Raffaele:
* Coordinamento del progetto e mantenimento repository GitHub.
* Redazione della documentazione e supervisione dei commenti nel codice.
* Conduzione di verifiche e test specifici per funzioni Linux e MacOs.
* Design e implementazione della versione iniziale della Ai (domino lineare senza tessere speciali).
* Design e implementazione della versione rivisitata della Ai (domino lineare con tessere speciali).
* Design e implementazione interfaccia grafica e flusso di interazione.
* Design e implementazione domino lineare.
* Design e implementazione domino 2D.
##### Veggis Francesco:
* Conduzione di verifiche e test specifici per funzioni Windows (e WSL).
* BugFix Ai.
* Design e implementazione dell'Ai in grado di trovare la migliore tessera da giocare a inizio partita.

# Diﬀicoltà incontrate
Si sono incontrate difficoltà nella gestione delle scadenze inizialmente prefissate, specie in seguito alla pubblicazione delle due challenge. 
<br>L'utilizzo corretto delle funzioni già create e l'adozione di uno stile di programmazione uniforme si è rivelato un ulteriore ostacolo, richiedendo un costante sforzo per mantenere il sorgente "pulito" e privo di ripetizioni o conflitti.
<br>Oltre a ciò, vista la carenza di tempo dovuta a vari problemi organizzativi, non è stata particolarmente curata la qualità del codice, che risulta talvolta difficile da comprendere e interpretare.

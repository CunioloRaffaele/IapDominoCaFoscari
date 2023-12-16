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
# Descrizione e struttura del progetto
Questo programma in C implementa una versione del gioco "Domino" con una serie di funzionalità che si adattano sia al gameplay standard che a modallità più complesse come il gameplay automatico e il domino su due dimensioni. Il programma, nel menù principale, include opzioni per visualizzare le tessere, ottenere tessere, giocare al Domino standard e giocare al Domino 2D. Inoltre è stata inclusa una modalità di debug dell'algoritmo di gampeplay automatico richiamabile con "--challenge".

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

>Selezionare l'opzione 5 per giocare a una variante del gioco nota come "Domino 2D". Questa variante permette di posizionare le tessere in maniera orizzontale e verticale. 

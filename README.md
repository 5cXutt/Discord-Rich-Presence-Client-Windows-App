# Discord-Rich-Presence-Client-Windows-App
Un semplice client per aggiornare la **Rich Presence** di Discord utilizzando la Pipe IPC di Discord. Questo programma invia informazioni personalizzate come il **gioco in corso**, il **livello**, le **immagini** e i **pulsanti interattivi** direttamente al profilo Discord dell'utente, per un'esperienza immersiva durante la sessione di gioco.

## Caratteristiche

- **Integrazione con Discord**: Aggiorna automaticamente la tua presenza su Discord con dettagli personalizzati.
- **Pulsanti Interattivi**: Aggiungi pulsanti per collegamenti esterni o per invitare altri a giocare con te.
- **Immagini personalizzate**: Imposta immagini di gioco personalizzate per una migliore visibilità del gioco in corso.
- **Aggiornamenti automatici**: L'attività viene aggiornata periodicamente ogni 15 secondi, per mantenere la tua presenza sempre attiva.

## Come usare

1. **Crea un'app Discord**: Ottieni il tuo `CLIENT_ID` creando un'applicazione su [Discord Developer Portal](https://discord.com/developers/applications).
2. **Compila il codice**: Sostituisci il valore di `CLIENT_ID` con quello ottenuto.
3. **Esegui il programma**: Una volta eseguito, il client si connetterà automaticamente al processo di Discord e aggiornerà la tua attività.

```bash
# Comando per eseguire il programma
g++ -o discord_rich_presence discord_rich_presence.cpp -lstdc++ -lgdi32
./discord_rich_presence

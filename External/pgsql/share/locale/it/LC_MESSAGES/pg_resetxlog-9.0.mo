��    N      �  k   �      �  9   �  -   �  ,     8   >  3   w  0   �  *   �  N     /   V  N   �     �  *   �  +    	     L	  !   h	  +   �	  )   �	  #   �	  &   
  -   +
  !   Y
  !   {
  +   �
  "   �
  (   �
       S   *  #   ~  #   �  #   �  #   �  #     #   2  \   V  +   �  0   �        @   1  D   r  &   �  -   �       )     )   F  )   p  )   �  )   �  )   �  )     )   B  )   l  )   �     �  V   �  )   4  )   ^  )   �  ,   �  )   �  )   	  )   3  )   ]  )   �  )   �  )   �  	     �        �  &   �  !   �  )     -   :     h     u     ~     �  )   �  �  �  O   �  0   �  1   .  ?   `  I   �  2   �  7     X   U  =   �  c   �  *   P  8   {  9   �  !   �  '     2   8  .   k  +   �  ,   �  7   �  (   +  )   T  0   ~  +   �  0   �       ]   "  &   �  &   �  &   �  &   �  &     &   C  k   j  7   �  9     6   H  C     Z   �  2     9   Q     �  6   �  )   �  +   �  0   (  5   Y  I   �  =   �  @      2   X   *   �      �   W   �   /   .!  /   ^!  '   �!  )   �!  .   �!  -   "  )   ="  2   g"  1   �"  2   �"  0   �"  	   0#  �   :#  %   �#  -   #$  %   Q$  +   w$  D   �$     �$  
   �$     %     %  *   /%        5       $       +           -      ?   *      F                  <       6      L   '           M   /          G   8               K   1          :             E      	   B       &                  C   ;   0               !      ,         N      J      A             @      #   %   9   4          2         )   >       
       I   7              (   .               "   H       3      D   =    
If these values seem acceptable, use -f to force reset.
 
Report bugs to <pgsql-bugs@postgresql.org>.
   --help          show this help, then exit
   --version       output version information, then exit
   -O OFFSET       set next multitransaction offset
   -e XIDEPOCH     set next transaction ID epoch
   -f              force update to be done
   -l TLI,FILE,SEG force minimum WAL starting location for new transaction log
   -m XID          set next multitransaction ID
   -n              no update, just show extracted control values (for testing)
   -o OID          set next OID
   -x XID          set next transaction ID
 %s resets the PostgreSQL transaction log.

 %s: OID (-o) must not be 0
 %s: cannot be executed by "root"
 %s: could not change directory to "%s": %s
 %s: could not create pg_control file: %s
 %s: could not delete file "%s": %s
 %s: could not open directory "%s": %s
 %s: could not open file "%s" for reading: %s
 %s: could not open file "%s": %s
 %s: could not read file "%s": %s
 %s: could not read from directory "%s": %s
 %s: could not write file "%s": %s
 %s: could not write pg_control file: %s
 %s: fsync error: %s
 %s: internal error -- sizeof(ControlFileData) is too large ... fix PG_CONTROL_SIZE
 %s: invalid argument for option -O
 %s: invalid argument for option -e
 %s: invalid argument for option -l
 %s: invalid argument for option -m
 %s: invalid argument for option -o
 %s: invalid argument for option -x
 %s: lock file "%s" exists
Is a server running?  If not, delete the lock file and try again.
 %s: multitransaction ID (-m) must not be 0
 %s: multitransaction offset (-O) must not be -1
 %s: no data directory specified
 %s: pg_control exists but has invalid CRC; proceed with caution
 %s: pg_control exists but is broken or unknown version; ignoring it
 %s: transaction ID (-x) must not be 0
 %s: transaction ID epoch (-e) must not be -1
 64-bit integers Blocks per segment of large relation: %u
 Bytes per WAL segment:                %u
 Catalog version number:               %u
 Database block size:                  %u
 Database system identifier:           %s
 Date/time type storage:               %s
 First log file ID after reset:        %u
 First log file segment after reset:   %u
 Float4 argument passing:              %s
 Float8 argument passing:              %s
 Guessed pg_control values:

 If you are sure the data directory path is correct, execute
  touch %s
and try again.
 Latest checkpoint's NextMultiOffset:  %u
 Latest checkpoint's NextMultiXactId:  %u
 Latest checkpoint's NextOID:          %u
 Latest checkpoint's NextXID:          %u/%u
 Latest checkpoint's TimeLineID:       %u
 Latest checkpoint's oldestXID's DB:   %u
 Latest checkpoint's oldestXID:        %u
 Maximum columns in an index:          %u
 Maximum data alignment:               %u
 Maximum length of identifiers:        %u
 Maximum size of a TOAST chunk:        %u
 Options:
 The database server was not shut down cleanly.
Resetting the transaction log might cause data to be lost.
If you want to proceed anyway, use -f to force reset.
 Transaction log reset
 Try "%s --help" for more information.
 Usage:
  %s [OPTION]... DATADIR

 WAL block size:                       %u
 You must run %s as the PostgreSQL superuser.
 by reference by value floating-point numbers pg_control values:

 pg_control version number:            %u
 Project-Id-Version: PostgreSQL 8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-03-26 13:22+0000
PO-Revision-Date: 2010-03-27 12:44:19+0100
Last-Translator: Gabriele Bartolini <gabriele.bartolini@2ndquadrant.it>
Language-Team: Gruppo traduzioni ITPUG <traduzioni@itpug.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Poedit-Language: Italian
X-Poedit-Country: ITALY
X-Poedit-SourceCharset: utf-8
 
Se questi parametri sembrano accettabili, utilizzate -f per forzare un reset.
 
Segnalare bachi a <pgsql-bugs@postgresql.org>.
   --help           mostra questo aiuto, poi esci
   --version       mostra informazioni sulla versione, poi esci
   -O OFFSET        imposta il prossimo multitransactio ID di transazione
   -x XIDEPOCH     imposta il prossimo ID di epoch
   -f              forza lesecuzione dell'aggiornamento
   -l TLI,FILE,SEG forza il minimo punto d'inizio WAL per il nuovo log della transazione
   -m XID          imposta il prossimo ID di multitransaction
   -n              nessun aggiornamento, mostra solo i valori di controllo estrati (solo per prove)
   -o OID          imposta il prossimo OID
   -x XID          imposta il prossimo ID di transazione
 %s riavvia il registro delle transazioni di PostgreSQL.

 %s: l'OID (-o) non deve essere 0
 %s non può esssere eseguita da "root"
 %s: Impossibile modificare la cartella a "%s": %s
 %s: impossibile creare il file pg_control: %s
 %s: impossibile eliminare il file "%s": %s
 %s: impossibile aprire la cartella "%s": %s
 %s: impossibile aprire il file "%s" per la lettura: %s
 %s: impossibile aprire il file "%s": %s
 %s: impossibile leggere il file "%s": %s
 %s: impossibile leggere dalla cartella "%s": %s
 %s: impossibile scrivere sul file "%s": %s
 %s: impossibile scrivere il file pg_control: %s
 %s: errore fsync: %s
 %s: errore interno -- sizeof(ControlFileData) è troppo grande ... sistemare PG_CONTROL_SIZE
 %s: parametro errato per l'opzione -O
 %s: parametro errato per l'opzione -e
 %s: parametro errato per l'opzione -l
 %s: parametro errato per l'opzione -m
 %s: parametro errato per l'opzione -o
 %s: parametro errato per l'opzione -x
 %s: il lock file "%s" esiste
Il server è in esecuzione? Se non lo è, eliminate il lock file e riprovate.
 %s: l'ID della multitransazione (-m) non deve essere 0
 %s: l'offset di una multitransazione (-O) must not be -1
 %s: non è stata specificata una directory per i dati
 %s: pg_control esiste ma ha un CRC invalido; procedere con cautela
 %s: pg_control esiste ma è inutilizzabile o è una versione sconosciuta; verrà ignorato
 %s: l'ID della transazione (-x) non deve essere 0
 %s: l'ID epoch della transazione (-e) non deve essere -1
 Interi a 64 bit Blocchi per ogni segmento di una grossa relazione: %u
 Byte per segmento WAL:                %u
 Numero versione catalogo:               %u
 Dimensione blocco database:                  %u
 Identificatore sistema database:                  %s
 Tipo di immagazzinaggio per dati temporali (date/time):               %s
 primo ID file di registro dopo il reset:                  %u
 primo segmento del file di log dopo il reset:                %u
 argomento passato di tipo float4:              %s
 argomento passato float8:              %s
 Valori pg_control indovinati:

 Se sei sicuro che il percorso della cartella è corretto, esegui
  touch %s
e riprova.
 Ultimo checkpoint NextMultiOffset:          %u
 Ultimo checkpoint NextMultiXactId:          %u
 Ultimo checkpoint NextOID:          %u
 Ultimo checkpoint NextXID:          %u%u
 Ultimo TimeLineId del checkpoint:          %u
 Ultimo checkpoint oldestXID del database: %u
 Ultimo checkpoint oldestXID:          %u
 Massimo numero di colonne in un indice:        %u
 Massimo allineamento dei dati:                %u
 Lunghezza massima degli identificatori:        %u
 Massima dimensione di un TOAST chunk:        %u
 Opzioni:
 Il server database non è stato chiuso correttamente.
Resettare il registro delle trasazioni può causare una perdita di dati.
Se volete continuare comunque, utilizzate -f per forzare il reset.
 registro delle transazioni riavviato
 Prova "%s --help" per maggiori informazioni.
 Utilizzo:
  %s [OPZIONI]... DATADIR

 Dimensione blocco WAL:                  %u
 Si deve obbligatoriamente eseguire %s come superuser di PostgreSQL.
 per reference per valore Numeri in virgola mobile Valori pg_control:

 Numero versione pg_control:            %u
 
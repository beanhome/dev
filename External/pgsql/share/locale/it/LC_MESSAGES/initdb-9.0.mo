��    �      4  �   L        R        l  
   �     �  -   �  �   �  �   ^    �  A     5   H  J   ~     �  6   �  P     C   m  :   �  ]   �  4   J  B     H   �  G     >   S  9   �  3   �  ?      /   @  -   p  y   �  (     #   A  7   e  (   �  ,   �  '   �  3     D   O  (   �  8   �  -   �  -   $  /   R  "   �  6   �  +   �       0     ;   P  $   �  /   �     �  $   �  ~   $  1   �     �  /   �  J   #  �   n     6  C   I  -   �  8   �  !   �  ,     /   C  4   s  A   �  @   �  ,   +  P   X  I   �  b   �     V     g  �   �  [   
     f          �  ;   �  9   �  �   +  >   �  ;   �    7  u   H   q   �   f   0!  s   �!  &   "     2"     :"  &   I"  0   p"  .   �"  )   �"  )   �"  "   $#  #   G#  "   k#      �#  (   �#  "   �#     �#  "   $  !   9$  ,   [$  $   �$  *   �$  %   �$  !   �$      %     :%     U%      p%     �%     �%  -   �%  0   �%     (&     G&     c&  *   w&  )   �&     �&     �&  &   �&  %   '     ,'  +   B'  !   n'  �  �'  V   f)  )   �)  
   �)     �)  2   *  �   6*  �   �*  n  �+  j   -  5   w-  N   �-     �-  :   .  w   S.  m   �.  9   9/  k   s/  <   �/  I   0  H   f0  u   �0  9   %1  9   _1  ;   �1  A   �1  3   2  9   K2  �   �2  1   3  (   Q3  H   z3  -   �3  2   �3  -   $4  C   R4  Q   �4  /   �4  7   5  7   P5  9   �5  8   �5  +   �5  >   '6  -   f6  '   �6  9   �6  W   �6  +   N7  I   z7     �7  )   �7  �   8  @   �8      �8  8   �8  ]   19  �   �9     N:  q   d:  6   �:  T   ;  (   b;  F   �;  >   �;  ?   <  \   Q<  H   �<  3   �<  f   +=  c   �=  b   �=     Y>  *   g>  �   �>  W   ?      r?  !   �?     �?  @   �?  :   @  �   P@  >   �@  G   A     gA  s   �B  |   �B  p   yC  v   �C  /   aD  
   �D     �D  -   �D  =   �D  9   E  4   XE  +   �E  "   �E  #   �E  &    F  '   'F  2   OF  )   �F  #   �F  *   �F  *   �F  6   &G  0   ]G  6   �G  -   �G  )   �G      H     >H  !   WH  (   yH  $   �H  %   �H  5   �H  5   #I  &   YI  "   �I     �I  3   �I  6   �I     &J     *J  8   <J  6   uJ     �J  ;   �J  "   K           V       k   A   S   c              o   O   !       \   9   i       C   >   y   (       g          ]           t          z   b      <   ?   s          )   m      r      f       H   �       Y   W   l   [   /   _   N   U       `   B       h                                L           "   @   F   a   0   #   1   :          P   Q   '   ;   j   ,             8              4      �   	   K              -       �   e      M              d               %       I   n      �      +   ^   3   =   D   6              7   w   J   u   Z       $       .       q      ~       x   p       X          
   E         T       G       }          {   &   2       R          *   |   v   5        
If the data directory is not specified, the environment variable PGDATA
is used.
 
Less commonly used options:
 
Options:
 
Other options:
 
Report bugs to <pgsql-bugs@postgresql.org>.
 
Success. You can now start the database server using:

    %s%s%spostgres%s -D %s%s%s
or
    %s%s%spg_ctl%s -D %s%s%s -l logfile start

 
WARNING: enabling "trust" authentication for local connections
You can change this by editing pg_hba.conf or using the -A option the
next time you run initdb.
       --lc-collate=, --lc-ctype=, --lc-messages=LOCALE
      --lc-monetary=, --lc-numeric=, --lc-time=LOCALE
                            set default locale in the respective category for
                            new databases (default taken from environment)
       --locale=LOCALE       set default locale for new databases
       --no-locale           equivalent to --locale=C
       --pwfile=FILE         read password for the new superuser from file
   %s [OPTION]... [DATADIR]
   -?, --help                show this help, then exit
   -A, --auth=METHOD         default authentication method for local connections
   -E, --encoding=ENCODING   set default encoding for new databases
   -L DIRECTORY              where to find the input files
   -T, --text-search-config=CFG
                            default text search configuration
   -U, --username=NAME       database superuser name
   -V, --version             output version information, then exit
   -W, --pwprompt            prompt for a password for the new superuser
   -X, --xlogdir=XLOGDIR     location for the transaction log directory
   -d, --debug               generate lots of debugging output
   -n, --noclean             do not clean up after errors
   -s, --show                show internal settings
  [-D, --pgdata=]DATADIR     location for this database cluster
 %s initializes a PostgreSQL database cluster.

 %s: "%s" is not a valid server encoding name
 %s: cannot be run as root
Please log in (using, e.g., "su") as the (unprivileged) user that will
own the server process.
 %s: could not access directory "%s": %s
 %s: could not access file "%s": %s
 %s: could not change permissions of directory "%s": %s
 %s: could not create directory "%s": %s
 %s: could not create symbolic link "%s": %s
 %s: could not execute command "%s": %s
 %s: could not find suitable encoding for locale %s
 %s: could not find suitable text search configuration for locale %s
 %s: could not get current user name: %s
 %s: could not obtain information about current user: %s
 %s: could not open file "%s" for reading: %s
 %s: could not open file "%s" for writing: %s
 %s: could not read password from file "%s": %s
 %s: could not write file "%s": %s
 %s: data directory "%s" not removed at user's request
 %s: directory "%s" exists but is not empty
 %s: encoding mismatch
 %s: failed to remove contents of data directory
 %s: failed to remove contents of transaction log directory
 %s: failed to remove data directory
 %s: failed to remove transaction log directory
 %s: file "%s" does not exist
 %s: file "%s" is not a regular file
 %s: input file "%s" does not belong to PostgreSQL %s
Check your installation or specify the correct path using the option -L.
 %s: input file location must be an absolute path
 %s: invalid locale name "%s"
 %s: locale %s requires unsupported encoding %s
 %s: must specify a password for the superuser to enable %s authentication
 %s: no data directory specified
You must identify the directory where the data for this database system
will reside.  Do this with either the invocation option -D or the
environment variable PGDATA.
 %s: out of memory
 %s: password prompt and password file cannot be specified together
 %s: removing contents of data directory "%s"
 %s: removing contents of transaction log directory "%s"
 %s: removing data directory "%s"
 %s: removing transaction log directory "%s"
 %s: symlinks are not supported on this platform %s: too many command-line arguments (first is "%s")
 %s: transaction log directory "%s" not removed at user's request
 %s: transaction log directory location must be an absolute path
 %s: unrecognized authentication method "%s"
 %s: warning: specified text search configuration "%s" might not match locale %s
 %s: warning: suitable text search configuration for locale %s is unknown
 Encoding %s is not allowed as a server-side encoding.
Rerun %s with a different locale selection.
 Enter it again:  Enter new superuser password:  If you want to create a new database system, either remove or empty
the directory "%s" or run %s
with an argument other than "%s".
 If you want to store the transaction log there, either
remove or empty the directory "%s".
 Passwords didn't match.
 Rerun %s with the -E option.
 Running in debug mode.
 Running in noclean mode.  Mistakes will not be cleaned up.
 The database cluster will be initialized with locale %s.
 The database cluster will be initialized with locales
  COLLATE:  %s
  CTYPE:    %s
  MESSAGES: %s
  MONETARY: %s
  NUMERIC:  %s
  TIME:     %s
 The default database encoding has accordingly been set to %s.
 The default text search configuration will be set to "%s".
 The encoding you selected (%s) and the encoding that the
selected locale uses (%s) do not match.  This would lead to
misbehavior in various character string processing functions.
Rerun %s and either do not specify an encoding explicitly,
or choose a matching combination.
 The files belonging to this database system will be owned by user "%s".
This user must also own the server process.

 The program "postgres" is needed by %s but was not found in the
same directory as "%s".
Check your installation.
 The program "postgres" was found by "%s"
but was not the same version as %s.
Check your installation.
 This might mean you have a corrupted installation or identified
the wrong directory with the invocation option -L.
 Try "%s --help" for more information.
 Usage:
 caught signal
 child process exited with exit code %d child process exited with unrecognized status %d child process was terminated by exception 0x%X child process was terminated by signal %d child process was terminated by signal %s copying template1 to postgres ...  copying template1 to template0 ...  could not change directory to "%s" could not find a "%s" to execute could not identify current directory: %s could not open directory "%s": %s
 could not read binary "%s" could not read directory "%s": %s
 could not read symbolic link "%s" could not remove file or directory "%s": %s
 could not set junction for "%s": %s
 could not stat file or directory "%s": %s
 could not write to child process: %s
 creating configuration files ...  creating conversions ...  creating dictionaries ...  creating directory %s ...  creating information schema ...  creating subdirectories ...  creating system views ...  creating template1 database in %s/base/1 ...  fixing permissions on existing directory %s ...  initializing dependencies ...  initializing pg_authid ...  invalid binary "%s" loading PL/pgSQL server-side language ...  loading system objects' descriptions ...  ok
 out of memory
 selecting default max_connections ...  selecting default shared_buffers ...  setting password ...  setting privileges on built-in objects ...  vacuuming database template1 ...  Project-Id-Version: PostgreSQL 8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-03-26 13:16+0000
PO-Revision-Date: 2010-09-25 00:44+0300
Last-Translator: Gabriele Bartolini <gabriele.bartolini@2ndquadrant.it>
Language-Team: Gruppo traduzioni ITPUG <traduzioni@itpug.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Poedit-Language: Italian
X-Poedit-Country: ITALY
X-Poedit-SourceCharset: utf-8
 
Se la directory dati non è specificata, viene usata la variabile
d'ambiente PGDATA.
 
Opzioni utilizzate meno frequentemente:
 
Opzioni:
 
Altre opzioni:
 
Segnalate i bachi a <pgsql-bugs@postgresql.org>.
 
Successo. Ora si può attivare il database server con:

    %s%s%spostgres%s -D %s%s%s
oppure
    %s%s%spg_ctl%s -D %s%s%s -l logfile start

 
ATTENZIONE: abilitazione dell'autenticazione "trust" per le connesioni
locali. E' possibile cambiare questa impostazione modificando il file
pg_hba.conf o utilizzando il flag -A alla prossima esecuzione di initdb.
   --lc-collate, --lc-ctype, --lc-messages=LOCALE
  --lc-monetary, --lc-numeric, --lc-time=LOCALE
                            inizializza il nuovo database cluster con il locale
                            specificato nella categoria corrispondente. Il
                            valore predefinito viene preso dalle variabili
                            d'ambiente
       --locale=LOCALE    imposta la codifica predefinita per i nuovi
                            database
   --no-locale               equivalente a --locale=C
   --pwfile=FILE             legge la password per il nuovo superuser dal file
   %s [OPTION]... [DATADIR]
   -?, --help                mostra questo aiuto, poi esce
   -A, --auth=METHOD         metodo di autenticazione predefinito per le
                            connessioni locali
   -E, --encoding=ENCODING   imposta la codifica predefinita per i nuovi
                            database
   -L DIRECTORY              dove trovare i file di input
   -T, --text-search-config=CFG
                            configurazione prefedinita per la ricerca testi
   -U, --username=NAME       nome del superuser del database
   -V, --version             mostra informazioni sulla versione, poi esce
   -W, --pwprompt            richiede la password per il nuovo superuser
   -X, --xlogdir=XLOGDIR     posizione della directory contenente i log
                            delle transazioni
   -d, --debug               genera molto output di debug
   -n, --noclean             non ripulire dopo gli errori
   -s, --show                mostra le impostazioni interne
  [-D, --pgdata=]DATADIR     posizione di questo database cluster
 %s inizializza un cluster di database PostgreSQL.

 %s: "%s" non è un nome di codifica per il server valido
 %s: non può essere eseguito da root
Effettuate il log in (usando per esempio "su") con l'utente
(non privilegiato) che controllerà il processo server.
 %s: impossibile accedere alla directory "%s": %s
 %s: impossibile aprire il file "%s": %s
 %s: impossibile cambiare i permessi di accesso della directory "%s": %s
 %s: impossibile creare la directory "%s": %s
 %s: impossibile creare il link simbolico "%s": %s
 %s: impossibile eseguire il comando "%s": %s
 %s: impossibile determinare una codifica adeguata per il locale %s
 %s: impossibile trovare una configurazione per la ricerca testo per il locale %s
 %s: impossibile determinare il nome utente: %s
 %s: impossibile acquisire informazioni sull'utente: %s
 %s: impossibile aprire il file "%s" per la lettura: %s
 %s: impossibile aprire il file "%s" per la scrittura: %s
 %s: impossibile leggere il file delle password "%s": %s
 %s: impossibile scrivere nel file "%s": %s
 %s: directory dati "%s" non rimossa per richiesta dell'utente
 %s: la directory "%s" esiste ma non è vuota
 %s: mancata corrispondenza di codifica
 %s: rimozione fallita dei contenuti dalla directory dati
 %s: rimozione fallita dei contenuti della directory contenente i log delle transazioni
 %s: rimozione fallita della directory dati
 %s: rimozione fallita della directory contenente i log delle transazioni
 %s: il file "%s" non esiste
 %s: il file "%s" non è un file regolare
 %s: il file di input "%s" non appartiene a PostgreSQL %s
Controllate l'installazione o specificate un percorso corretto con
l'opzione -L.
 %s: la posizione del file di input deve essere un path assoluto
 %s: nome locale non valido "%s"
 %s: il locale %s richiede la codifica non supportata %s
 %s: è obbligatorio specificare una password per abilitare l'autenticazione %s del superuser
 %s: nessuna directory dati specificati
E' necessario indicare la directory dove risiederanno i dati di questo
database. Fate questo invocando l'opzione -D o con la variabile globale
PGDATA.
 %s: memoria esaurita
 %s: il prompt della password ed un file contenente la password non
possono essere specificati contemporaneamente
 %s: rimozione dei contenuti dalla directory dati "%s"
 %s: rimozione dei contenuti della directory contenente i log delle transazioni "%s"
 %s: rimozione della directory dati "%s"
 %s: rimozione della directory contenente i log delle transazioni "%s"
 %s: i link simbolici non sono supportati su questa piattaforma %s: troppi parametri nella linea di comando (il primo è "%s")
 %s: directory contenente i log delle transazioni "%s" non rimossa per richiesta dell'utente
 %s: la directory dei log delle transazioni deve essere un path assoluto
 %s: metodo di autenticazione non riconosciuto "%s"
 %s: attenzione: la configurazione specificata per la ricerca testo "%s"
 non corrisponde al locale %s
 %s: attenzione: la configurazione adeguata per la ricerca testo per il locale %s non è conosciuta
 La codifica %s non è disponibile come codifica server-side.
Rieseguite %s con un locale diverso.
 Reinserirla:  Inserire la nuova password del superuser:  Se volete creare un nuovo sistema di database, cancellate o svuotate
la directory "%s" o eseguite %s
con un argomento diverso da "%s".
 Se volete salvare i log delle transazioni la', rimuovete
o svuotate la directory "%s".
 Le password non corrispondono. 
 Rieseguite %s con l'opzione -E .
 Esecuzione in modalità debug
 Esecuzione in modalità noclean. Gli errori non verrano puliti.
 Il database cluster sarà inizializzato con il locale %s.
 Il database cluster sarà inizializzato con i locale
  COLLATE:  %s
  CTYPE:    %s
  MESSAGES: %s
  MONETARY: %s
  NUMERIC:  %s
  TIME:     %s
 La codifica predefinita del database è stata impostata a %s.
 La configurazione predefinita di ricerca testo sarà impostata a "%s".
 La codifica selezionata (%s) e la codifica usata dal locale
(%s) non sono uguali. Questo causerebbe un funzionamento errato
in molte funzioni di elaborazione delle stringhe di caratteri.
Rieseguite %s e non specificate una codifica esplicitamente o
selezionate una combinazione corretta.
 I file di questo database apparterranno all'utente "%s".
Questo utente deve inoltre possedere il processo server.

 Il programma "postgres" è richiesto da %s ma non è stato trovato
nella stessa directory "%s".
Verificate l'installazione.
 Il programma "postgres" è stato trovato da "%s" ma non ha
la stessa versione "%s".
Verificate l'installazione.
 Questo potrebbe indica una corruzione dell'installazione oppure
avete indicato una directory errata con l'opzione -L.
 Provate "%s --help" per maggiori informazioni.
 Utilizzo:
 intercettato segnale
 il processo figlio è uscito con exit code %d il processo figlio è uscito con lo stato non riconosciuto %d il processo figlio è stato terminato dall'eccezione 0x%X il processo figlio è stato terminato dal segnale %d il processo figlio terminato dal segnale %s copia di template1 a postgres ...  copia di template1 a template0 ...  impossibile cambiare directory in "%s" impossibile trovare un "%s" da eseguire impossibile identificare la directory corrente: %s impossibile aprire la directory "%s": %s
 impossibile leggere il binario "%s" impossibile leggere la directory "%s": %s
 impossibile leggere il link simbolico "%s" impossibile rimuovere il file o la directory "%s": %s
 impossibile impostare la giunzione per "%s": %s
 impossibile rimuovere il file o la directory "%s": %s
 impossibile scrivere sul processo figlio: %s
 creazione dei file di configurazione ...  creazione delle conversioni ...  creazione dizionari ...  creazione della directory %s ...  creazione dello schema informazioni ...  creazione delle sottodirectory  ...  creazione delle viste di sistema ...  creazione del database template1 in in %s/base/1 ...  correggo i permessi sulla directory esistente %s ...  inizializzazione delle dipendenze ...  inizializzazione di pg_authid ...  binario non valido "%s" caricamento sul server del linguaggio PL/pgSQL ...  caricamento delle descrizioni degli oggetti di sistema ok
 memoria esaurita
 selezione del parametro max_connections predefinito ...  si sta selezionando lo shared_buffers predefinito ...  impostazione password ...  impostazione dei privilegi per gli oggetti incorporati ...  vacuum del database template1 ...  
��    �        �   
      �  K   �     �  f   �  
   b  >   m  >   �  =   �  -   )  C   W  A   �     �  #   �       (   5     ^  <   {  9   �  6   �  H   )  E   r  B   �  9   �  C   5  9   y  4   �  E   �  =   .  .   l  ;   �  E   �  :     5   X  7   �  9   �  7      4   8  L   m  J   �  5     2   ;  C   n  7   �  2   �  2     J   P  :   �  5   �  G     0   T  <   �  0   �  M   �  J   A  G   �  4   �  H   	  E   R  9   �  v   �  <   I  I   �  @   �  5     4   G  1   |  ;   �  5   �  6      3   W  4   �  =   �  8   �  8   7  8   p  2   �  9   �  6     >   M     �  /   �  <   �  #      #   )   ?   M   %   �   #   �      �   3   �   &   +!  5   R!  E   �!  I   �!  5   "  I   N"  5   �"  E   �"  F   #  4   [#  D   �#     �#  *   �#  8   $  6   W$  %   �$  (   �$  (   �$  8   %  #   ?%      c%     �%  8   �%  4   �%  $   &     7&  ,   W&  ,   �&  ;   �&  9   �&     ''     :'     O'     b'  *   �'  8   �'  ,   �'  8   (  #   J(  G   n(  4   �(     �(  )   )  7   2)     j)     x)  !   �)  +   �)     �)     �)     *     %*     C*     H*  
   e*     p*     �*     �*  '   �*  "   �*  2   +  7   9+     q+  &   z+     �+     �+     �+     �+  :   �+     �+     �+  �  �+  M   �-     %.  e   ?.  
   �.  L   �.  L   �.  K   J/  0   �/  D   �/  B   0     O0  ,   j0     �0  *   �0      �0  >    1  @   ?1  ;   �1  P   �1  P   2  I   ^2  >   �2  F   �2  5   .3  6   d3  X   �3  =   �3  .   24  <   a4  N   �4  :   �4  5   (5  7   ^5  ;   �5  D   �5  I   6  R   a6  U   �6  B   
7  ?   M7  W   �7  ;   �7  6   !8  6   X8  X   �8  :   �8  6   #9  G   Z9  4   �9  E   �9  4   :  E   R:  N   �:  ?   �:  >   ';  H   f;  B   �;  7   �;  v   *<  L   �<  Q   �<  K   @=  5   �=  5   �=  6   �=  ?   />  2   o>  6   �>  3   �>  ;   ?  L   I?  8   �?  8   �?  8   @  <   A@  ?   ~@  <   �@  N   �@     JA  0   VA  G   �A  !   �A  %   �A  B   B  %   ZB  $   �B  "   �B  6   �B  +   �B  E   +C  R   qC  X   �C  C   D  `   aD  E   �D  R   E  R   [E  S   �E  g   F     jF  0   �F  C   �F  D   �F  +   DG  .   pG  /   �G  7   �G  *   H  &   2H  %   YH  6   H  5   �H  (   �H  '   I  *   =I  7   hI  @   �I  @   �I     "J     8J     NJ     fJ  0   �J  B   �J  1   �J  C   ,K  -   pK  P   �K  >   �K     .L  /   ML  B   }L     �L     �L  5   �L  2   !M     TM  ,   gM  +   �M  *   �M     �M  $   �M  
   N       N     AN     `N  /   vN  (   �N  %   �N  )   �N     O  /   +O  
   [O     fO     hO     kO  F   }O     �O     �O        W   q   a   !   �   %      X      �   h       C   |          j   m   �   ^   :          c               s   �       d   V          ~   t      <       E   
   �       R   �   �   ,       )   e       K   �               D                     S       g      	   _       9   N   �           J   2   �       \   f      >   k   w   ?              /         $                     0           -   �       1   .       �   (   �   F               `           �   8   v   �      H       @           I   �       �   �       �       Z       &          y   �       ]              '   A       l   G   Y   �   z   {       �   �   M   �       *      =   U   r   p       T      Q          �   #   �      P   O   }   B   i   4   +      ;   u       �   n   b               7   o       L   �   "               x               �   �   �       �   �       [   5       6   3       
By default, a database with the same name as the current user is created.
 
Connection options:
 
If one of -d, -D, -r, -R, -s, -S, and ROLENAME is not specified, you will
be prompted interactively.
 
Options:
 
Read the description of the SQL command CLUSTER for details.
 
Read the description of the SQL command REINDEX for details.
 
Read the description of the SQL command VACUUM for details.
 
Report bugs to <pgsql-bugs@postgresql.org>.
       --lc-collate=LOCALE      LC_COLLATE setting for the database
       --lc-ctype=LOCALE        LC_CTYPE setting for the database
   %s [OPTION]... DBNAME
   %s [OPTION]... LANGNAME [DBNAME]
   %s [OPTION]... [DBNAME]
   %s [OPTION]... [DBNAME] [DESCRIPTION]
   %s [OPTION]... [ROLENAME]
   --help                          show this help, then exit
   --help                       show this help, then exit
   --help                    show this help, then exit
   --version                       output version information, then exit
   --version                    output version information, then exit
   --version                 output version information, then exit
   -D, --no-createdb         role cannot create databases
   -D, --tablespace=TABLESPACE  default tablespace for the database
   -E, --encoding=ENCODING      encoding for the database
   -E, --encrypted           encrypt stored password
   -F, --freeze                    freeze row transaction information
   -I, --no-inherit          role does not inherit privileges
   -L, --no-login            role cannot login
   -N, --unencrypted         do not encrypt stored password
   -O, --owner=OWNER            database user to own the new database
   -P, --pwprompt            assign a password to new role
   -R, --no-createrole       role cannot create roles
   -S, --no-superuser        role will not be superuser
   -T, --template=TEMPLATE      template database to copy
   -U, --username=USERNAME      user name to connect as
   -U, --username=USERNAME   user name to connect as
   -U, --username=USERNAME   user name to connect as (not the one to create)
   -U, --username=USERNAME   user name to connect as (not the one to drop)
   -W, --password               force password prompt
   -W, --password            force password prompt
   -Z, --analyze-only              only update optimizer statistics
   -a, --all                       vacuum all databases
   -a, --all                 cluster all databases
   -a, --all                 reindex all databases
   -c, --connection-limit=N  connection limit for role (default: no limit)
   -d, --createdb            role can create new databases
   -d, --dbname=DBNAME             database to vacuum
   -d, --dbname=DBNAME       database from which to remove the language
   -d, --dbname=DBNAME       database to cluster
   -d, --dbname=DBNAME       database to install language in
   -d, --dbname=DBNAME       database to reindex
   -e, --echo                      show the commands being sent to the server
   -e, --echo                   show the commands being sent to the server
   -e, --echo                show the commands being sent to the server
   -f, --full                      do full vacuuming
   -h, --host=HOSTNAME          database server host or socket directory
   -h, --host=HOSTNAME       database server host or socket directory
   -i, --index=INDEX         recreate specific index only
   -i, --inherit             role inherits privileges of roles it is a
                            member of (default)
   -i, --interactive         prompt before deleting anything
   -l, --list                show a list of currently installed languages
   -l, --locale=LOCALE          locale settings for the database
   -l, --login               role can login (default)
   -p, --port=PORT              database server port
   -p, --port=PORT           database server port
   -q, --quiet                     don't write any messages
   -q, --quiet               don't write any messages
   -r, --createrole          role can create new roles
   -s, --superuser           role will be superuser
   -s, --system              reindex system catalogs
   -t, --table='TABLE[(COLUMNS)]'  vacuum specific table only
   -t, --table=TABLE         cluster specific table only
   -t, --table=TABLE         reindex specific table only
   -v, --verbose                   write a lot of output
   -v, --verbose             write a lot of output
   -w, --no-password            never prompt for password
   -w, --no-password         never prompt for password
   -z, --analyze                   update optimizer statistics
 %s (%s/%s)  %s cleans and analyzes a PostgreSQL database.

 %s clusters all previously clustered tables in a database.

 %s creates a PostgreSQL database.

 %s creates a new PostgreSQL role.

 %s installs a procedural language into a PostgreSQL database.

 %s reindexes a PostgreSQL database.

 %s removes a PostgreSQL database.

 %s removes a PostgreSQL role.

 %s removes a procedural language from a database.

 %s: "%s" is not a valid encoding name
 %s: cannot cluster a specific table in all databases
 %s: cannot cluster all databases and a specific one at the same time
 %s: cannot reindex a specific index and system catalogs at the same time
 %s: cannot reindex a specific index in all databases
 %s: cannot reindex a specific table and system catalogs at the same time
 %s: cannot reindex a specific table in all databases
 %s: cannot reindex all databases and a specific one at the same time
 %s: cannot reindex all databases and system catalogs at the same time
 %s: cannot vacuum a specific table in all databases
 %s: cannot vacuum all databases and a specific one at the same time
 %s: clustering database "%s"
 %s: clustering of database "%s" failed: %s %s: clustering of table "%s" in database "%s" failed: %s %s: comment creation failed (database was created): %s %s: could not connect to database %s
 %s: could not connect to database %s: %s %s: could not get current user name: %s
 %s: could not obtain information about current user: %s
 %s: creation of new role failed: %s %s: database creation failed: %s %s: database removal failed: %s %s: language "%s" is already installed in database "%s"
 %s: language "%s" is not installed in database "%s"
 %s: language installation failed: %s %s: language removal failed: %s %s: missing required argument database name
 %s: missing required argument language name
 %s: only one of --locale and --lc-collate can be specified
 %s: only one of --locale and --lc-ctype can be specified
 %s: out of memory
 %s: query failed: %s %s: query was: %s
 %s: reindexing database "%s"
 %s: reindexing of database "%s" failed: %s %s: reindexing of index "%s" in database "%s" failed: %s %s: reindexing of system catalogs failed: %s %s: reindexing of table "%s" in database "%s" failed: %s %s: removal of role "%s" failed: %s %s: still %s functions declared in language "%s"; language not removed
 %s: too many command-line arguments (first is "%s")
 %s: vacuuming database "%s"
 %s: vacuuming of database "%s" failed: %s %s: vacuuming of table "%s" in database "%s" failed: %s Are you sure? Cancel request sent
 Could not send cancel request: %s Database "%s" will be permanently removed.
 Enter it again:  Enter name of role to add:  Enter name of role to drop:  Enter password for new role:  Name Password encryption failed.
 Password:  Passwords didn't match.
 Please answer "%s" or "%s".
 Procedural Languages Role "%s" will be permanently removed.
 Shall the new role be a superuser? Shall the new role be allowed to create databases? Shall the new role be allowed to create more new roles? Trusted? Try "%s --help" for more information.
 Usage:
 n no out of memory
 pg_strdup: cannot duplicate null pointer (internal error)
 y yes Project-Id-Version: PostgreSQL 8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-03-26 13:16+0000
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
Di base, un database con lo stesso nome dell'utente corrente verrà creato.
 
Opzioni di connessione:
 
Se uno tra -d, -D, -r, -R, -s, -S ed UTENTE non è specificato, ti sarà richesto interattivamente.
 
Opzioni:
 
Consulta la descrizione del comando SQL CLUSTER per maggiori informazioni.
 
Consulta la descrizione del comando SQL REINDEX per maggiori informazioni.
 
Consulta la descrizione del comando SQL VACUUM per maggiori informazioni.
 
Segnalare bachi a <pgsql-bugs@postgresql.org>.
       --lc-collate=LOCALE      LC_COLLATE settaggio per il database
       --lc-ctype=LOCALE        LC_CTYPE settaggio per il database
   %s [OPZIONE]... NOME_DB
   %s [OPZIONE]... NOME_LINGUAGGIO [NOME_DB]
   %s [OPZIONI]... [NOME_DB]
   %s [OPZIONE]... [NOME_DB] [DESCRIZIONE]
   %s [OPZIONI]... [NOME_UTENTE]
   --help                          mostra questi aiuti ed esci
   --help                       mostra questa guida, quindi esce
   --help                    mostra questo aiuto e poi esci
   --version                       mostra informazioni sulla versione e poi esci
   --version                       mostra informazioni sulla versione e poi esce
   --version                 mostra informazioni sulla versione, poi esci
   -D, --no-createdb         l'utente non può creare database
   -D, --tablespace=TABLESPACE  tablespace predefinito per il database
   -E, --encoding=ENCODING      codifica del database
   -E, --encrypted           cifra la password salvata
   -F, --freeze                    congela le informazioni per la transazione sulla riga
   -I, --no-inherit          role does not inherit privileges
   -L, --no-login            role cannot login
   -N, --unencrypted         non cifrare la password salvata
   -O, --owner=OWNER            utente database propietario del nuovo database
   -P, --pwprompt            assign a password to new role
   -R, --no-createrole       role cannot create roles
   -S, --no-superuser        role will not be superuser
   -T, --template=TEMPLATE      modello database da copiare
   -U, --username=USERNAME      nome utente da usare per connettersi
   -U, --username=UTENTE     nome utente da utilizzare per la connessione
   -U, --username=UTENTE     nome utente con cui collegarsi (non quello da creare)
   -U, --username=UTENTE     nome utente con cui collegarsi (non quello da eliminare)
   -W, --password               forza la richiesta di una password
   -W, --password            forza la richiesta di una password
   -z, --analyze-only              aggiorna soltanto le statistiche per l'ottimizzatore
   -a, --all                       pulisci tutti i database
   -a, --all                 riordina tutti i database
   -a, --all                 riordina tutti i database
   -c, --connection-limit=N  limite di connessione per un utente(default: nessun limite)
   -d, --createdb            l'utente può creare database
   -d, --dbname=NOME_DB             database da pulire
   -d, --dbname=NOME_DB      database dal quale eliminare il linguaggio
   -d, --dbname=NOME_DB       database da riordinare
   -d, --dbname=NOME_DB      database in cui installare il linguaggio
   -d, --dbname=NOME_DB       database da riordinare
   -e, --echo                      mostra i comandi inviati al server
   -e, --echo                   mostra i comandi che vengono inviati al server
   -e, --echo                mostra i comandi inviati al server
   -f, --full                      esegui una pulizia completa
   -h, --host=HOSTNAME          host server database o directory socket 
   -h, --host=NOME_HOST      indirizzo database o directory socket
   -I, --index=NOME         ricrea l'indice specificato
   -i, --inherit             role inherits privileges of roles it is a
                            member of (default)
   -i, --interactive         chiedi conferma prima di eseguire un operazione
   -l, --list                mostra la lista dei linguaggi attualmente installati
   -l, --locale=LOCALE          settaggi per la localizzazione del database
   -l, --login               role can login (default)
   -p, --port=PORT          porta del server database
   -p, --port=PORTA          porta del server database
   -q, --quiet                     non stampare alcun messaggio
   -q, --quiet               non stampare messaggi
   -r, --createrole          role can create new roles
   -s, --superuser           role will be superuser
   -s, --show                mostra le impostazioni interne
   -t, --table='TABELLA[(COLONNE)]'  pulisci solamente una tabella specifica
   -t, --table=TABELLA         riordina solo una tabella
   -t, --table=TABELLA         riordina solo una tabella
   -v, --verbose                   mostra molti messaggi
   -v, --verbose                   mostra un output completo
   -w, --no-password            non richiedere mai una password
   -w, --no-password         non richiedere mai una password
   -z, --analyze                   aggiorna le statistiche per l'ottimizzatore
 %s (%s/%s)  %s pulisce ed analizza un database PostgreSQL.

 %s riordina tutte le tabelle precedentemente riordinate nel database.

 %s crea un database PostgreSQL.

 %s crea un nuovo utente PostgreSQL.

 %s installa un linguaggio procedurale in un database PostgreSQL.

 %s riordina un database PostgreSQL.

 %s elimina un database PostgreSQL.

 %s elimina un utente PostgreSQL.

 %s elimina un linguaggio procedurale da un database.

 %s: "%s" non è un nome di codifica valido
 %s: impossibile riordinare una tabella specifica in tutti i database
 %s: impossibile riordinare tutti i database ed uno specifico nello stesso momento
 %s: impossibile riordinare un indice specifico ed i cataloghi di sistema stesso momento
 %s: impossibile riordinare un indice specifico in tutti i database
 %s: impossibile riordinare una specifica tabella ed i cataloghi di sistema nello stesso momento
 %s: impossibile riordinare una tabella specifica in tutti i database
 %s: impossibile riordinare tutti i database ed uno specifico nello stesso momento
 %s: impossibile riordinare tutti i database ed uno specifico nello stesso momento
 %s: impossibile effettuare la pulizia di una tabella specifica in tutti i database
 %s: impossibile effettuare la pulizia di tutti i database e di uno in particolare nello stesso momento
 %s: riordino del database "%s"
 %s: il riordino del database "%s" è fallito: %s %s: il riordino della tabella "%s" nel database "%s" è fallito: %s %s: creazione del commento fallita (il database è stato creato): %s %s: impossibile connettersi al database %s
 %s: impossibile connettersi al database %s: %s %s: impossibile determinare il nome utente: %s
 %s: impossibile acquisire informazioni sull'utente: %s
 %s: creazione del nuovo utente fallita: %s %s: creazione del database fallita: %s %s: eliminazione database fallita: %s %s: linguaggio "%s" già installato nel database "%s"
 %s: linguaggio "%s" non installato nel database "%s"
 %s: installazione linguaggio fallita: %s %s: eliminazione linguaggio fallita: %s %s: parametro mancante, nome del database
 %s: parametro mancante necessario: nome del linguaggio
 %s: solo uno di --locale e --lc-collate può essere specificato
 %s: solo uno dei  --locale e --lc-ctype può essere specificato
 %s: memoria esaurita
 %s: query fallita: %s %s: query eseguita: %s
 %s: riordino del database "%s"
 %s: il riordino del database "%s" è fallito: %s %s: il riordino di un indice "%s" nel database "%s" è fallito: %s %s: riordino dei cataloghi di sistema fallito: %s %s: il riordino della tabella "%s" nel database "%s" è fallito: %s %s: eliminazione dell'utente "%s" fallita: %s %s: ancora %s funzioni dichiarate nel linguaggio "%s"; linguaggio non eliminato
 %s: troppi parametri dalla riga di comando (il primo è "%s")
 %s: pulizia del database "%s"
 %s: la pulizia del database "%s" è fallito: %s %s: la pulizia della tabella "%s" nel database "%s" è fallito: %s Sei sicuro? Cancella la richiesta spedita
 Impossibile mandare la richiesta di cancellazione: %s Il database "%s" sarà eliminato definitivamente.
 Conferma password: Inserisci il nome dell'utente da aggiungere: Inserisci il nome dell'utente da eliminare: Inserisci la password per il nuovo utente: Nome crittazione della password fallita.
 Password:  Le password non corrispondono. 
 Prego rispondere "%s" o "%s".
 Linguaggi Procedurali L'utente "%s" sarà definitivamente eliminato.
 Il nuovo utente dev'essere un superuser? Il nuovo utente può creare database? Il nuovo utente può creare altri utenti? Affidabile? Prova "%s --help" per avere più informazioni.
 Utilizzo:
 n no memoria esaurita
 pg_strdup: impossibile duplicare un  puntatore nullo (errore interno)
 s si 
��    u      �  �   l      �	  ~   �	  -   `
  +   �
  0   �
  7   �
  g   #     �  4   �  s   �  .   T  G   �  4   �  )      w   *  4   �     �  @   �  =   +  !   i     �  ,   �  1   �  *     -   3  -   a  1   �  '   �  &   �  +     "   <      _     �  #   �     �  )   �  =   �  	   2     <  &   X  <     !   �  	   �  -   �  9     +   P  "   |     �  ,   �     �       *   %  "   P  '   s     �     �  !   �     �  !        '      <  3   ]  /   �  '   �  ,   �  /     *   F  T   q  '   �     �     	     %     7     N  -   h  ,   �  ,   �  5   �     &  )   B  ?   l  8   �  �   �  0   |  5   �     �  A   �  L   :     �  6   �  '   �  #   �       (   %  4   N  )   �     �  /   �     �        $   4     Y  "   q  ,   �     �     �  '   �     !     @  $   [  0   �     �  8   �     	     '  &   E      l    �  �   �  0   !   .   R   @   �   A   �   r   !  "   w!  5   �!  �   �!  5   R"  X   �"  9   �"  0   #  �   L#  7   �#     $  K   #$  :   o$  (   �$  2   �$  <   %  7   C%  0   {%  3   �%  3   �%  7   &  -   L&  ,   z&  1   �&  #   �&  !   �&     '  )   >'     h'  /   q'  _   �'  	   (     (  /   ((  G   X(  %   �(     �(  /   �(  C   )  6   G)  +   ~)     �)  2   �)      �)     *  3   8*  4   l*  0   �*     �*     �*  %   +     ++  !   D+     f+  ,   y+  C   �+  N   �+  9   9,  7   s,  4   �,  D   �,  ]   %-  ,   �-  %   �-  "   �-     �-     .     %.  3   =.  2   q.  2   �.  ?   �.     /  /   0/  F   `/  =   �/  �   �/  ?   �0  ?   �0     1  E   $1  U   j1     �1  ?   �1  +   2  '   =2     e2  /   x2  A   �2  )   �2     3  =   23  !   p3  )   �3  #   �3     �3  '   �3  =   $4     b4  /   |4  *   �4  $   �4     �4  ;   5  8   V5  %   �5  D   �5  !   �5  )   6  .   F6  2   u6         =   p       9   P   *   V          L      \              e   `   5       7          $   f          	                    
   k                     b           c   a   ;   !       j   ]   i   s   1   6      M   _   h      ^   Z      ?                 d   /   U   l   ,      [               t          N   '   K   .   G   F   g      I   E          #   %   n   W          Q   :   +   Y       X   2       &           B               J   m      q   H       (             3   u       8   D   <   A       T   4       S   R   O   -       )   @       o   >   "   C                    0             r    
If no output file is specified, the name is formed by adding .c to the
input file name, after stripping off .pgc if present.
 
Report bugs to <pgsql-bugs@postgresql.org>.
   --help         show this help, then exit
   --regression   run in regression testing mode
   --version      output version information, then exit
   -C MODE        set compatibility mode; MODE can be one of
                 "INFORMIX", "INFORMIX_SE"
   -D SYMBOL      define SYMBOL
   -I DIRECTORY   search DIRECTORY for include files
   -c             automatically generate C code from embedded SQL code;
                 this affects EXEC SQL TYPE
   -d             generate parser debug output
   -h             parse a header file, this option includes option "-c"
   -i             parse system include files as well
   -o OUTFILE     write result to OUTFILE
   -r OPTION      specify run-time behavior; OPTION can be:
                 "no_indicator", "prepare", "questionmarks"
   -t             turn on autocommit of transactions
 %s at or near "%s" %s is the PostgreSQL embedded SQL preprocessor for C programs.

 %s, the PostgreSQL embedded C preprocessor, version %d.%d.%d
 %s: could not open file "%s": %s
 %s: no input files specified
 %s: parser debug support (-d) not available
 AT option not allowed in CLOSE DATABASE statement AT option not allowed in CONNECT statement AT option not allowed in DEALLOCATE statement AT option not allowed in DISCONNECT statement AT option not allowed in SET CONNECTION statement AT option not allowed in TYPE statement AT option not allowed in VAR statement AT option not allowed in WHENEVER statement COPY FROM STDIN is not implemented COPY FROM STDOUT is not possible COPY TO STDIN is not possible CREATE TABLE AS cannot specify INTO ERROR:  EXEC SQL INCLUDE ... search starts here:
 Error: include path "%s/%s" is too long on line %d, skipping
 Options:
 SHOW ALL is not implemented Try "%s --help" for more information.
 Unix-domain sockets only work on "localhost" but not on "%s" Usage:
  %s [OPTION]... FILE...

 WARNING:  arrays of indicators are not allowed on input constraint declared INITIALLY DEFERRED must be DEFERRABLE could not open include file "%s" on line %d could not remove output file "%s"
 cursor "%s" does not exist cursor "%s" has been declared but not opened cursor "%s" is already defined descriptor "%s" does not exist descriptor header item "%d" does not exist descriptor item "%s" cannot be set descriptor item "%s" is not implemented end of search list
 expected "://", found "%s" expected "@" or "://", found "%s" expected "@", found "%s" expected "postgresql", found "%s" incomplete statement incorrectly formed variable "%s" indicator for array/pointer has to be array/pointer indicator for simple data type has to be simple indicator for struct has to be a struct indicator variable must have an integer type initializer not allowed in EXEC SQL VAR command initializer not allowed in type definition internal error: unreachable state; please report this to <pgsql-bugs@postgresql.org> interval specification not allowed here invalid bit string literal invalid connection type: %s invalid data type key_member is always 0 missing "EXEC SQL ENDIF;" missing identifier in EXEC SQL DEFINE command missing identifier in EXEC SQL IFDEF command missing identifier in EXEC SQL UNDEF command missing matching "EXEC SQL IFDEF" / "EXEC SQL IFNDEF" more than one EXEC SQL ELSE multidimensional arrays are not supported multidimensional arrays for simple data types are not supported multidimensional arrays for structures are not supported multilevel pointers (more than 2 levels) are not supported; found %d level multilevel pointers (more than 2 levels) are not supported; found %d levels nested arrays are not supported (except strings) no longer supported LIMIT #,# syntax passed to server nullable is always 1 only data types numeric and decimal have precision/scale argument only protocols "tcp" and "unix" and database type "postgresql" are supported out of memory pointer to pointer is not supported for this data type pointers to varchar are not implemented subquery in FROM must have an alias syntax error syntax error in EXEC SQL INCLUDE command too many levels in nested structure/union definition too many nested EXEC SQL IFDEF conditions type "%s" is already defined type name "string" is reserved in Informix mode unmatched EXEC SQL ENDIF unrecognized data type name "%s" unrecognized descriptor item code %d unrecognized token "%s" unrecognized variable type code %d unsupported feature will be passed to server unterminated /* comment unterminated bit string literal unterminated hexadecimal string literal unterminated quoted identifier unterminated quoted string using unsupported DESCRIBE statement variable "%s" is neither a structure nor a union variable "%s" is not a pointer variable "%s" is not a pointer to a structure or a union variable "%s" is not an array variable "%s" is not declared variable "%s" must have a numeric type zero-length delimited identifier Project-Id-Version: PostgreSQL 8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-03-26 13:23+0000
PO-Revision-Date: 2010-03-27 12:44:19+0100
Last-Translator: Gabriele Bartolini <gabriele.bartolini@2ndquadrant.it>
Language-Team: Gruppo traduzioni ITPUG <traduzioni@itpug.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=n != 1;
X-Poedit-Language: Italian
X-Poedit-Country: ITALY
X-Poedit-SourceCharset: utf-8
 
Se non viene specificato nessun file di output, il nome è composto aggiungendo .c
la nome del file di input, dopo aver tolto .pgc se presente.
 
Segnalare bachi a <pgsql-bugs@postgresql.org>.
   --help         mostra questo help, poi esce
   --regression   viene eseguito in modalità regression testing
   --version      mostra le informazioni sulla versione, poi esce
   -C MODE        setta il compatibility mode; MODE può essere uno tra
                 "INFORMIX", "INFORMIX_SE"
   -D SYMBOL      definisce SYMBOL
   -I DIRECTORY   cerca gli include file in DIRECTORY
   -c             genera automaticamente il codice C dal codice SQL embedded;
                 questo ha effetto su EXEC SQL TYPE
   -d             genera l'output di debug del parser
   -h             fa il parsing di un header file, questa opzione include l'opzione "-c"
   -i             fa il parsing anche dei file di sistema
   -o OUTFILE     scrive il risultato in OUTFILE
   -r OPTION      specifica il comportamento run-time; OPTION può essere:
                 "no_indicator", "prepare", "questionmarks"
   -t             attiva l'autocommit nelle transazioni
 %s presso o vicino "%s" %s è il PostgreSQL embedded SQL preprocessor for programmi scritti in C.

 %s, PostgreSQL embedded C preprocessor, versione %d.%d.%d
 %s: impossibile aprire il file "%s": %s
 %s: non è stato specificato nessun file di input
 %s: il supporto al debug del parser (-d) non è disponibile
 l'opzione AT non è permessa nel comando CLOSE DATABASE l'opzione AT non è permessa nel comando CONNECT l'opzione AT non è permessa nel comando DEALLOCATE l'opzione AT non è permessa nel comando DISCONNECT l'opzione AT non è permessa nel comando SET CONNECTION l'opzione AT non è permessa nel comando TYPE l'opzione AT non è permessa nel comando VAR l'opzione AT non è permessa nel comando WHENEVER COPY FROM STDIN non è implementato COPY FROM STDOUT non è possibile COPY TO STDIN non è possibile CREATE TABLE AS non può specificare INTO ERRORE:  EXEC SQL INCLUDE ... la ricerca inizia da qui:
 Errore: il percorso della include "%s/%s" è troppo lungo alla linea %d, perciò viene saltato
 Opzioni:
 SHOW ALL non è implementato Prova "%s --help" per avere più informazioni.
 gli Unix-domain sockets funzionano solo con "localhost" ma non con "%s" Utilizzo:
  %s [OPZIONE]... FILE...

 ATTENZIONE:  un array di indicatori non è permesso in input la condizione dichiarata INITIALLY DEFERRED  deve essere DEFERRABLE non posso aprire il file di include "%s" alla linea %d non posso rimuovere il file di output "%s"
 il cursore "%s" non esiste il cursore "%s" è stato dichiarato, ma non aperto il cursore "%s" è già definito il descrittore "%s" non esiste la voce "%d" dell'header del descrittore non esiste la voce "%s" del descrittore non può essere settata la voce "%s" del descrittore non è implementata fine della search list
 atteso "://", trovato "%s" atteso "@" oppure "://", trovato "%s" atteso "@", trovato "%s" atteso "postgresql", trovato "%s" comando incompleto variabile "%s" composta in maniera scorretta un indicatore per un array/puntatore deve essere un array/puntatore un indicatore per tipi dato semplici deve essere formato da tipi dato semplici un indicatore per una struttura deve essere una struttura il tipo di variabile di un indicator debe essere intero initializer non è permesso nel comando EXEC SQL VAR l'inizializzatore non è permesso nella definizione del tipo di dato errore interno: stato non raggiungibile, si prega di segnalarlo a <pgsql-bugs@postgresql.org> specificazione d'intervallo non permessa qui bit nella stringa literal non valido  tipo di connessione non valido: %s tipo dato non valido key_member è sempre 0 manca "EXEC SQL ENDIF;" identificatore mancante nel comando EXEC SQL DEFINE identificatore mancante nel comando EXEC SQL IFDEF identificatore mancante nel comando EXEC SQL UNDEF mancata corrispondenza fra "EXEC SQL IFDEF" / "EXEC SQL IFNDEF" più di un EXEC SQL ELSE gli array multidimensionali non sono supportati gli array multidimensionali per tipi dato semplici non sono supportati gli array multidimensionali per strutture non sono supportati puntatori a più livelli (più di 2 livelli) non sono supportati; trovato %d livello puntatori a più livelli (più di 2 livelli) non sono supportati; trovati %d livelli array annidati non sono supportati (tranne che per le stringhe) la sintassi LIMIT #,# passata al server, non è più supportata nullable è sempre 1 solo i dati di tipo numeric e decimal hanno argomento precision/scale soltanto i protocolli "tcp" e "unix" ed il tipo database "postgresql" sono supportati memoria esaurita puntatore a puntatore non è supportato per questo tipo di dato i puntatori a varchar non sono implementati la subquery in FROM deve avere un alias errore di sintassi errore di sintassi nel comando EXEC SQL INCLUDE troppi livelli nidificati nella definizione della struttura/union troppe condizioni EXEC SQL IFDEF annidate il tipo "%s" è già definito il nome di tipo "string" è riservato alla modalità Informix EXEC SQL ENDIF non corrispondente tipo di dato chiatato "%s" è sconosciuto descittore di codice %d sconosciuto token "%s" non riconosciuto tipo di variabile sconosciuto codice %d al server è stata richiesta una funzionalità non supportata commento /* non terminato  bit di chiusura nella stringa literal mancante stringa esadecimale literal non terminata  identificatore quotato non terminato stringa quotata non terminata si sta utilizzando la dichiarazione non supportata DESCRIBE la variabile "%s" non è nè una struttura nè una union la variabile "%s" non è un puntatore la variabile "%s" non è un puntatore ad una strutura o ad una union la variabile "%s" non è un array la variabile "%s" non è stata dichiarata la variabile "%s" deve essere di tipo numerico identificatore di delimitazione di dimensione-zero 
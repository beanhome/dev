��    K      t  e   �      `  9   a  -   �  ,   �  8   �  3   /  0   c  *   �  N   �  /     N   >     �  *   �  +   �     	  !    	  +   B	  )   n	  #   �	  &   �	  -   �	  !   
  !   3
  +   U
  "   �
  (   �
     �
  S   �
  #   6  #   Z  #   ~  #   �  #   �  #   �  \     +   k  0   �      �  @   �  D   *  &   o  -   �     �  )   �  )   �  )   (  )   R  )   |  )   �  )   �  )   �     $  V   A  )   �  )   �  )   �  ,     )   C  )   m  )   �  )   �  )   �  )     )   ?  )   i  	   �  �   �     >  &   U  !   |  )   �  -   �     �       )   "  Z  L  M   �  1   �  2   '  :   Z  5   �  3   �  (   �  G   (  2   p  L   �  !   �  -     -   @     n  !   �  %   �  (   �  %   �  &   #  .   J  "   y  !   �  *   �  #   �  )        7  U   J  &   �  &   �  &   �  &     &   <  &   c  W   �  .   �  2        D  H   c  N   �  )   �  0   %     V  )   e  )   �  )   �  )   �  )     )   7  )   a  )   �     �  X   �  -   +  -   Y  )   �  ,   �  )   �  -     ,   6  )   c  )   �  )   �  )   �  )      	   5   �   ?   $   �   ,   !  *   A!  )   l!  1   �!     �!     �!  )   �!     A       F                 ;   K      5   :   (   7      H              &       ,              $       C      .      2      E   >       '             D   J         %             	   I   !                     <          #   )          9   @      G   8                    0       1   -   *           ?          =   
      6      +       4      3   B       "              /    
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
 Guessed pg_control values:

 If you are sure the data directory path is correct, execute
  touch %s
and try again.
 Latest checkpoint's NextMultiOffset:  %u
 Latest checkpoint's NextMultiXactId:  %u
 Latest checkpoint's NextOID:          %u
 Latest checkpoint's NextXID:          %u/%u
 Latest checkpoint's TimeLineID:       %u
 Latest checkpoint's oldestActiveXID:  %u
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
 floating-point numbers pg_control values:

 pg_control version number:            %u
 Project-Id-Version: PostgreSQL 9.0
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-07-02 05:22+0000
PO-Revision-Date: 2010-07-02 20:32-0400
Last-Translator: Peter Eisentraut <peter_e@gmx.net>
Language-Team: Swedish <sv@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=ISO-8859-1
Content-Transfer-Encoding: 8bit
 
Om dessa v�rden verkar acceptable, anv�nd -f f�r
att forcera �terst�llande.
 
Reportera fel till <pgsql-bugs@postgresql.org>.
   --help          visa denna hj�lp, avsluta sedan
   --version       visa versionsinformation, avsluta sedan
   -O OFFSET       s�tt n�sta multitransaktionsoffset
   -x XIDEPOCH     s�tt n�sta transaktions-ID-epoch
   -f              forcera �terst�llande
   -l TLI,FILID,SEG    ange minsta WAL-startposition f�r ny transaktion
   -m XID          s�tt n�sta multitransaktions-ID
   -n              ingen updatering, visa bara kontrollv�rden (f�r testning)
   -o OID          s�tt n�sta OID
   -x XID          s�tt n�sta transaktions-ID
 %s �terst�ller PostgreSQL transaktionslogg.

 %s: OID (-o) f�r inte vara 0
 %s: kan inte exekveras av "root"
 %s: kunde byta katalog till "%s": %s
 %s: kunde inte skapa pg_control-fil: %s
 %s: kunde inte radera filen "%s": %s
 %s: kunde inte �ppna katalog "%s": %s
 %s: kunde inte �ppna fil "%s" f�r l�sning: %s
 %s: kunde inte �ppna fil "%s": %s
 %s: kunde inte l�sa fil "%s": %s
 %s: kunde inte l�sa fr�n katalog "%s": %s
 %s: kunde inte skriva fil "%s": %s
 %s: kunde inte skriva pg_control-fil: %s
 %s: fsync fel: %s
 %s: internt fel -- sizeof(ControlFileData) �r f�r stor ... r�tt till PG_CONTROL_SIZE
 %s: ogiltigt argument till flaggan -O
 %s: felaktigt argument till flagga -e
 %s: ogiltigt argument till flaggan -l
 %s: ogiltigt argument till flaggan -m
 %s: ogiltigt argument till flaggan -o
 %s: ogiltigt argument till flaggan -x
 %s: l�sfil "%s" existerar
K�r servern redan? Om inte, radera l�sfilen och f�rs�k igen.
 %s: multitransaktions-ID (-m) f�r inte vara 0
 %s: multitransaktionsoffset (-O) f�r inte vara -1
 %s: ingen datakatalog angiven
 %s: pg_control existerar men har ogiltig CRC; forts�tt med f�rsiktighet
 %s: pg_control existerar men �r trasig eller har ok�nd version; ignorerar den
 %s: transaktions-ID (-x) f�r inte vara 0
 %s: transaktions-ID epoch (-e) f�r inte vara -1
 64-bits heltal Block per segment i stor relation:    %u
 Bytes per WAL-segment:                %u
 Katalogversionsnummer:                %u
 Databasens blockstorlek:              %u
 Databasens systemidentifierare:       %s
 Lagringstyp f�r datum/tid:            %s
 F�rsta loggfil efter nollst�llning:   %u
 F�rsta loggfilsegment efter nollst.:  %u
 Gissade pg_control-v�rden:

 Om du �r s�ker p� att datakatalogs�kv�gen �r korrekt s� g�r
  touch %s
och f�rs�k igen.
 Senaste kontrollpunktens NextMultiOffset: %u
 Senaste kontrollpunktens NextMultiXactId: %u
 Senaste kontrollpunktens NextOID:     %u
 Senaste kontrollpunktens NextXID:     %u/%u
 Senaste kontrollpunktens TimeLineID:  %u
 Senaste kontrollpunktens oldestActiveXID: %u
 Senaste kontrollpunktens oldestXID:s DB: %u
 Senaste kontrollpunktens oldestXID:   %u
 Maximalt antal kolumner i index:      %u
 Maximal data-alignment:               %u
 Maximal l�ngd p� identifierare:       %u
 Maximal storlek p� TOAST-bit:         %u
 Flaggor:
 Databasservern st�ngdes inte ner korrekt. Att �terst�lla
transaktionsloggen kan medf�ra att data f�rloras.
Om du vill forts�tta �nd�, anv�nd -f f�r att forcera
�terst�llande.
 �terst�llande fr�n transaktionslogg
 F�rs�k med "%s --help" f�r mer information.
 Anv�ndning:
  %s [FLAGGA]... DATAKATALOG

 WAL-blockstorlek:                     %u
 Du m�ste k�ra %s som PostgreSQLs superanv�ndare.
 flyttalsnummer pg_control-v�rden:

 pg_control versionsnummer:            %u
 
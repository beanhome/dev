��    :      �  O   �      �  X   �  C   R  -   �  !   �      �       ,     )   D  )   n  )   �  )   �  )   �  )     )   @  )   j  )   �  )   �  )   �  )     )   <  ,   f  )   �  )   �  )   �  ,   	  ,   >	  )   k	  )   �	  )   �	  )   �	  )   
  )   =
  )   g
  )   �
  ,   �
  ,   �
  ,     )   B  &   l  �   �  )     �   I               -     6     M     a     s  )   �  )   �  	   �     �     �               (  Z  ?  Y   �  I   �  4   >  (   s  $   �     �  0   �  .     -   3  -   a  -   �  -   �  -   �  -     /   G  -   w  -   �  -   �  .     .   0  0   _  -   �  -   �  -   �  0     0   K  -   |  -   �  -   �  -     -   4  -   b  .   �  0   �  0   �  0   !  5   R  -   �  8   �  �   �  /   �  �   �  S  �     �                 &   <     c  .   w  -   �     �  )   �               '     B        /                     8           .   4            %               :                              #      *      5              $      (   )         "   '      1       !           7   ,      0   2   
          9                              	   &   -       6                3   +    
If no data directory (DATADIR) is specified, the environment variable PGDATA
is used.

 %s displays control information of a PostgreSQL database cluster.

 %s: could not open file "%s" for reading: %s
 %s: could not read file "%s": %s
 %s: no data directory specified
 64-bit integers Backup start location:                %X/%X
 Blocks per segment of large relation: %u
 Bytes per WAL segment:                %u
 Catalog version number:               %u
 Current max_connections setting:      %d
 Current max_locks_per_xact setting:   %d
 Current max_prepared_xacts setting:   %d
 Current wal_level setting:            %s
 Database block size:                  %u
 Database cluster state:               %s
 Database system identifier:           %s
 Date/time type storage:               %s
 Float4 argument passing:              %s
 Float8 argument passing:              %s
 Latest checkpoint location:           %X/%X
 Latest checkpoint's NextMultiOffset:  %u
 Latest checkpoint's NextMultiXactId:  %u
 Latest checkpoint's NextOID:          %u
 Latest checkpoint's NextXID:          %u/%u
 Latest checkpoint's REDO location:    %X/%X
 Latest checkpoint's TimeLineID:       %u
 Latest checkpoint's oldestActiveXID:  %u
 Latest checkpoint's oldestXID's DB:   %u
 Latest checkpoint's oldestXID:        %u
 Maximum columns in an index:          %u
 Maximum data alignment:               %u
 Maximum length of identifiers:        %u
 Maximum size of a TOAST chunk:        %u
 Minimum recovery ending location:     %X/%X
 Prior checkpoint location:            %X/%X
 Report bugs to <pgsql-bugs@postgresql.org>.
 Time of latest checkpoint:            %s
 Try "%s --help" for more information.
 Usage:
  %s [OPTION] [DATADIR]

Options:
  --help         show this help, then exit
  --version      output version information, then exit
 WAL block size:                       %u
 WARNING: Calculated CRC checksum does not match value stored in file.
Either the file is corrupt, or it has a different layout than this program
is expecting.  The results below are untrustworthy.

 WARNING: possible byte ordering mismatch
The byte ordering used to store the pg_control file might not match the one
used by this program.  In that case the results below would be incorrect, and
the PostgreSQL installation would be incompatible with this data directory.
 by reference by value floating-point numbers in archive recovery in crash recovery in production pg_control last modified:             %s
 pg_control version number:            %u
 shut down shut down in recovery shutting down starting up unrecognized status code unrecognized wal_level Project-Id-Version: PostgreSQL 9.0
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-06-03 17:16+0000
PO-Revision-Date: 2010-06-03 21:41+0300
Last-Translator: Peter Eisentraut <peter_e@gmx.net>
Language-Team: German <peter_e@gmx.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
 
Wenn kein Datenverzeichnis angegeben ist, wird die Umgebungsvariable
PGDATA verwendet.

 %s zeigt Kontrollinformationen über einen PostgreSQL-Datenbankcluster.

 %s: konnte Datei »%s« nicht zum Lesen öffnen: %s
 %s: konnte Datei »%s« nicht lesen: %s
 %s: kein Datenverzeichnis angegeben
 64-Bit-Ganzzahlen Backup-Startpunkt:                        %X/%X
 Blöcke pro Segment:                       %u
 Bytes pro WAL-Segment:                    %u
 Katalogversionsnummer:                    %u
 Aktuelle max_connections-Einstellung:     %d
 Aktuelle max_locks_per_xact-Einstellung:  %d
 Aktuelle max_prepared_xacts-Einstellung:  %d
 Aktuelle wal_level-Einstellung:           %s
 Datenbankblockgröße:                      %u
 Datenbank-Cluster-Status:                 %s
 Datenbanksystemidentifikation:            %s
 Speicherung von Datum/Zeit-Typen:         %s
 Übergabe von Float4-Argumenten:           %s
 Übergabe von Float8-Argumenten:           %s
 Position des letzten Checkpoints:         %X/%X
 NextMultiOffset des letzten Checkpoints:  %u
 NextMultiXactId des letzten Checkpoints:  %u
 NextOID des letzten Checkpoints:          %u
 NextXID des letzten Checkpoints:          %u/%u
 REDO-Position des letzten Checkpoints:    %X/%X
 TimeLineID des letzten Checkpoints:       %u
 oldestActiveXID des letzten Checkpoints:  %u
 DB der oldestXID des letzten Checkpoints: %u
 oldestXID des letzten Checkpoints:        %u
 Maximale Spalten in einem Index:          %u
 Maximale Datenausrichtung (Alignment):    %u
 Maximale Bezeichnerlänge:                 %u
 Maximale Größe eines Stücks TOAST:        %u
 Minimaler Wiederherstellungsendpunkt:     %X/%X
 Position des vorletzten Checkpoints:      %X/%X
 Berichten Sie Fehler an <pgsql-bugs@postgresql.org>.
 Zeit des letzten Checkpoints:             %s
 Versuchen Sie »%s --help« für weitere Informationen.
 Aufruf:
  %s [OPTION] [DATENVERZEICHNIS]

Optionen:
  --help         diese Hilfe anzeigen, dann beenden
  --version      Versionsinformationen anzeigen, dann beenden
 WAL-Blockgröße:                           %u
 WARNUNG: Berechnete CRC-Checksumme stimmt nicht mit dem Wert in der Datei
überein. Entweder ist die Datei kaputt oder sie hat ein anderes Layout
als von diesem Program erwartet. Die Ergebnisse unten sind nicht
verlässlich.

 WARNUNG: möglicherweise falsche Byte-Reihenfolge
Die Byte-Reihenfolge, die zur Speicherung der Datei pg_control verwendet wurde,
stimmt möglicherweise nicht mit der von diesem Programm verwendeten überein. In
diesem Fall wären die Ergebnisse unten falsch und die PostgreSQL-Installation
wäre inkompatibel mit diesem Datenverzeichnis.
 Referenz Wert Gleitkommazahlen bei der Archivwiederherstellung bei der Wiederherstellung nach Absturz im Produktionsmodus pg_control zuletzt geändert:              %s
 pg_control-Versionsnummer:                %u
 heruntergefahren in der Wiederherstellung heruntergefahren fährt herunter startet nicht erkannter Statuscode unbekanntes wal_level 
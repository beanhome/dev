��    n      �  �   �      P	      Q	     r	  &   �	     �	     �	  -   �	     
  =   .
     l
  |   �
       a   &  K   �     �  A   �  !   1  3   S  ?   �  ?   �  H     D   P  E   �  ?   �  >     9   Z  B   �  <   �  �     0   �  F   �  >     8   P  2   �  O   �  7        D     K  �   T  !   �  C     y   K  C   �  D   	  >   N  A   �  *   �  /   �  %   *  /   P  #   �     �  3   �  0   �  ,   '  .   T  3   �  -   �  0   �  5     *   L  "   w  $   �  J   �     
     &  3   =  0   q     �     �  !   �  $   �        -   <  4   j  %   �  $   �  "   �  F     F   T     �  7   �  )   �  k     `   }  %   �  &        +  d   3     �  &   �  0   �  .     )   >  )   h  "   �      �  (   �     �  !        <     T     h     ~     �     �     �     �  "   �     �  d    %        �  1   �  $   �  '      6   ?      v   @   �      �   �   �   !   m!  d   �!  N   �!     C"  C   `"  !   �"  <   �"  F   #  .   J#  C   y#  N   �#  D   $  E   Q$  C   �$  8   �$  x   %  F   �%  �   �%  7   U&  G   �&  :   �&  ?   '  4   P'  g   �'  F   �'     4(     =(  �   F(  %   )  L   B)  �   �)  H   :*  J   �*  Y   �*  G   (+  -   p+  3   �+  .   �+  7   ,  (   9,  $   b,  <   �,  ;   �,  1    -  4   2-  <   g-  1   �-  7   �-  >   .  8   M.  )   �.  +   �.  S   �.     0/     O/  @   g/  4   �/     �/  !   �/     0  '   80  %   `0  +   �0  <   �0  '   �0  &   1  "   >1  _   a1  W   �1     2  M   -2  1   {2  �   �2  z   43  6   �3  8   �3     4  ~   (4     �4  #   �4  1   �4  -   5  '   K5  '   s5  +   �5  (   �5  0   �5  '   !6  2   I6     |6     �6     �6     �6     �6     �6     7     !7  '   97     a7               6      7         =          [           )      :   /   $          g           (   a   T   Y   M   >   _   h      D   F   '       R   J          .   &              l      8       U   ;                N   I   C   b   5      E               +   e   \   L   	   V          f          
   H   B       "   #   !   -   ?      4       m               W   j      X               ]   ^          2   %      A   3       0       `   Q          P   n   9   ,   @           d   k                               S   O   i   G   Z           c   1       *   K   <           
Allowed signal names for kill:
 
Common options:
 
Options for register and unregister:
 
Options for start or restart:
 
Options for stop or restart:
 
Report bugs to <pgsql-bugs@postgresql.org>.
 
Shutdown modes are:
   %s init[db]               [-D DATADIR] [-s] [-o "OPTIONS"]
   %s kill    SIGNALNAME PID
   %s register   [-N SERVICENAME] [-U USERNAME] [-P PASSWORD] [-D DATADIR]
                    [-w] [-t SECS] [-o "OPTIONS"]
   %s reload  [-D DATADIR] [-s]
   %s restart [-w] [-t SECS] [-D DATADIR] [-s] [-m SHUTDOWN-MODE]
                 [-o "OPTIONS"]
   %s start   [-w] [-t SECS] [-D DATADIR] [-s] [-l FILENAME] [-o "OPTIONS"]
   %s status  [-D DATADIR]
   %s stop    [-W] [-t SECS] [-D DATADIR] [-s] [-m SHUTDOWN-MODE]
   %s unregister [-N SERVICENAME]
   --help                 show this help, then exit
   --version              output version information, then exit
   -D, --pgdata DATADIR   location of the database storage area
   -N SERVICENAME  service name with which to register PostgreSQL server
   -P PASSWORD     password of account to register PostgreSQL server
   -U USERNAME     user name of account to register PostgreSQL server
   -W                     do not wait until operation completes
   -c, --core-files       allow postgres to produce core files
   -c, --core-files       not applicable on this platform
   -l, --log FILENAME     write (or append) server log to FILENAME
   -m SHUTDOWN-MODE   can be "smart", "fast", or "immediate"
   -o OPTIONS             command line options to pass to postgres
                         (PostgreSQL server executable) or initdb
   -p PATH-TO-POSTGRES    normally not necessary
   -s, --silent           only print errors, no informational messages
   -t SECS                seconds to wait when using -w option
   -w                     wait until operation completes
   fast        quit directly, with proper shutdown
   immediate   quit without complete shutdown; will lead to recovery on restart
   smart       quit after all clients have disconnected
  done
  failed
 %s is a utility to start, stop, restart, reload configuration files,
report the status of a PostgreSQL server, or signal a PostgreSQL process.

 %s: PID file "%s" does not exist
 %s: another server might be running; trying to start server anyway
 %s: cannot be run as root
Please log in (using, e.g., "su") as the (unprivileged) user that will
own the server process.
 %s: cannot reload server; single-user server is running (PID: %ld)
 %s: cannot restart server; single-user server is running (PID: %ld)
 %s: cannot set core file size limit; disallowed by hard limit
 %s: cannot stop server; single-user server is running (PID: %ld)
 %s: could not find own program executable
 %s: could not find postgres program executable
 %s: could not open PID file "%s": %s
 %s: could not open service "%s": error code %d
 %s: could not open service manager
 %s: could not read file "%s"
 %s: could not register service "%s": error code %d
 %s: could not send reload signal (PID: %ld): %s
 %s: could not send signal %d (PID: %ld): %s
 %s: could not send stop signal (PID: %ld): %s
 %s: could not start server
Examine the log output.
 %s: could not start server: exit code was %d
 %s: could not start service "%s": error code %d
 %s: could not unregister service "%s": error code %d
 %s: database system initialization failed
 %s: invalid data in PID file "%s"
 %s: missing arguments for kill mode
 %s: no database directory specified and environment variable PGDATA unset
 %s: no operation specified
 %s: no server running
 %s: old server process (PID: %ld) seems to be gone
 %s: option file "%s" must have exactly one line
 %s: out of memory
 %s: server does not shut down
 %s: server is running (PID: %ld)
 %s: service "%s" already registered
 %s: service "%s" not registered
 %s: single-user server is running (PID: %ld)
 %s: too many command-line arguments (first is "%s")
 %s: unrecognized operation mode "%s"
 %s: unrecognized shutdown mode "%s"
 %s: unrecognized signal name "%s"
 (The default is to wait for shutdown, but not for start or restart.)

 If the -D option is omitted, the environment variable PGDATA is used.
 Is server running?
 Please terminate the single-user server and try again.
 Server started and accepting connections
 The program "%s" is needed by %s but was not found in the
same directory as "%s".
Check your installation.
 The program "%s" was found by "%s"
but was not the same version as %s.
Check your installation.
 Timed out waiting for server startup
 Try "%s --help" for more information.
 Usage:
 WARNING: online backup mode is active
Shutdown will not complete until pg_stop_backup() is called.

 Waiting for server startup...
 child process exited with exit code %d child process exited with unrecognized status %d child process was terminated by exception 0x%X child process was terminated by signal %d child process was terminated by signal %s could not change directory to "%s" could not find a "%s" to execute could not identify current directory: %s could not read binary "%s" could not read symbolic link "%s" could not start server
 invalid binary "%s" server shutting down
 server signaled
 server started
 server starting
 server stopped
 starting server anyway
 waiting for server to shut down... waiting for server to start... Project-Id-Version: PostgreSQL 9.0
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-02-18 13:21+0000
PO-Revision-Date: 2010-02-18 20:53+0200
Last-Translator: Peter Eisentraut <peter_e@gmx.net>
Language-Team: Peter Eisentraut <peter_e@gmx.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
 
Erlaubte Signalnamen für »kill«:
 
Optionen für alle Modi:
 
Optionen für »register« oder »unregister«:
 
Optionen für Start oder Neustart:
 
Optionen für Anhalten oder Neustart:
 
Berichten Sie Fehler an <pgsql-bugs@postgresql.org>.
 
Shutdown-Modi sind:
   %s init[db]               [-D DATENVERZ] [-s] [-o "OPTIONEN"]
   %s kill    SIGNALNAME PID
   %s register   [-N SERVICENAME] [-U BENUTZERNAME] [-P PASSWORT]
                    [-D DATENVERZ] [-t SEK] [-w] [-o "OPTIONEN"]
   %s reload  [-D DATENVERZ] [-s]
   %s restart [-w] [-t SEK] [-D DATENVERZ] [-s] [-m SHUTDOWN-MODUS]
                 [-o "OPTIONEN"]
   %s start   [-w] [-t SEK] [-D DATENVERZ] [-s] [-l DATEINAME] [-o "OPTIONEN"]
   %s status  [-D DATENVERZ]
   %s stop    [-W] [-t SEK] [-D DATENVERZ] [-s] [-m SHUTDOWN-MODUS]
   %s unregister [-N SERVICENAME]
   --help                 diese Hilfe anzeigen, dann beenden
   --version              Versionsinformationen anzeigen, dann beenden
   -D, --pgdata DATENVERZ Datenbankverzeichnis
   -N SERVICENAME  Servicename um PostgreSQL-Server zu registrieren
   -P PASSWORD     Passwort des Benutzers um PostgreSQL-Server zu registrieren
   -U USERNAME     Benutzername um PostgreSQL-Server zu registrieren
   -W                     warte nicht bis Operation abgeschlossen ist
   -c, --core-files       erlaubt postgres Core-Dateien zu erzeugen
   -c, --core-files       betrifft diese Plattform nicht
   -l, --log DATEINAME    schreibe Serverlog in DATEINAME (wird an
                         bestehende Datei angehängt)
   -m SHUTDOWN-MODUS  kann »smart«, »fast« oder »immediate« sein
   -o OPTIONEN            Kommandozeilenoptionen für postgres (PostgreSQL-
                         Serverprogramm) oder initdb
   -p PFAD-ZU-POSTGRES    normalerweise nicht notwendig
   -s, --silent           zeige nur Fehler, keine Informationsmeldungen
   -t SEK                 Sekunden zu warten bei Option -w
   -w                     warte bis Operation abgeschlossen ist
   fast        beende direkt, mit richtigem Shutdown
   immediate   beende ohne vollständigen Shutdown; führt zu Recovery-Lauf
              beim Neustart
   smart       beende nachdem alle Clientverbindungen geschlossen sind
  fertig
  Fehler
 %s ist ein Hilfsprogramm, um einen PostgreSQL-Server zu starten,
anzuhalten, neu zu starten, Konfigurationsdateien neu zu laden, den
Serverstatus auszugeben oder ein Signal an einen PostgreSQL-Prozess zu
senden.

 %s: PID-Datei »%s« existiert nicht
 %s: ein anderer Server läuft möglicherweise; versuche trotzdem zu starten
 %s: kann nicht als root ausgeführt werden
Bitte loggen Sie sich (z.B. mit »su«) als der (unprivilegierte) Benutzer
ein, der Eigentümer des Serverprozesses sein soll.
 %s: kann Server nicht neu laden; Einzelbenutzerserver läuft (PID: %ld)
 %s: kann Server nicht neu starten; Einzelbenutzerserver läuft (PID: %ld)
 %s: kann Grenzwert für Core-Datei-Größe nicht setzen; durch harten Grenzwert verboten
 %s: kann Server nicht anhalten; Einzelbenutzerserver läuft (PID: %ld)
 %s: konnte eigene Programmdatei nicht finden
 %s: konnte »postgres« Programmdatei nicht finden
 %s: konnte PID-Datei »%s« nicht öffnen: %s
 %s: konnte Service »%s« nicht öffnen: Fehlercode %d
 %s: konnte Servicemanager nicht öffnen
 %s: konnte Datei »%s« nicht lesen
 %s: konnte Service »%s« nicht registrieren: Fehlercode %d
 %s: konnte Signal zum Neuladen nicht senden (PID: %ld): %s
 %s: konnte Signal %d nicht senden (PID: %ld): %s
 %s: konnte Stopp-Signal nicht senden (PID: %ld): %s
 %s: konnte Server nicht starten
Prüfen Sie die Logausgabe.
 %s: konnte Server nicht starten: Exitcode war %d
 %s: konnte Service »%s« nicht starten: Fehlercode %d
 %s: konnte Service »%s« nicht deregistrieren: Fehlercode %d
 %s: Initialisierung des Datenbanksystems fehlgeschlagen
 %s: ungültige Daten in PID-Datei »%s«
 %s: fehlende Argumente für »kill«-Modus
 %s: kein Datenbankverzeichnis angegeben und Umgebungsvariable PGDATA nicht gesetzt
 %s: keine Operation angegeben
 %s: kein Server läuft
 %s: alter Serverprozess (PID: %ld) scheint verschwunden zu sein
 %s: Optionsdatei »%s« muss genau eine Zeile haben
 %s: Speicher aufgebraucht
 %s: Server fährt nicht herunter
 %s: Server läuft (PID: %ld)
 %s: Service »%s« bereits registriert
 %s: Service »%s« nicht registriert
 %s: Einzelbenutzerserver läuft (PID: %ld)
 %s: zu viele Kommandozeilenargumente (das erste ist »%s«)
 %s: unbekannter Operationsmodus »%s«
 %s: unbekannter Shutdown-Modus »%s«
 %s: unbekannter Signalname »%s«
 (Die Voreinstellung ist, beim Herunterfahren zu warten, aber nicht beim
Start oder Neustart.)

 Wenn die Option -D weggelassen wird, dann wird die Umgebungsvariable
PGDATA verwendet.
 Läuft der Server?
 Bitte beenden Sie den Einzelbenutzerserver und versuchen Sie es noch einmal.
 Server wurde gestartet und nimmt Verbindungen an
 Das Programm »%s« wird von %s benötigt, aber wurde nicht im
selben Verzeichnis wie »%s« gefunden.
Prüfen Sie Ihre Installation.
 Das Programm »%s« wurde von %s gefunden,
aber es hatte nicht die gleiche Version wie %s.
Prüfen Sie Ihre Installation.
 Zeitüberschreitung beim Warten auf Start des Servers
 Versuchen Sie »%s --help« für weitere Informationen.
 Aufruf:
 WARNUNG: Online-Backup-Modus ist aktiv
Herunterfahren wird erst abgeschlossen werden, wenn pg_stop_backup() aufgerufen wird.

 Warte auf Start des Servers...
 Kindprozess hat mit Code %d beendet Kindprozess hat mit unbekanntem Status %d beendet Kindprozess wurde durch Ausnahme 0x%X beendet Kindprozess wurde von Signal %d beendet Kindprozess wurde von Signal %s beendet konnte nicht in Verzeichnis »%s« wechseln konnte kein »%s« zum Ausführen finden konnte aktuelles Verzeichnis nicht ermitteln: %s konnte Programmdatei »%s« nicht lesen konnte symbolische Verknüpfung »%s« nicht lesen konnte Server nicht starten
 ungültige Programmdatei »%s« Server fährt herunter
 Signal an Server gesendet
 Server gestartet
 Server startet
 Server angehalten
 starte Server trotzdem
 warte auf Herunterfahren des Servers... warte auf Start des Servers... 
��    :      �  O   �      �  X   �  C   R  -   �  !   �      �       ,     )   D  )   n  )   �  )   �  )   �  )     )   @  )   j  )   �  )   �  )   �  )     )   <  ,   f  )   �  )   �  )   �  ,   	  ,   >	  )   k	  )   �	  )   �	  )   �	  )   
  )   =
  )   g
  )   �
  ,   �
  ,   �
  ,     )   B  &   l  �   �  )     �   I               -     6     M     a     s  )   �  )   �  	   �     �     �               (    ?  d   �  T   $  9   y  ,   �  )   �     
  >     ;   Y  ;   �  ;   �  ;     ;   I  ;   �  ;   �  ;   �  ;   9  ;   u  ;   �  ;   �  ;   )  >   e  ;   �  ;   �  ;     >   X  >   �  ;   �  ;     ;   N  ;   �  ;   �  ;     ;   >  ;   z  >   �  >   �  4   4  ;   i  0   �  �   �  ;   s  	  �  7  �     �  
   �     
  -   &  /   T     �  ;   �  ;   �     
          .     =     P     g        /                     8           .   4            %               :                              #      *      5              $      (   )         "   '      1       !           7   ,      0   2   
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
 shut down shut down in recovery shutting down starting up unrecognized status code unrecognized wal_level Project-Id-Version: PostgreSQL 8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-06-17 03:16+0000
PO-Revision-Date: 2010-06-17 13:48+0100
Last-Translator: Guillaume Lelarge <guillaume@lelarge.info>
Language-Team: PostgreSQLfr <pgsql-fr-generale@postgresql.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=ISO-8859-15
Content-Transfer-Encoding: 8bit
 
Si aucun r�pertoire (R�P_DONN�ES) n'est indiqu�, la variable
d'environnement PGDATA est utilis�e.

 %s affiche les informations de contr�le du cluster de bases de donn�es
PostgreSQL.

 %s : n'a pas pu ouvrir le fichier � %s � en lecture : %s
 %s : n'a pas pu lire le fichier � %s � : %s
 %s : aucun r�pertoire de donn�es indiqu�
 entiers 64-bits D�but de la sauvegarde :                                %X/%X
 Blocs par segment des relations volumineuses :          %u
 Octets par segment du journal de transaction :          %u
 Num�ro de version du catalogue :                        %u
 Param�trage actuel de max_connections :                 %d
 Param�trage actuel de max_locks_per_xact :              %d
 Param�trage actuel de max_prepared_xacts :              %d
 Param�trage actuel de wal_level :                       %s
 Taille du bloc de la base de donn�es :                  %u
 �tat du cluster de base de donn�es :                    %s
 Identifiant du syst�me de base de donn�es :             %s
 Stockage du type date/heure :                           %s
 Passage d'argument float4 :                             %s
 Passage d'argument float8 :                             %s
 Dernier point de contr�le :                             %X/%X
 Dernier NextMultiOffset du point de contr�le :          %u
 Dernier NextMultiXactId du point de contr�le :          %u
 Dernier NextOID du point de contr�le :                  %u
 Dernier NextXID du point de contr�le :                  %u/%u
 Dernier REDO (reprise) du point de contr�le :           %X/%X
 Dernier TimeLineID du point de contr�le :               %u
 Dernier oldestActiveXID du point de contr�le :          %u
 Dernier oldestXID du point de contr�le de la base :     %u
 Dernier oldestXID du point de contr�le :                %u
 Nombre maximum de colonnes d'un index:                  %u
 Alignement maximal des donn�es :                        %u
 Longueur maximale des identifiants :                    %u
 Longueur maximale d'un morceau TOAST :                  %u
 Emplacement de fin de la r�cup�ration minimale :        %X/%X
 Point de contr�le pr�c�dent :                           %X/%X
 Rapporter les bogues � <pgsql-bugs@postgresql.org>.
 Heure du dernier point de contr�le :                    %s
 Essayer � %s --help � pour plus d'informations.
 Usage :
  %s [OPTION] [R�P_DONN�ES]

Options :
  --help         affiche cette aide et quitte
  --version      affiche les informations de version et quitte
 Taille de bloc du journal de transaction :              %u
 ATTENTION : Les sommes de contr�le (CRC) calcul�es ne correspondent pas aux
valeurs stock�es dans le fichier.
Soit le fichier est corrompu, soit son organisation diff�re de celle
attendue par le programme.
Les r�sultats ci-dessous ne sont pas dignes de confiance.

 ATTENTION : possible incoh�rence dans l'ordre des octets
L'ordre des octets utilis� pour enregistrer le fichier pg_control peut ne
pas correspondre � celui utilis� par ce programme. Dans ce cas, les
r�sultats ci-dessous sont incorrects, et l'installation PostgreSQL
incompatible avec ce r�pertoire des donn�es.
 par r�f�rence par valeur nombres � virgule flottante restauration en cours (� partir des archives) restauration en cours (suite � un arr�t brutal) en production Derni�re modification de pg_control :                   %s
 Num�ro de version de pg_control :                       %u
 arr�t arr�t pendant la restauration arr�t en cours d�marrage en cours code de statut inconnu wal_level non reconnu 
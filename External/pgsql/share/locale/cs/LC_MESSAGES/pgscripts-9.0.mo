��    �        �   �	      8  K   9     �  f   �  
     >     >   L  =   �  -   �  C   �  A   ;     }  #   �     �  (   �     �  <     9   X  6   �  H   �  E     B   X  9   �  C   �  9     4   S  E   �  =   �  .     ;   ;  E   w  :   �  5   �  7   .  9   f  7   �  4   �  L     J   Z  5   �  2   �  7     2   F  2   y  J   �  :   �  5   2  G   h  0   �  <   �  0     M   O  J   �  G   �  4   0  H   e  E   �  9   �  v   .  <   �  I   �  @   ,  5   m  4   �  1   �  ;   
  5   F  6   |  3   �  4   �  =     8   Z  8   �  8   �  2     9   8  6   r  9   �     �  /   �  <     #   \  #   �  ?   �  %   �  #   
      .   3   N   &   �   5   �   E   �   I   %!  5   o!  I   �!  5   �!  E   %"  F   k"  4   �"  D   �"     ,#  *   J#  8   u#  6   �#  %   �#  (   $  (   4$  8   ]$  #   �$      �$     �$  8   �$  4   4%  $   i%     �%  ,   �%  ,   �%  ;   &  9   D&     ~&     �&     �&  *   �&  8   �&  ,   ('  8   U'  #   �'  G   �'  4   �'     /(  )   L(  7   v(     �(     �(  !   �(  +   �(     )     0)     L)     i)     �)     �)  
   �)     �)     �)     �)  '   �)  2   '*  7   Z*     �*  &   �*     �*     �*     �*     �*  :   �*     +     +  �  +  ^   �,     -  y   #-     �-  2   �-  2   �-  1   .  5   E.  C   {.  A   �.      /  (   "/  "   K/  *   n/  $   �/  @   �/  =   �/  ?   =0  G   }0  D   �0  A   
1  E   L1  G   �1  ?   �1  B   2  K   ]2  1   �2  9   �2  >   3  W   T3  :   �3  @   �3  7   (4  D   `4  K   �4  H   �4  L   :5  R   �5  6   �5  3   6  D   E6  ;   �6  ;   �6  T   7  C   W7  R   �7  H   �7  3   78  I   k8  4   �8  I   �8  F   49  D   {9  ?   �9  X    :  U   Y:  <   �:  t   �:  A   a;  I   �;  ?   �;  E   -<  ;   s<  7   �<  .   �<  9   =  >   P=  5   �=  >   �=  S   >  @   X>  =   �>  =   �>  7   ?  2   M?  /   �?  �   �?     4@  4   @@  P   u@  $   �@  %   �@  <   A  $   NA  &   sA  !   �A  2   �A  1   �A  K   !B  V   mB  E   �B  <   
C  G   GC  >   �C  I   �C  I   D  E   bD  S   �D  (   �D  5   %E  C   [E  >   �E  ,   �E  /   F  6   ;F  9   rF  !   �F  %   �F  )   �F  4   G  2   SG      �G  &   �G  2   �G  +   H  4   -H  2   bH     �H     �H     �H  )   �H  7   I  1   >I  8   pI  )   �I  L   �I  E    J  '   fJ  2   �J  A   �J  	   K  $   K  (   2K  (   [K     �K  +   �K  &   �K     �K     L     	L     (L     0L  #   FL     jL  #   �L  5   �L  >   �L     M  )   )M     SM     _M     aM     dM  >   yM     �M     �M     2   F   6   ]       m          �   8   _       t           �   �       P          �   Q   x                      <   e      c          k          >   l          �       �       ~   S   ;       %   @           !   r          C   K           �   f   3      G   Z   o      E   �       W   i   &   =   (      	   /   O   \   �   A           n   s   �       0      �   �   ^   }   d   �   �      �   #   J   Y   �             �   g   ?   :   y   +          {   1   w   �      �       z       -   4                   .                 q       5      `                      b       U   L   h   [      
   )       �   H   �   �   �   I   9      �           M   �   R   N           V   a   �   p   v          j   X               �       ,   �   "      |   �       *      �   B   $   7      u      '       T          D    
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
   -z, --analyze                   update optimizer hints
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
 Shall the new role be allowed to create databases? Shall the new role be allowed to create more new roles? Trusted? Try "%s --help" for more information.
 Usage:
 n no out of memory
 pg_strdup: cannot duplicate null pointer (internal error)
 y yes Project-Id-Version: postgresql-8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2009-06-06 23:08+0000
PO-Revision-Date: 2009-07-06 14:09+0200
Last-Translator: Zdeněk Kotala
Language-Team: 
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: KBabel 1.3.1
Plural-Forms: nplurals=3; plural=(n==1) ? 0 : (n>=2 && n<=4) ? 1 : 2;
 
Implicitně je vytvořena databáze stejného jména jako je jméno aktuálního uživatele.
 
Parametry spojení:
 
Je-li použit jeden z parametrů -d, -D, -r, -R, -s, -S, a jméno role
není zadáno, budete dotázán/a interaktivně.
 
Přepínače:
 
Pro detaily čtěte popis SQL příkazu CLUSTER.
 
Pro detaily čtěte popis SQL příkazu REINDEX.
 
Pro detaily čtěte popis SQL příkazu VACUUM.
 
Chyby hlaste na adresu <pgsql-bugs@postgresql.org>.
       --lc-collate=LOCALE      nastavení LC_COLLATE pro databázi
       --lc-ctype=LOCALE        nastavení LC_CTYPE pro databázi
   %s [PŘEPÍNAČ]... DATABÁZE
   %s [PŘEPÍNAČ]... JAZYK [DATABÁZE]
   %s [PŘEPÍNAČ]... [DATABÁZE]
   %s [PŘEPÍNAČ]... [DATABÁZE] [POPIS]
   %s [PŘEPÍNAČ]... [JMÉNO ROLE]
   --help                          ukáže tento text a skončí
   --help                       ukáže tento text a skončí
   --help                    ukáže tuto nápovědu a skončí
   --version                       ukáže informace o verzi a skončí
   --version                    ukáže informace o verzi a skončí
   --version                 ukáže informaci o verzi a skončí
   -D, --no-createdb         role nemůže vytvářet nové databáze
   -D, --tablespace=PROSTOR     výchozí prostor tabulek pro databázi
   -E, --encoding=KÓDOVÁNÍ      kódování znaků databáze
   -E, --encrypted           uložit heslo v zašifrované podobě
   -F, --freeze                    zmrazí transakční informace záznamů
   -I, --no-inherit          role nedědí práva
   -L, --no-login            role se nemůže přihlásit
   -N, --unencrypted         uložit heslo v otevřeném tvaru
   -O, --owner=VLASTNÍK         uživatel, který má být vlastníkem nové databáze
   -P, --pwprompt            nastavit heslo pro novou roli
   -R, --no-createrole       role nemůže vytvářet nové role
   -S, --no-superuser        role nebude superuživatel
   -T, --template=ŠABLONA       šablona databáze ke kopírování
   -U, --username=UŽIVATEL      jméno uživatele pro spojení se serverem
   -U, --username=UŽIVATEL   jméno uživatele pro spojení se serverem
   -U, --username=UŽIVATEL   jméno uživatele pro spojení (ne pro tvorbu)
   -U, --username=UŽIVATEL   jméno uživatele pro spojení (ne pro odstranění)
   -W, --password               vynutí dotaz na heslo
   -W, --password            vynutí dotaz na heslo
   -a, --all                       provést VACUUM všech databází
   -a, --all                 clusterovat všechny databáze
   -a, --all                 reindexovat všechny databáze
   -c, --connection-limit=N  limit počtu konexí pro role (implicitně: bez limitu)
   -d, --createdb            role může vytvářet nové databáze
   -d, --dbname=DATABÁZE           jméno databáze k provedení příkazu VACUUM
   -d, --dbname=DATABÁZE     databáze, ze které bude jazyk odstraněn
   -d, --dbname=DATABÁZE     databáze pro cluster
   -d, --dbname=DATABÁZE      databáze do které bude jazyk instalován
   -d, --dbname=DATABÁZE     databáze k reindexaci
   -e, --echo                      ukázat příkazy posílané na server
   -e, --echo                   ukázat příkazy posílané na server
   -e, --echo                ukazovat příkazy posílané na server
   -f, --full                      provést plné (FULL) VACUUM
   -h, --host=HOSTNAME          jméno databázového serveru nebo adresáře se soketem
   -h, --host=HOSTNAME       jméno databázového serveru nebo adresáře se soketem
   -i, --index=JMÉNO         obnovit pouze jmenovaný index
   -i, --inherit             role dědí práva rolí, kterých je členem
                            (implicitně)
   -i, --interactive         zeptej se před smazáním čehokoli
   -l, --list                ukáže seznam již nainstalovaných jazyků
   -l, --locale=LOCALE          nastavení locale pro databázi
   -l, --login               role se může přihlásit (implicitně)
   -p, --port=PORT              port databázového serveru
   -p, --port=PORT          port databázového serveru
   -q, --quiet                     tichý mód
   -q, --quiet               nevypisovat žádné zprávy
   -r, --createrole          role může vytvářet nové role
   -s, --superuser           role bude superuživatel
   -s, --system              reindexace systémového katalogu
   -t, --table='TABULKA[(SLOUPCE)]'  provést VACUUM pouze u specifikované tabulky
   -t, --table=TABULKA       vytvořit cluster pro danou tabulku
   -t, --table=TABULKA       reidexace pouze zvolené tabulky
   -v, --verbose                   vypisovat více informací
   -v, --verbose             vypisovat více informací
   -w, --no-password            neptá se na heslo
   -w, --no-password         neptá se na heslo
   -z, --analyze                   aktualizace informací používaných pro
                                  optimalizaci dotazů
 %s (%s/%s)  %s pročišťuje a analyzuje PostgreSQL databázi.

 %s vytváří cluster všech již dříve clusterovaných tabulek v databázi.

 %s vytvoří PostgreSQL databázi.

 %s vytvoří novou PostgreSQL roli.

 %s instaluje procedurální jazyk do PostgreSQL databáze.

 %s vytvoří PostgreSQL databázi.

 %s odstraňuje PostgreSQL databázi.

 %s odstraňuje PostgreSQL roli.

 %s odstraňuje procedurální jazyk z databáze.

 %s: "%s" není platné jméno kódování znaků
 %s: nelze vytvořit cluster pro specifickou tabulku ve všech databázích
 %s: nelze vytvořit cluster ve všech databázích a zároveň specifikovat jen jednu
 %s: nelze reindexovat vybraný index a současně sytémový katalog
 %s: nelze reindexovat vybraný index ve všech databázích
 %s: nelze reindexovat vybranou tabulku a současně sytémový katalog
 %s: nelze reindexovat vybranou tabulku ve všech databázích
 %s: nelze reindexovat všechny databáze a současně zvolenou databázi
 %s: nelze reindexovat všechny databáze a současně systemový katalog
 %s: nelze provést VACUUM specifické tabulky ve všech databázích
 %s: nelze provádět VACUUM u všech databází a zároveň specifikovat jen jednu
 %s: provádí se cluster databáze "%s"
 %s: vytváření clusterů databáze "%s" selhalo: %s %s: vytváření clusteru tabulky "%s" v databázi "%s" selhalo: %s %s: tvorba komentáře selhala (databáze byla vytvořena): %s %s: nelze navázat spojení s databází %s
 %s: nelze navázat spojení s databází %s: %s %s: nelze získat aktuální uživatelské jméno: %s
 %s: nelze získat informace o aktuálním uživateli: %s
 %s: tvorba nové role selhala: %s %s: vytvoření databáze selhalo: %s %s: odstraňování databáze selhalo: %s %s: jazyk "%s" je již v databázi "%s" instalován
 %s: jazyk "%s" není v databázi "%s" instalován
 %s: instalace jazyka selhala: %s %s: odstraňování jazyka selhalo: %s %s: chybí vyžadovaný parametr jméno databáze
 %s: chybí povinný parametr jméno jazyka
 %s: --locale a --lc-collate nelze zvolit současně
 %s: --locale a --lc-ctype nelze zvolit současně
 %s: dotaz selhal: %s %s: dotaz byl: %s
 %s: reindexace databáze "%s"
 %s: reindexace databáze "%s" selhala: %s %s: reindexace indexu "%s" v databázi "%s" selhala: %s %s: reindexace systémového katalogu selhala: %s %s: reindexace tabulky "%s" v databázi "%s" selhala: %s %s: odstraňování role "%s" selhalo: %s %s: stále je %s funkcí definováno v jazyce "%s"; jazyk nebyl odstraněn.
 %s: příliš mnoho parametrů příkazové řádky (první je "%s")
 %s: provádí se VACUUM databáze "%s"
 %s: provádění VACUUM databáze "%s" selhalo: %s %s: provádění VACUUM tabulky "%s" v databázi "%s" selhalo: %s Určitě? Požadavek na zrušení byl poslán
 Nelze poslat požadavek na zrušení: %s Databáze "%s" bude trvale odstraněna.
 Zadejte znova:  Vložte jméno role, kterou chete přidat:  Vložte jméno role pro odstranění:  Vložte heslo nové role:  Jméno Zašifrování hesla selhalo.
 Heslo:  Hesla se neshodují.
 Prosím odpovězte "%s" nebo "%s".
 Procedurální jazyky Role "%s" bude trvale odstraněna.
 Měla by mít nová role právo vytvářet databáze? Měla by mít nová role právo vytvářet další nové role? Důvěryhodný? Zkuste "%s --help" pro více informací.
 Použití:
 n ne paměť vyčerpána
 pg_strdup: nelze duplikovat nulový ukazatel (interní chyba)
 a ano 
��    �      �  �   l	      �  K   �     �  e   �  
   Q  >   \  >   �  =   �  -        F  #   _     �  (   �     �  <   �  9   !  6   [  H   �  E   �  B   !  9   d  C   �  9   �  4     =   Q  .   �  ;   �  E   �  :   @  5   {  7   �  9   �  7   #  4   [  L   �  J   �  3   (  0   \  ;   �  7   �  2     2   4  J   g  :   �  5   �  G   #  0   k  <   �  0   �  M   
  J   X  G   �  4   �  H      E   i  9   �  v   �  <   `  I   �  5   �  4     1   R  ;   �  5   �  6   �  3   -  4   a  =   �  8   �  8     8   F  9        �  /   �  <   �  #   2  #   V  ?   z  %   �  #   �       3   $  &   X  5     E   �  I   �  5   E  I   {  5   �  E   �  F   A   4   �   D   �      !  *    !  8   K!  6   �!  %   �!  (   �!  (   
"  8   3"  #   l"      �"     �"  8   �"  4   
#  $   ?#     d#  ,   �#  ,   �#     �#     �#     $  *   $$  8   O$  ,   �$  8   �$  #   �$  G   %  4   Z%     �%  )   �%  7   �%     &     &  !   1&  "   S&  +   v&     �&     �&     �&     �&     
'     '  
   ,'     7'     P'     m'  '   �'  "   �'  2   �'  7    (     8(  &   A(     h(     p(     r(     u(     w(  �  {(  �   *  :   �*  �   +     ,  �   ',  �   �,  �   R-  ~   �-     r.  #   �.     �.  (   �.     �.  �   /  t   �/  �   0  �   �0  �   71  �   �1  �   n2  �   3  ~   �3  �   +4  m   �4  g   55  �   �5  �   B6  �   �6  �   �7  �   38     �8  n   =9  g   �9  �   :  �   �:  N   ^;  ^   �;  �   <  �   �<  �   "=  �   �=  �   `>  �   ?  �   �?  �   !@  }   �@  |   7A  �   �A  �   7B  �   �B  �   qC  [   �C  �   WD  �   �D  �   �E    F  �   7G  �   �G  �   aH  Y   �H  V   JI  n   �I  q   J  �   �J  }   K  �   �K  �   &L  �   �L  �   nM  p   N  �   �N     O  �   O  �   �O  x   YP  �   �P  �   ZQ  �   R  c   �R  x   �R  �   oS  c   T  �   vT  �   BU  �   V  �   W    �W  �   �X  �   �Y    �Z  �   �[  �   �\  f   l]  g   �]  �   ;^  (   �^  _   �^  b   \_  m   �_  �   -`  e   �`  S   a  Z   qa  �   �a  u   Ub  F   �b  R   c  �   ec  {   �c  6   vd  0   �d  m   �d  s   Le  �   �e  z   ff  �   �f  W   �g  �   �g  |   �h  d   @i  k   �i  �   j     �j  [   �j  s   k  t   �k  k   l  8   ql  �   �l  b   5m  �   �m     .n  Y   >n     �n  R   �n  7   o  +   Co  c   oo  w   �o  �   Kp  �   �p  %   �q  d   �q     )r     >r     Nr  	   ^r  	   hr     0       �                      H       �   4   !       _   @   2   '           -              e   =       &   ^              #   K       `   l             /          "   f           ,   j   F   q   N   z   \       y   P   {   S       $             C   o   J   ;   E   V   d           .   |       :   u      �      O   Z   �   7   G   }       �          �       h   *          X   >   i   �   Y      �   ~   [   T   B   w   �          Q           �   c   ]       L   a      t      �   M   %   s              �       (         <          
   �   R       )   6   n   9   �   D      5   �       1   �       v   p       I   g   b       A       �   8   ?          �      +   m       �   3   U       W   �              �   x   	              k      �   r                 
By default, a database with the same name as the current user is created.
 
Connection options:
 
If one of -s, -S, -d, -D, -r, -R and ROLENAME is not specified, you will
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
   -W, --password               prompt for password
   -W, --password            prompt for password
   -W, --password            prompt for password to connect
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
 %s: query failed: %s %s: query was: %s
 %s: reindexing database "%s"
 %s: reindexing of database "%s" failed: %s %s: reindexing of index "%s" in database "%s" failed: %s %s: reindexing of system catalogs failed: %s %s: reindexing of table "%s" in database "%s" failed: %s %s: removal of role "%s" failed: %s %s: still %s functions declared in language "%s"; language not removed
 %s: too many command-line arguments (first is "%s")
 %s: vacuuming database "%s"
 %s: vacuuming of database "%s" failed: %s %s: vacuuming of table "%s" in database "%s" failed: %s Are you sure? Cancel request sent
 Could not send cancel request: %s Could not send cancel request: %s
 Database "%s" will be permanently removed.
 Enter it again:  Enter name of role to add:  Enter name of role to drop:  Enter password for new role:  Name Password encryption failed.
 Password:  Passwords didn't match.
 Please answer "%s" or "%s".
 Procedural Languages Role "%s" will be permanently removed.
 Shall the new role be a superuser? Shall the new role be allowed to create databases? Shall the new role be allowed to create more new roles? Trusted? Try "%s --help" for more information.
 Usage:
 n no y yes Project-Id-Version: pgscripts
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2007-09-22 03:23-0300
PO-Revision-Date: 2007-11-20 11:52+0530
Last-Translator: ஸ்ரீராமதாஸ் <shriramadhas@gmail.com>
Language-Team: தமிழ் <ubuntu-l10n-tam@lists.ubuntu.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: KBabel 1.11.4
 
இயல்பாக, தற்போதைய பயனரின் பெயரினையேக் கொண்டு தரவுக் களன் உருவாக்கப்படும்.
 
இணைப்புத் தேர்வுகள்:
 
-s, -S, -d, -D, -r, -R மற்றும் ROLENAME ல் ஏதேனும் ஒன்று தரப் படவில்லையென்றாலும், தாங்கள்
தரக் கோரப்படுவீர்கள்.
 
தேர்வுகள்:
 
மேலும் விவரங்களக்கு SQL ஆணை CLUSTER ன் விளக்கத்தினை வாசிக்கவும்ails.
 
விவரங்களுக்கு SQL ஆணை REINDEX விளக்கத்தினை வாசிக்கவும்.
 
மேலும் விவரங்களுக்கு SQL ஆணை VACUUM ன் விளக்கத்தினை வாசிக்கவும்.
 
வழுக்களை <pgsql-bugs@postgresql.org> க்குத் தெரியப்படுத்தவும்.
   %s [OPTION]... DBNAME
   %s [OPTION]... LANGNAME [DBNAME]
   %s [OPTION]... [DBNAME]
   %s [OPTION]... [DBNAME] [DESCRIPTION]
   %s [OPTION]... [ROLENAME]
   --help                          இவ்வுதவியினைக் காட்டியபின் வெளிவருக
   --help                       உதவியைக் காட்டியபின், வெளிவருக
   --help                    இவ்வுதவியினைக் காட்டியதும், வெளிவருக
   --version                       வெளியீட்டு விவரங்களைக் காட்டியபின் வெளிவரவும்
   --version                    வெளியீட்டுத் தகவலைக் காட்டியபின், வெளிவருக
   --version                 வெளியீட்டு விவரங்களை வெளியிட்டபின், வெளிவரவும்
   -D, --no-createdb         இப்பொறுப்புடையவர் தரவுக் களன்களை உருவாக்க இயலாது 
   -D, --tablespace=TABLESPACE  தரவுக் களனுக்கான இயல்பிருப்பு அட்டவணை இடம்
   -E, --encoding=ENCODING      தரவுக்களனுக்கான எழுத்துருவாக்கம்
   -E, --encrypted           சேமிக்கப் பட்ட கடவுச்சொல்லின் உருதிரிக்கவும்
   -I, --no-inherit          இப்பொறுப்பு சலுகைகளை ஏற்காது
   -L, --no-login            இப்பொறுப்பால் நுழைய இயலாது
   -N, --unencrypted           சேமிக்கப் பட்ட கடவுச்சொல்லின் உருதிரிக்க வேண்டா
   -O, --owner=OWNER            புதிய தரவுக் களனுக்கு உரிமையுள்ள தரவுக் களப் பயனர்
   -P, --pwprompt            புதியப் பொறுப்பிற்கு கடவுச் சொல்லொன்றினைத் தரவும்
   -R, --no-createrole       இப்பொறுப்பு புதிய பொறுப்புகளை உருவாக்க இயலாது
   -S, --no-superuser        பொறுப்பு முதன்மைப் பயனருக்கானதாக இராது
   -T, --template=TEMPLATE      நகலெடுப்பதற்கான தரவுக்கள வார்ப்பு
   -U, --username=USERNAME      தொடர்பு கொள்ளும் பயனர் பெயர்
   -U, --username=USERNAME   இணைப்பிற்கான பயனரின் பெயர்
   -U, --username=USERNAME   இணைப்புக்கான பயனர் பெயர் (உருவாக்கத்துக்கானது அல்ல)
   -U, --username=USERNAME   இணைப்பதறகான பயனர் பெயர் (விலக்குவதற்கானது அல்ல)
   -W, --password               கடவுச்சொல் கோருக
   -W, --password            கடவுச் சொல்லினைக் கோருக
   -W, --password            இணைக்கும் பொருுட்டு கடவுச் சொல் கோரவும்
   -a, --all                       அனைத்து தரவுக் களனையும் காலி செய்யும்
   -a, --all                 அனைத்து தரவுக் களன்களையும் கூட்டமைக்கும்ும்
   -a, --all                 அனைத்து தரவுக்களன்களையும் மீள்வரிசைப் படுத்தும்
   -c, --connection-limit=N  பொறுப்புக்கான தொடர்பு எல்லை (இயல்பு: எல்லை இல்லை)
   -d, --createdb            பொறுப்பாளர் தரவுக் களன்களை உருவாக்க இயலாதும்
   -d, --dbname=DBNAME             காலி செய்யப் பட் வேண்டிய தரவுக் களன்
   -d, --dbname=DBNAME       அகற்றப்பட வேண்டிய மொழி இருக்கும் தரவுக் களன்
   -d, --dbname=DBNAME       கூட்டமைக்கப்பட வேண்டிய தரவுக் களன்
   -d, --dbname=DBNAME       தரவுக் களன் நிறுவப் பட வேண்டிய மொழி
   -d, --dbname=DBNAME       மீள்வரிசையிடப் படவேண்டிய தரவுக்களன்
   -e, --echo                      வழங்கிக்கு அனுப்ப் படவேண்டிய ஆணைகளைக் காட்டுக
   -e, --echo                   வழங்கிக்கு அனுப்பப் படும் ஆணைகளைக் காட்டுக
   -e, --echo                வழங்கிக்கு இடப்படும் ஆணைகளைக் காட்டும்
   -f, --full                      முழுமையாக காலி செய்க
   -h, --host=HOSTNAME          தரவுக் கள வழங்கி தருநர் அல்லது சாக்கெட் அடைவு
   -h, --host=HOSTNAME       தரவுக் கள வழங்கி தருநர் அல்லது சாக்கெட் அடைவு
   -i, --index=INDEX         குறிப்பிட்ட வரிசையை மட்டும் மீளுருவாக்குக
   -i, --inherit             தான் அங்கத்தினராய் உள்ள பொறுப்புகளின்
                            சலுகைகளை இப்பொறுப்பு பெறும் (இயல்பிருப்பு)
   -i, --interactive         எதையும் அகற்றும் முன் எச்சரிக்கவும்
   -l, --list                தற்சமயம் நிறுவப்பட்ட மொழிகளின் பட்டியலைக் காட்டுக
   -l, --login               இப்பொறுப்பால் நுழைய இயலும் (இயல்பிருப்பு)
   -p, --port=PORT              தரவுக் கள வழங்கி துறை
   -p, --port=PORT           தரவுக் கள வழங்கி துறை
   -q, --quiet                     தகவல் எதையும் எழுத வேண்டாம்
   -q, --quiet               எந்தத் தகவலையும் எழுத வேண்டாம்
   -r, --createrole          இப்பொறுப்பு புதிய பொறுப்புகளை உருவாக்கலாம்
   -s, --superuser           பொறுப்பு முதன்மைப் பயனாக இருக்கும்
   -s, --system              அமைப்பு காடலாகுகளை மீள்வரிசைப் படுத்தும்
   -t, --table='TABLE[(COLUMNS)]'  குறிப்பிட்டு காலியாக்கப் படவேண்டிய அட்டவணைகள் மட்டும்
   -t, --table=TABLE         குறிப்பிட்ட அட்டவணையை மாத்திரம் கூட்டமை
   -t, --table=TABLE         குறிப்பிட்ட அட்டவணையை மாத்திரம் மீள்வரிசையிடுக
   -v, --verbose                   அதிக வெளியீட்டினை இயற்றவும்
   -z, --analyze                   திறமேம்பாட்டு குறிப்புகளை புதுப்பி
 %s (%s/%s)  %s போஸ்டுகிரெஸ் தரவுக் களனொன்றை துடைத்து ஆராயும்.

 %s தரவுக் களத்தில் முன்னரே கூட்டமைக்கப்பட்ட அட்டவணைகளை கூட்டமைக்கும்.

 %s போஸ்ட்கிரெஸ் தரவுக் களனொன்றை உருவாக்கும்.

 %s போஸ்டுகிரெஸ்ஸின் புதிய பொறுப்பினை உருவாக்கும்.

 %s முறைசார் மொழியொன்றை போஸ்டுகிரெஸ் தரவுக்களத்தினுள் நிறுவும்.

 %s போஸ்டுகிரெஸ் தரவுக் களனொன்றை மீள்வரிசையிடுறோம்.

 %s போஸ்டுகிரெஸ் தரவுக் களனை அகற்றும்.

 %s ஒரு போஸ்டுகிரெஸ் பொறுப்பினை அகற்றிவிடும்.

 %s முறை சார் மொழியொன்று தரவுக் களத்திலிருந்து அகற்றப் படும்.

 %s: "%s" செல்லத்தகாத எழுத்துருவாக்க முறை
 %s: குறிப்பிட்ட அட்டவணையொன்றை அனைத்து தரவுக் களன்களிலும் கூட்டமைக்க இயலாது
 %s: அனைத்துத் தரவுக் களன்களோடு குறிப்பிட்ட ஒன்றை ஒரே நேரத்தில் கூட்டமைக்க இயலாது
 %s: ஒரே நேரத்தில் குறிப்பிட்ட வரிசையினையும் அமைப்பு காடலாகுகளையும் மீள்வரிசைப் படுத்த இயலாது
 %s: வரிசையொன்றினை அனைத்து தரவுக் களன்களிலும் மீள்வரிசைப் படுத்த இயலாது
 %s: ஒரே நேரத்தில் குறிப்பிட்ட அட்டவணையினையும் அமைப்பு காடலாகுகளையும் மீள்வரிசைப் படுத்த இயலாது
 %s: குறிப்பிட்ட அட்டவணையினைமஅனைத்து தரவுக் களன்களிலும்ல் மீள்வரிசைப் படுத்த இயலாது
 %s: அனைத்து தரவுக் களன்களையும் ் குறிப்பிட்ட ஒன்றையும் ஒரே நேரத்தில மீள்வரிசைப் படுத்த இயலாது
 %s: அனைத்து தரவுக் களன்களையும் அமைப்பின் காடலாகுகளையும் ஒரே நேரத்தில் மீள்வரிசைப் படுத்த இயலாது
 %s: குறிப்பிட்ட அட்டவணையை அனைத்து தரவுக் களன்களிலும் காலி செய்ய இயலாது
 %s: அனைத்துக் தரவுக் களன்களையும் குறிப்பிட்ட ஒன்றையும் ஒரே நேரத்தில் காலி செய்ய இயலாது
 %s: "%s" தரவுக் களன் கூட்டமைக்கப்படுகிறது
 %s: "%s" தரவுக் களனை கூட்டமைக்க இயலவில்லை: %s %s: அட்வணை "%s" யினை "%s" தரவுக்பளத்தில் கூட்டமைக்க இயலவில்லை: %s %s: கரு (database was created): %s %s: தரவுக் களனுடன் இணைக்க இயலவில்லை %s
 %s: தரவுக் களனுடன் இணைக்க இயலவில்லை %s: %s %s: தற்போதைய பயனர் பெயரைப் பெற இயலவில்லை: %s
 %s: தற்போதைய பயனர் குறித்த விவரங்களை பெற இயலவில்லை: %s
 %s: புதிய பொறுப்பை உருவாக்க இயலவில்லை: %s %s: தரவுக் கள உருவாக்கம் தோல்வி: %s %s: தரவுக் களத்தை அகற்ற இயலவில்லை : %s %s: "%s" மொழி ஏற்கனவே தரவுக் களத்தில் விடுபட்டுள்ளது "%s"
 %s: மொழி "%s" தரவுக் களத்தில் நிறுவப்படவில்லை "%s"
 %s: நிறுவல் மொழிக்ககான ளம்: %s %s: மொழியை அகற்றுவதில் சிக்கல்: %s %s: தரவுக் கள பெயருக்குத் தேவையான துப்பு விடுபட்டுள்ளது
 %s: தேவையான மொழிப் பெயர் துப்பு விடுபட்டுள்ளது
 %s: கோரிக்கை தவறியது: %s %s: கோரிக்கையாவது: %s
 %s: தரவுக்களன் "%s" மீள்வரிசையிடப் படுகிறது 
 %s: தரவுக்களன் "%s" னை மீள்வரிசையிட இயலவில்லை: %s %s: வரிசை "%s" யினை தரவுக்களன் "%s" ல் மீள்வரிசைப் படுத்த இயலவில்லை: %s %s: அமைப்பு காடலாகுகளை மீளவரிசையிட இயலவில்லை: %s %s: அட்டவணை "%s" யினை தரவுக் களன் "%s" ல் மீள் வரிசைப் படுத்த இயலவில்லை: %s %s: பொறுப்பினை "%s" அகற்ற இயலவில்லை: %s %s: ஆயினும் %s மொழிக்கான செயற்பாடுகள் விண்டப் பட்டுள்ளன "%s"; மொழி அகற்றப் படவி்வில்லை
 %s: அளவுக்கதிக முனைய-வரி துப்புகள்க முதலாவதுs "%s")
 %s: "%s" தரவுக் களன் காலிசெய்யப் படுகிறது
 %s: "%s" தரவுக் களனைக் காலி செய்ய இயலவில்லை: %s %s: அட்டவணை "%s" னைக் தரவுக் களன் "%s" ல் காலி செய்ய இயலவில்லை: %s உறுதியாக? அனுப்பப் பட்ட கோரிக்கையை இரத்துக
 இரத்துக்கான கோரிக்கையை அனுப்ப அயலவில்லை: %s இரத்துக்கான கோரிக்கையை அனுப்ப இயலவில்லை: %s
 தரவுக் களன் "%s" நிரந்தரமாக அகற்றப் படும்.
 மீண்டும் உள்ளிடவும்: சேர்க்கப் படவேண்டிய பொறுப்பின் பெயரினைக் காட்டுக:  விலக்கப் படவேண்டிய பொறுப்பினை இடுக:  புதியப் பொறுப்பிற்கானகானக் கடவுச் சொல்லினைக் காட்டுக: பெயர் கடவுச் சொல் உருதிரிப்பு தவறியது.
 கடவுச்சொல்: கடவுச் சொற்கள் பொருந்தவில்லை.
 பதிலிடுக "%s" அல்லது "%s".
 முறையான மொழிகள் பொறுப்பு "%s" நிரந்தரமாக அகற்றப்படும்.
 மூதன்மைப் பயனராக புதிய பொறுப்பு இருக்கலாமா? தரவுக் களத்தினை உருவாக்க புதிய பொறுப்பினை அனுமதிக்கலாமா? புதிய பொறுப்பிற்கு புதிய பொறுப்புக்களை உருவாக்க அனுமதி வழங்கலாமா? நம்பத்தக்கதா? மேலும் விவரமறிய "%s --help" முயற்சிக்கவும்.
 பயனளவு:
 இல்லை இல்லை ஆம் ஆம் 
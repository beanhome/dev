��    |      �  �   �      x
  R   y
     �
  
   �
  -   �
  �   #  �   �  B   N     �    �  J   �  5     J   N  6   �  P   �  C   !  :   e     �  4   �  B   �  H   8  G   �  >   �  9     3   B  ?   v  /   �  -   �  E     y   Z  (   �  �   �  7   �  (   �  ,   �  3   "  '   V  5   ~  F   �  -   �  -   )  /   W  "   �  6   �  �   �  �   �  0     ;   H  $   �  /   �  �   �  �   e  ~   �  1   w     �  J   �  �        �  C   �  -   1  8   _  !   �  ,   �  /   �  4     A   L  ,   �     �  P   �  K   ,     x     �     �     �     �  ;   �  9   3  �   m  >   �  ;   =  2  y  u   �   q   "!  f   �!  &   �!     ""     *"  &   9"  0   `"  .   �"  )   �"  )   �"  "   #  #   7#  "   [#      ~#  (   �#  "   �#     �#  "   $  !   )$  ,   K$  $   x$  %   �$  !   �$     �$     �$     %      5%     V%     s%  -   �%  0   �%     �%     &     (&  )   <&     f&     j&  &   y&  3   �&     �&  +   �&  !   '  �  8'  �   �(  l   �)     >*  �   T*  8  �*  �  ,  �   .     �.  �  �.  �   �0  5   �1  �   �1  }   �2  }   3  �   �3  �   R4     �4  x   �4  �   v5  �   6  �   �6     A7  �   �7  a   I8  }   �8  ~   )9  q   �9  �   :  *  �:  L   <  �  ]<  s   �=  W   g>  s   �>  �   3?  U   �?  �   @  �   �@  �   }A  �   B  �   �B  S   1C  �   �C  "  &D  t  IF  y   �G  �   8H  V   �H  u   *I  x  �I  �  K  �  �L  �   SN  <   %O  �   bO  L  HP  -   �R  �   �R  v   �S  �   T  a   �T  }   U  �   �U  �   .V  �   �V  L   W  h   �W  �   5X  �   Y  2   �Y  {   Z  R   �Z  X   �Z  �   =[  �   �[  z   �\    �\  �   ^  �   �^  �  \_  0  4b  )  ec    �d  r   �e     f  E   5f  �   {f  �   g  l   �g  a   �g  b   _h  �   �h  �   Oi  G   �i  n   j  d   �j  N   �j  P   Ak  K   �k  h   �k  p   Gl  d   �l  _   m     }m  \   �m  Y   Zn  M   �n  h   o  c   ko  p   �o  �   @p  �   �p  _   nq  E   �q  -   r  x   Br  
   �r  !   �r  �   �r  �   �s  Y   #t  �   }t  �   ?u     e      t   B             S       *   G         [   ?   ]   -            F       r              Q      W           x   n      w   K                    	       i   _   k   U          7       $       l   8              Y   (   A   @   D      p   J       h      s      m       R   M       !   C   a   '      `   T   #   d   E       2              4       {   q   /   5       O       <                   3   f   I       g   z       X       L   >       V   j   H      v          |   c   0   b   6                  %       ,   9   "   N       :   .   \          =   
             Z   &   1   P              ;       u   y       ^   )   o   +    
If the data directory is not specified, the environment variable PGDATA
is used.
 
Less commonly used options:
 
Options:
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
                             set default text search configuration
   %s [OPTION]... [DATADIR]
   --lc-collate, --lc-ctype, --lc-messages=LOCALE
  --lc-monetary, --lc-numeric, --lc-time=LOCALE
                            initialize database cluster with given locale
                            in the respective category (default taken from
                            environment)
   --locale=LOCALE           initialize database cluster with given locale
   --no-locale               equivalent to --locale=C
   --pwfile=FILE             read password for the new superuser from file
   -?, --help                show this help, then exit
   -A, --auth=METHOD         default authentication method for local connections
   -E, --encoding=ENCODING   set default encoding for new databases
   -L DIRECTORY              where to find the input files
   -T, --text-search-config=CFG
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
 %s: The password file was not generated. Please report this problem.
 %s: cannot be run as root
Please log in (using, e.g., "su") as the (unprivileged) user that will
own the server process.
 %s: could not access directory "%s": %s
 %s: could not access file "%s": %s
This might mean you have a corrupted installation or identified
the wrong directory with the invocation option -L.
 %s: could not change permissions of directory "%s": %s
 %s: could not create directory "%s": %s
 %s: could not create symbolic link "%s": %s
 %s: could not determine valid short version string
 %s: could not execute command "%s": %s
 %s: could not find suitable encoding for locale "%s"
 %s: could not find suitable text search configuration for locale "%s"
 %s: could not open file "%s" for reading: %s
 %s: could not open file "%s" for writing: %s
 %s: could not read password from file "%s": %s
 %s: could not write file "%s": %s
 %s: data directory "%s" not removed at user's request
 %s: directory "%s" exists but is not empty
If you want to create a new database system, either remove or empty
the directory "%s" or run %s
with an argument other than "%s".
 %s: directory "%s" exists but is not empty
If you want to store the transaction log there, either
remove or empty the directory "%s".
 %s: failed to remove contents of data directory
 %s: failed to remove contents of transaction log directory
 %s: failed to remove data directory
 %s: failed to remove transaction log directory
 %s: file "%s" does not exist
This means you have a corrupted installation or identified
the wrong directory with the invocation option -L.
 %s: file "%s" is not a regular file
This means you have a corrupted installation or identified
the wrong directory with the invocation option -L.
 %s: input file "%s" does not belong to PostgreSQL %s
Check your installation or specify the correct path using the option -L.
 %s: input file location must be an absolute path
 %s: invalid locale name "%s"
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
 %s: unrecognized authentication method "%s"
 %s: warning: encoding mismatch
 %s: warning: specified text search configuration "%s" may not match locale "%s"
 %s: warning: suitable text search configuration for locale "%s" is unknown
 Enter it again:  Enter new superuser password:  Passwords didn't match.
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
 The encoding you selected (%s) and the encoding that the selected
locale uses (%s) are not known to match.  This might lead to
misbehavior in various character string processing functions.  To fix
this situation, rerun %s and either do not specify an encoding
explicitly, or choose a matching combination.
 The files belonging to this database system will be owned by user "%s".
This user must also own the server process.

 The program "postgres" is needed by %s but was not found in the
same directory as "%s".
Check your installation.
 The program "postgres" was found by "%s"
but was not the same version as %s.
Check your installation.
 Try "%s --help" for more information.
 Usage:
 caught signal
 child process exited with exit code %d child process exited with unrecognized status %d child process was terminated by exception 0x%X child process was terminated by signal %d child process was terminated by signal %s copying template1 to postgres ...  copying template1 to template0 ...  could not change directory to "%s" could not find a "%s" to execute could not identify current directory: %s could not open directory "%s": %s
 could not read binary "%s" could not read directory "%s": %s
 could not read symbolic link "%s" could not remove file or directory "%s": %s
 could not set junction for "%s": %s
 could not write to child process: %s
 creating configuration files ...  creating conversions ...  creating dictionaries ...  creating directory %s ...  creating information schema ...  creating subdirectories ...  creating system views ...  creating template1 database in %s/base/1 ...  fixing permissions on existing directory %s ...  initializing dependencies ...  initializing pg_authid ...  invalid binary "%s" loading system objects' descriptions ...  ok
 out of memory
 selecting default max_connections ...  selecting default shared_buffers/max_fsm_pages ...  setting password ...  setting privileges on built-in objects ...  vacuuming database template1 ...  Project-Id-Version: Postgres Tamil Translation
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2007-09-21 09:15-0300
PO-Revision-Date: 2007-09-25 20:54+0530
Last-Translator: ஆமாச்சு <amachu@ubuntu.com>
Language-Team: Ubuntu Tamil Team <ubuntu-l10n-tam@lists.ubuntu.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
Content-Transfer-Encoding: 8bit
X-Poedit-Language: Tamil
X-Poedit-Country: INDIA
X-Poedit-SourceCharset: utf-8
 
 தரவின் அடைவு கொடுக்கப் படவில்லையெனின், பணிச்சுழல் மாறி PGDATA
 பயன் படுத்தப் படும்.
 
அரிதாகப் பயன்படுத்தப் படும் தேர்வுகள்:
 
தேர்வு:
 
 வழுக்களை <pgsql-bugs@postgresql.org> ற்குத் தெரியப் படுத்தவும். 
 
வெற்றி.  கீழ்காணும் தகவல்களைப் பயன் படுத்தி தாங்கள் தரவுக் கள வழங்கியைத் துவக்கலாம்:

    %s%s%spostgres%s -D %s%s%s
or
    %s%s%spg_ctl%s -D %s%s%s -l logfile start

 
எச்சரிக்கை: உள் இணைப்புகளுக்கு"trust" அங்கீகாரம் வழங்கப்படுகிறது.
இதனை அடுத்த முறை initidb இயக்கும் போது 
 pg_hba.conf கோப்பினை  தொகுப்பதன் மூலமாகவோ அல்லது -A தேர்வினை பயன்படுத்தியோ மாற்றிக் கொள்ளலாம்.
                              இயல்பிருப்பு உரைத் தேடல் வடிவமைப்பினை அமைக்கவும்.
   %s [OPTION]... [DATADIR]
   --lc-collate, --lc-ctype, --lc-messages=LOCALE
  --lc-monetary, --lc-numeric, --lc-time=LOCALE
                            கொடுக்கப் பட்ட அகத்தினைக் கொண்டு தரவுக் கள கூட்டமைப்பை அததற்கான வகையிலிருந்து (இயல்பிருப்பு 
 பணிச்சூழலிலிருந்து எடுக்கப்படும்) துவக்கவும்
   --locale=LOCALE           கொடுக்கப் பட்ட அகத்தினைக் கொண்டு தரவுக் கள கூட்டமைப்பை துவக்கவும்
   --no-locale               equivalent to --locale=C
   --pwfile=FILE             கோப்பிலிருந்து முதன்மைப் பயனருக்கான கடவுச் சொல்லை  வாசிக்கவும்
   -?, --help                இவ்வுதவியைக் காட்டிய பின் வெளிவருக
   -A, --auth=METHOD         உள்ளூர இணைப்புகளுக்கான அனுமதி முறை
   -E, --encoding=ENCODING   புதிய தரவுக் களன்களுக்கு இயல்பான என்கோடிங்களை  அமைக்கவும்
  -L DIRECTORY               உள்ளீட்டு கோப்புகளை எங்கே  கண்டெடுப்பது
   -T, --text-search-config=CFG
   -U, --username=NAME       தரவுக் கள முதன்மைப் பயனரின் பெயர்
   -V, --version             வெளியீட்டுத் தகவலைக் காட்டியப் பின் வெளிவருக
   -W, --pwprompt            புதிய முதன்மைப் பயனருக்கான கடவுச் சொல்லைக் கோரவும்
   -X, --xlogdir=XLOGDIR     பரிமாற்றப் பதிவுக்கான அடைவின் இருப்பு
   -d, --debug               வழு ஆய்வறிக்கைகளை  அதிகமாக கொணரவும்.
   -n, --noclean             வழுக்களுக்குப் பிறகு துடைக்க வேண்டாம்.
  -s, --show                 உள் அமைப்புகளைக் காட்டுக
  [-D, --pgdata=]DATADIR     தரவுக் கள கூட்டமைப்பிற்கான இருப்பு
 %s போஸ்ட்க்ரெஸிச் தரவு கள கூட்டத்தை துவக்கும். 
 
 %s: "%s:" வழங்கியின் என்கோடிங் பெயர் செல்லாதது
 %s: கடவுச் சொல்லுக்கான கோப்பை உருவாக்க இயலவில்லை. இவ்வழுவினை தெரிவிக்கவும்.
 %s: மூலவராக இயக்க இயலாது
 வழங்கியின் பணிகளுக்கு உரிமையுள்ள 
 பயனராக (சலுகையற்ற) நுழையவும் (உ.ம்., "su" பயன்படுத்துவது).
 %s: "%s": அடைவினை அணுக இயலவில்லை %s
 %s: "%s": %s கோப்பினை அணுக இயலவில்லை
 தாங்கள் பழுதடைந்த நிறுவலை கொண்டிருக்கவேண்டும் அல்லது
  துவக்கத் தேர்வு -L ஆக உள்ள தவறான அடைவினை இனங்கண்டிருக்க வேண்டும்.
 %s: "%s": %sஅடைவிற்கான அனுமதிகளை மாற்ற இயலவில்லை
 %s: அடைவினை உருவாக்க இயலவில்லை "%s":%s
 %s: இணைப்பு மாதிரிகளை உருவாக்க இயலவில்லை %s": %s
 %s: ஏற்க உகந்த சிறிய வகை சரத்தை கண்டெடுக்க இயலவில்லை
 %s: ஆணையை நிறைவேற்ற இயலவில்லை "%s": %s
 %s: அகத்திற்கு தகுந்த என்கோடிங் வகையை  கண்டுபிடிக்க இயலவில்லை "%s"
 %s: தக்கதொரு உரை  தேடல் வடிவமைப்பினை அகத்திற்காக கண்டெடுக்க இயலவில்லை "%s"
 %s: "%s" கோப்பினை வாசிக்கும் பொருட்டுத் திறக்க இயலவில்லை: %s
 %s: "%s" கோப்பினை இயற்றும் பொருட்டு திறக்க இயலவில்லை: %s
 %s: கோப்பிலிருந்து கடவுச் சொல்லினை  வாசிக்க இயலவில்லை "%s": %s
 %s: கோப்பினை  இயற்ற இயலவில்லை "%s": %s
 %s: பயனரின் கோரிக்கைக்கு இணங்க தரவு அடைவு "%s" அகற்றப் படவில்லை
 %s: அடைவு "%s" இருந்தாலும்  காலியாக  இல்லை
 தாங்கள் புதிய தரவுக் கள அமைப்பினை  உருவாக்க நினைத்தால், ஒன்று அடைவினை அகற்றவோ அல்லது காலியோ
 செய்யவும் "%s" அல்லது %s
 னை "%s" மதிப்பினைத் தவிர வேறேதாவது கொடுத்து இயக்கவும்.
 %s: அடைவு "%s" உள்ளது ஆனால் காலியாக இல்லை
 பரிமாற்றப் பதிவினை  அவ்விடத்தே  காக்க விரும்பிடின் ஒன்று
 அடைவினை  அகற்றவும் அல்லது காலி செய்யவும் "%s".
 %s: தரவு அடைவில் இருப்பனவற்றை  அகற்ற இயலவில்லை
 %s: பரிமாற்றப் பதிவு அடைவின் இருப்புக்களை அகற்ற இயலவில்லை
 %s: தரவின் அடைவினை அகற்ற இயவில்லை
 %s: பரிமாற்றப் பதிவு அடைவினை அகற்ற இயலவில்லை
 %s: "%s" கோப்பு இல்லை
 அதாவது தாங்கள் பழுதடைந்த நிறுவலை கொண்டிருக்கிறீர்கள் அல்லது
 துவக்கத் தேர்வு -L ஆக உள்ள தவறான அடைவினை இனங்கண்டுள்ளீர்கள். 
 %s: "%s" கோப்பு வழக்கதில் உள்ளது அல்ல.  தாங்கள் பழுதடைந்த நிறுவலை கொண்டிருக்கவேண்டும் அல்லது
  துவக்கத் தேர்வு -L ஆக உள்ள தவறான அடைவினை இனங்கண்டிருக்க வேண்டும்.
 %s: "%s" உள்ளீட்டுக் கோப்பு போஸ்ட்கிரெஸுக்கு சொந்தமானது அல்ல %s
 தங்கள் நிறுவலை  சரி பார்க்கவும் அல்லது -L தேர்வினைப் பயன்படுத்தி சரியானப் பாதையினைத் தரவும். 
 %s: உள்ளீட்டுக் கோப்பின் இருப்பு முழுமையான பாதையினைக் கொண்டிருத்தல் வேண்டும்
 %s: செல்லாத அகப் பெயர் "%s"
 %s அனுமதியினை செயல்படுத்த முதன்மைப் பயனருக்கானக் கடவுச் சொல்லொன்றை %s: தருவது அவசியம்.
 %s: எந்தவொரு தரவு அடைவும் கொடுக்கப் படவில்லை
 இத் தரவுக் கள அமைப்பின்
தரவுகள் உறையும் இடத்தினைத் தாங்கள் இனங்காண வேண்டும். துவக்கத் தேர்வு -D யின் துணைக் கொண்டோ அல்லது
 பணிச்சூழலின் மாறி PGDATA வினைக் கொண்டோ இதனைச் செய்யவும்.
 %s: நினைவில் இல்லை
 %s: மேலெழும்பு கடவுச்சொல்லும் கடவுச் சொல்லுக்கான கோப்பையும் ஒரு சேர வழங்க இயலாது
 %s: தரவு அடைவில் இருப்பவை அகற்றப்படுகின்றன "%s"
 %s: பரிமாற்றப் பதிவு அடைவின் இருப்புக்கள் அகற்றப் படுகின்றன "%s"
 %s: தரவின் அடைவு அகற்றப் படுகின்றது "%s"
 %s: பரிமாற்றப் பதிவு அடைவு அகற்றப் படுகின்றது "%s"
 இத் தளத்தில் இணைப்பு மாதிரிகள் ஆதரிக்கப் படுவதில்லை %s: %s: முனைய-வரி மதிப்புகள் மிக அதிகமாக உள்ளன (முதலாவது "%s")
 %s: பயனரின் கோரிக்கைக்கு இணங்க பரிமாற்றப் பதிவு அடைவு "%s" அகற்றப் படவில்லை
 %s: இனங்காண இயலாத சோதனை முறை "%s"
 %s: எச்சரிக்கை: என்கோடிங் முரண்படுகிறது
 %s: எச்சரிக்கை: கொடுக்கப் பட்ட உரைத் தேடல் வடிவமைப்பு "%s" அகத்தோடு பொருந்தாது போகலாம்"%s"
 %s: எச்சரிக்கை: அகத்தின் உரைத் தேடலுக்குத் தகுந்த வடிவமைப்பு "%s" தெரியவில்லை
 மீண்டும் பதியவும்: புதிய முதன்மைப் பயனர் கடவுச் சொல்லை பதியவும்: கடவுச் சொற்கள் பொருந்தவில்லை.
 %s னை -E தேர்வுடன் மீண்டும் இயக்குக
 வழுஆய்வு முறையில் இயங்கிக் கொண்டிருக்கின்றது. 
 துடை தவிர் முறையில் இயங்கிக் கொண்டிருக்கின்றது. வழுக்கள் களையப் படாது.
 தரவுக் கள கூட்டம் %s அகத்துடன் துவக்கப் படும். 
 தரவுக் கள கூட்டமைப்பு கீழ்காணும் அகங்களைக் கொண்டு துவக்கப் படும்
COLLATE:  %s
  CTYPE:    %s
  MESSAGES: %s
  MONETARY: %s
  NUMERIC:  %s
  TIME:     %s
 தரவுக் களத்தின் இயல்பிருப்பு என்கோடிங் %s ஆக அமைக்கப் பட்டுள்ளது. 
 இயல்பாக அமையும் உரைத் தேடல் வடிவமைப்பு "%s" ஆக அமைக்கப் படும்.
 தாங்கள் தேர்வு செய்த என்கோடிங் வகையும் (%s) தேர்வு செய்யப் பட்ட 
அகத்தின் என்கோடிங் வகையும் (%s) பொருந்தவில்லை. இது
 சரங்களின் மீது பணிபுரியும் செயற்பாடுகளை பாதிக்கும். இதனைக்
 களைய, %sனை என்கோடிங்  வகையைக் கொடுக்காதவாறோ
அல்லது பொருந்தக் கூடிய ஒன்றைக் கொடுத்தோ  மீள இயக்கவும்.
 இத் தரவுக் கள அமைப்பின் கோப்புகளின் உரிமையாளர் "%s".
 வழங்கியின் பணிகளுக்கும் இவரே  உரிமையாளராக இருத்தல் வேண்டும்.

 %s லுக்கு "postgres" நிரல் தேவைப்படுகிறது. 
ஆனால் அதே அடைவில "%s" காணக்கிடைக்கவில்லை.
தங்களின் நிறுவலைச் சரிபார்க்கவும்.
 "postgres" நிரல் "%s"
 ஆல் கண்டுபிடிக்கப்பட்டது.  ஆனால் %s னை  ஒத்த வெளியீடு அல்ல.
 தங்கள் நிறுவலைச் சரி பார்க்கவும். 
 மேலும் விவரங்களுக்கு "%s --help" முயற்சிக்கவும்
 பயன்பாடு:
 சமிக்ஞை பெறப் பட்டுள்ளது
 துணைப் பணி வெளியேற்றக் குறியீடு %d யுடன் வெளிவந்தது அடையாளங்காண இயலாத நிலை %d யால் துணைப் பணி வெளிவந்தது 0x%X விதிவிலக்கால் துணைப் பணி தடைப் பட்டது சமிக்ஞை %d ஆல் துணைப் பணி தடைப்பட்டது சமிக்ஞை %s ஆல் துணைப் பணி தடைப் பட்டது வார்ப்பு1  போஸ்ட்க்ரெஸுக்கு நகலெடுக்கப் படுகின்றது வார்ப்பு1  வார்ப்பு0 க்கு நகலெடுக்கப் படுகின்றது ... அடைவை "%s" ஆக மாற்ற இயலவில்லை செயற்படுத்த "%s" னை கண்டுபிடிக்க இயலவில்லை தற்போதைய அடைவினை இனங்காண இயலவில்லை: %s "%s": %s அடைவைத் திறக்க இயலவில்லை
 "%s" இருமத்தை  வாசிக்க இயலவில்லை "%s": %s அடைவை வாசிக்க இயலவில்லை
 "%s" இணைப்பு மாதிரிகளை வாசிக்க இயலவில்லை "%s": %s அடைவையோக் கோப்பினையோ அகற்ற இயலவில்லை
 "%s": %s க்கான இணைப்பினை அமைக்க இயலவில்லை
 துணைப் பணிக்குள் இயற்ற இயலவில்லை: %s
 வடிவமைப்புக் கோப்புகள் உருவாக்கப் படுகின்றன ... மாற்றங்கள் உருவாக்கப் படுகின்றன... அகராதிகள் உருவாக்கப் படுகின்றன... %s அடைவு உருவாக்கப் படுகிறது... தகவல் ஸ்கீமா  உருவாக்கப் படுகின்றாது ... துணையடைவுகள் உருவாக்கப் படுகின்றன ... அமைப்பு பார்வைகள் உருவாக்கப் படுகின்றன ... %s/base/1 ல் வார்ப்பு1  தரவுக் களன் உருவாக்கப் படுகிறது ... இருக்கக் கூடிய அடைவுகளில் உரிமங்கள் சரிசெய்யப் படுகின்றன %s ... சார்புடைமைகள் துவக்கப்படுகின்றன ... pg_authid துவக்கப் படுகின்றது ... செல்லாத இருமம் "%s" வன் பொருட்களின் விவரங்கள் ஏற்றப்படுகின்றன... சரி
 நினைவை  மீறி
 இயல்பிருப்பாக இருக்க வேண்டிய max_connections தேர்வு செய்யப் படுகின்றது ... இயல்பிருப்பு shared_buffers/max_fsm_pages தேர்வு செய்யப் படுகின்றது ... கடவுச் சொல் அமைக்கப்படுகின்றது... உருவாக்கப் பட்டிருக்கும் பொருட்களுக்கு சலுகைகள்  அமைக்கப் படுகின்றன ... தரவுக் களத்தின் வார்ப்பு காலியாக்கப் படுகின்றது ... 
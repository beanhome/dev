��    M      �  g   �      �  9   �  -   �  ,   �  8     3   W  0   �  *   �  N   �  /   6  N   f     �  *   �  +    	     ,	  !   H	  +   j	  )   �	  #   �	  &   �	  -   
  !   9
  !   [
  +   }
  "   �
  (   �
     �
  S   
     ^     ~  #   �  #   �  #   �  #     #   ,  #   P  \   t  +   �  0   �      .  @   O  D   �  &   �  -   �     *  )   :  )   d  )   �  )   �  )   �  )     )   6  )   `     �  V   �  )   �  )   (  )   R  )   |  )   �  ,   �  )   �  )   '  )   Q  )   {  )   �  )   �  	   �  �        �  &   �  !   �  )     -   .     \     s  )   �  �  �  �   G  y   A  x   �  �   4  y   �  �   7  `   �  �     y     �   �  <   Z  v   �  {     B   �  8   �  \     a   c  R   �  X     �   q  <     Y   B  g   �  9      X   >      �   �   �   G   4!  E   |!  \   �!  \   "  S   |"  \   �"  h   -#  \   �#  ]  �#  y   Q%  y   �%  s   E&  �   �&  �   �'  p   I(  v   �(  "   1)  }   T)  \   �)  Q   /*  F   �*  f   �*  M   /+  �   }+  ~   ,  T   �,    �,  )   �-  )   	.  N   3.  N   �.  N   �.  Q    /  N   r/  �   �/  [   Y0  c   �0  `   1  M   z1     �1  �  �1  N   ~3  g   �3  .   54  5   d4  �   �4  %   #5  ,   I5  C   v5     &   ;         L         *          !   =          #       B                -   (   G   0   :          )   J          8       M   E           1   >   	       <   I             2   
      +   C           F              5   6          ,            A             @   9                    K   /              3   .   ?       7          D   $              H   '      "   4   %            
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
 %s: invalid LC_COLLATE setting
 %s: invalid LC_CTYPE setting
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
 First log file ID for new XLOG:       %u
 First log file segment for new XLOG:  %u
 Guessed pg_control values:

 If you are sure the data directory path is correct, execute
  touch %s
and try again.
 LC_COLLATE:                           %s
 LC_CTYPE:                             %s
 Latest checkpoint's NextMultiOffset:  %u
 Latest checkpoint's NextMultiXactId:  %u
 Latest checkpoint's NextOID:          %u
 Latest checkpoint's NextXID:          %u/%u
 Latest checkpoint's TimeLineID:       %u
 Maximum columns in an index:          %u
 Maximum data alignment:               %u
 Maximum length of identifiers:        %u
 Maximum length of locale name:        %u
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
 Project-Id-Version: pg_resetxlog
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2007-09-22 03:20-0300
PO-Revision-Date: 2007-11-11 09:38+0530
Last-Translator: ஆமாச்சு <amachu@ubuntu.com>
Language-Team: தமிழ் <https://lists.ubuntu.com/mailman/listinfo/ubuntu-l10n-tam>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: KBabel 1.11.4
 
இம்மதிப்புகள் ஏற்புடையவையாகத் தோன்றிடின், கட்டாயம் மீளமைக்காயம்மைக்க -f பயன்படுத்தவும்ம்.
 
வழுக்களை <pgsql-bugs@postgresql.org> க்குத் தெரியப் படுத்துக.
   --help          இவ்வுதவியினைக் காட்டியபின் வெளிவருக
   --version       வெளியீட்டுத் தகவலை வெளியிட்டபின் வெளிவருக
   -O OFFSET       அடுத்த பல்பரிமாற்ற ஆபுஃசெட்டை அமைக்க
   -e XIDEPOCH     அடுத்த பரிமாற்ற குறியீடு எபோக்கினை அமைக்க
   -f              புதுப்பித்தலை வலிந்து செய்க
   -l TLI,FILE,SEG புதிய பரிமாற்றப் பதிவிற்கான குறைந்த பட்ச WAL துவக்க இருப்பிடத்தை வலிந்து செய்க.
   -m XID          அடுத்த பல்பரிமாற்ற குறியீட்டை அமைக்க
   -n              புதுப்பிக்க வேண்டாம், கொணரப்பட்ட நிர்வாக மதிப்புகளை காட்டுக (சோதனைக்காக)
   -o OID          அடுத்த OID அமைக்க
   -x XID          அடுத்த பரிமாற்றக் குறியீட்டை அமைக்க
 %s போஸ்டுகிரெஸ் பரிமாற்ற பதிவை மீட்டமைக்கும்.

 %s: OID (-o) 0 வாக இருத்தல் ஆகாது
 %s: "root" ஆல் இயக்க இயலாது
 %s: அடைவினை "%s": க்கு மாற்ற இயலவில்லை %s
 %s: pg_control கோப்பினை உருவாக்க இயலவில்லை: %s
 %s: "%s" கோப்பினை அகற்ற இயலவில்லை: %s
 %s: "%s" அடைவினைத் திறக்க இயலவில்லை: %s
 %s: "%s" கோப்பினை வாசிக்கும் பொருட்டுத் திறக்க இயலவில்லை: %s
 %s: "%s" திறக்க இயலவில்லை: %s
 %s: "%s": கோப்பினை வாசிக்க இயலவில்லை: %s
 %s: "%s" அடைவிலிருந்து வாசிக்க இயலவில்லை: %s
 %s: "%s" இயற்ற இயலவில்லை: %s
 %s: pg_control கோப்பினை இயற்ற இயலவில்லை: %s
 %s: fsync பிழை: %s
 %s: உட்பிழை -- sizeof(ControlFileData) மிக அதிகமாக உள்ளது ... fix PG_CONTROL_SIZE
 %s: செல்லத்தகாத LC_COLLATE அமைப்பு
 %s: செல்லத்தகாத LC_CTYPE அமைப்பு
 %s: தேர்வு -O க்குப் பொருந்தாத துப்பு
 %s: தேர்வு -e க்குப் பொருந்தாத துப்பு
 %s: தேரவு -l க்கு பொருந்தாத துப்பு
 %s: தேர்வு -m க்குப் பொருந்தாத துப்பு
 %s: தேர்வு -o வுக்குப் பொருந்தாதத் துப்பு
 %s: தேர்வு -x க்குப் பொருந்தாத துப்பு
 %s: சாற்றுக் கோப்பு "%s" இருக்கிறது
வழங்கி இயக்கத்தில் உள்ளதா?  இல்லையெனில், சாற்றுக் கோப்பினை அகற்றிவிட்டு மீண்டும் முயற்சிக்கவும்.
 %s: பல்பரிமாற்ற குறியீடு (-m) 0 வாக இருத்தல் ஆகாது
 %s: பல்பரிமாற்ற ஆபுஃசெட்(-O) -1 ஆக இருக்கக் கூடாது
 %s: குறிப்பிடப்பட்ட அடைவில் தரவெதுவுமில்லை
 %s: pg_control இருந்தாலும் செல்லாத CRC கொண்டுள்ளது; எச்சரிக்கையுடன் அடியெடுக்கவும்
 %s: pg_control உடையப்பட்டோ அல்லது அறியப்படாத வெளியீடாகவோ உள்ளது; தவிர்க்கின்றோம்
 %s: (-x) பரிமாற்ற குறியீடு 0 வாக இருத்தல் ஆகாது
 %s: பரிமாற்றக் குறியீடு epoch (-e) -1 ஆக இருத்தலாகாது
 64-ஒரும எண்கள் பெரிய தொடர்புடைய பகுதியொன்றிலுள்ள பாகங்கள்: %u
 பிரதி WAL பகுதிக்கான பைட்கள்:                %u
 காடலாக் வெளியீட்டு எண்:               %u
 தரவுக் கள பாக அளவு:                  %u
 தரவுக் கள அமைப்பு இனங்காட்டி்டி:           %s
 தேதி /நேர வகை சேமிப்பு:               %s
 புதிய XLOG க்கான முதற் பதிவுக் கோப்பின் குறியீடு:       %u
 புதிய XLOG க்கான முதற் பதிவுக் கோப்பின் பகுதி:       %u
 கணிக்கப்பெற்ற pg_control மதிப்புகள்:

 தரவு அடைவின் பாதை சரியென உறுதியாக இருந்தால், செயற்படுத்துக
  தொடுக %s
மற்றும் மீண்டும் முயற்சிக்க.
 LC_COLLATE:                           %s
 LC_CTYPE:                             %s
 அண்மைய சோதனை மையத்து NextMultiOffset:  %u
 அண்மைய சோதனை மையத்து NextMultiXactId:  %u
 அண்மைய சோதனை மையத்து NextOID:          %u
 அண்மைய சோதனை மையத்து NextXID:          %u/%u
 அண்மைய சோதனை மையத்து TimeLineID:       %u
 அட்டவணையொன்றில் இருக்கத் தக்க அதிக பட்ச நெடுவரிசை:          %u
 அதிகப் பட்ச தரவு ஒழுங்கீடு:               %u
 இனங்காட்டிகளின் அதிக பட்ச நீளம்:        %u
 அகப் பெயருக்கான அதிகபட்ச நீளம்:        %u
 TOAST சங்கின் அதிகபட்ச அளவு:        %u
 தேர்வுகள்:
 தரவுக் கள வழங்கி முறையாக அணைக்கப் படவில்லை.
பரிமாற்ற பதிவை மீளமைப்பது தரவினை கெடுத்துவிடலாம்.
செய்து தான் ஆக வேண்டுமெனின் -f பயன்படுத்தி மீளமைக்கவும்.
 பரிமாற்றப் பதிவினை மீளமைக்க
 மேலும் தகவலுக்கு "%s --help" முயற்சிக்கவும்.
 பயனளவு:
  %s [OPTION]... DATADIR

 WAL பாக அளவு:                       %u
 போஸ்டுகிரெஸ் முதன்மைப் பயனராக %s னை இயக்க வேண்டும்.
 புள்ளி எண்கள் pg_control மதிப்புகள்:

 pg_control வெளியீட்டு எண்:            %u
 
��    j      l  �   �      	      	     2	  &   D	     k	     �	  -   �	     �	     �	  r   
     ~
  F   �
  A   �
     '  7   B  !   z  3   �  ?   �  ?     H   P  D   �  E   �  ?   $  >   d  9   �  B   �  <      z   ]  0   �  F   	  8   P  2   �  O   �  7        D     K  �   T  !   �  C     y   K  C   �  D   	  4   N  A   �  *   �  /   �  %      /   F  #   v     �  3   �  0   �  ,     .   J  3   y  -   �  0   �  5     "   B  $   e  J   �     �     �  3     0   <     m     �  !   �  $   �      �  -     4   5  %   j  $   �  "   �  F   �  F        f  7   z  )   �  q   �  f   N  %   �  &   �          
  &   )  0   P  .   �  )   �  )   �  "         '  (   H     q  !   �     �     �     �     �               "     2  "   J     m  �  �  �   b  :   �  y   %     �  k         �   =   !  '   I!  �   q!  4   �!  c   /"  T   �"  /   �"  N   #  X   g#  �   �#  �   C$  k   �$  �   H%  �   �%  �   �&  �   ~'  �   (  `   �(  �   !)  �   �)  �   n*  Z   \+  �   �+  z   _,  o   �,    J-  �   a.     �.     /    5/  0   ;1    l1    �2  �   �3  �   �4  �   V5  �   6  *   �6  ~   7  _   �7  m   �7  \   Q8  T   �8  �   9  z   �9  g   :  �   l:  �   �:  �   �;  o   3<  �   �<  j   &=  _   �=  �   �=  a   �>  R   ?  �   b?  �   @  9   �@  :   �@  h   3A  t   �A  a   B  �   sB  p   C  L   |C  m   �C  j   7D  �   �D  �   }E  :   F  �   ZF  �   G  ?  �G    I  v   J  h   �J     �J  �   K  t   �K  s   L  i   �L  ]   �L  ]   VM  S   �M  }   N  j   �N  U   �N  e   GO  T   �O  -   P  H   0P  [   yP  2   �P  E   Q  )   NQ  p   xQ  �   �Q  �   rR               4      5         W                     '       8   -   "          c           &   Q   Y   e   J   ;   [   +      A   C   %       O   G          ,   $              h   d   6       R   9                    F   @   M   3      B           Z   )       X   I      S       i   b       ^   	   E   ?       
   !          <      2                       T   f      U                      K       0   #      >   1       .   a   \   N             j   7   *   =           `   g                 ]             P   L       D   V           _   /       (   H   :           
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
   %s kill    SIGNALNAME PID
   %s register   [-N SERVICENAME] [-U USERNAME] [-P PASSWORD] [-D DATADIR]
                    [-w] [-o "OPTIONS"]
   %s reload  [-D DATADIR] [-s]
   %s restart [-w] [-D DATADIR] [-s] [-m SHUTDOWN-MODE] [-o "OPTIONS"]
   %s start   [-w] [-D DATADIR] [-s] [-l FILENAME] [-o "OPTIONS"]
   %s status  [-D DATADIR]
   %s stop    [-W] [-D DATADIR] [-s] [-m SHUTDOWN-MODE]
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
                         (PostgreSQL server executable)
   -p PATH-TO-POSTGRES    normally not necessary
   -s, --silent           only print errors, no informational messages
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
 %s: cannot set core size, disallowed by hard limit.
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
 The program "postgres" is needed by %s but was not found in the
same directory as "%s".
Check your installation.
 The program "postgres" was found by "%s"
but was not the same version as %s.
Check your installation.
 Timed out waiting for server startup
 Try "%s --help" for more information.
 Usage:
 Waiting for server startup...
 child process exited with exit code %d child process exited with unrecognized status %d child process was terminated by exception 0x%X child process was terminated by signal %d child process was terminated by signal %s could not change directory to "%s" could not find a "%s" to execute could not identify current directory: %s could not read binary "%s" could not read symbolic link "%s" could not start server
 invalid binary "%s" server shutting down
 server signaled
 server started
 server starting
 server stopped
 starting server anyway
 waiting for server to shut down... waiting for server to start... Project-Id-Version: pg_ctl
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2007-09-22 03:19-0300
PO-Revision-Date: 2007-11-01 12:53+0530
Last-Translator: ஸ்ரீராமதாஸ் <shriramadhas@gmail.com>
Language-Team: தமிழ் <ubuntu-l10n-tam@lists.ubuntu.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: KBabel 1.11.4
X-Poedit-Language: Tamil
X-Poedit-Country: ITALY
X-Poedit-SourceCharset: utf-8
 
முடிப்பதற்கு அனுமதிக்கப்படும் சமிக்ஞை பெயர்கள்:
 
பொதுவானத் தேர்வுகள்:
 
பதிவு செய்ய மற்றும் விலகுவதற்கான தேர்வுகள்:
 
துவங்க அல்லது மீளத் துவங்குவதற்கான தேர்வுகள்:
 
துவக்க மீளத்துவக்குவதற்கான தேர்வுகள்:
 
வழுக்களை <pgsql-bugs@postgresql.org> க்குத் தெரியப் படுத்தவும்.
 
நிறுத்தும் முறைகளாவன:
   %s கொல்க    SIGNALNAME PID
   %s பதிவுசெய்க   [-N SERVICENAME] [-U USERNAME] [-P PASSWORD] [-D DATADIR]
                    [-w] [-o "OPTIONS"]
   %s மீளேற்றுக  [-D DATADIR] [-s]
   %s மீளத்துவக்கு [-w] [-D DATADIR] [-s] [-m SHUTDOWN-MODE] [-o "OPTIONS"]
   %s துவக்குக   [-w] [-D DATADIR] [-s] [-l FILENAME] [-o "OPTIONS"]
   %s மீளேற்றுக  [-D DATADIR]
   %s நிறுத்துக    [-W] [-D DATADIR] [-s] [-m SHUTDOWN-MODE]
   %s பதிவைத் திரும்பப் பெறுக [-N SERVICENAME]
   --help                 இவ்வுதவியினைக் காட்டிவிட்டு வெளிவருக
   --version              வெளியீட்டுத் தகவலை வெளியிட்டுவிட்டு வெளிவருக
   -D, --pgdata DATADIR   தரவுக் களன் காக்கப்படும் இடம்
   -N SERVICENAME  போஸ்ட்கிரெஸ் வழங்கியினை பதிவு செய்வதற்கானச் சேவைப் பெயர்
   -P PASSWORD     போஸ்ட்கிரெஸ் வழங்கியினை பதிவு செய்வதற்கான கணக்கின் கடவுச் சொல்
   -U USERNAME     போஸ்ட்கிரெஸ் வழங்கியினை பதிவு செய்வதற்கான கணக்கின் பயனர் பெயர்
   -w                     செயல் பூரத்தியாகும் வரைக் காத்திருக்காதே
   -c, --core-files       மூலக் கோப்புகளை உருவாக்க போஸ்டகிரெஸ்ஸினை அனுமதிக்கவும்
   -c, --core-files       இக்கட்டமைப்புக்கு ஒவ்வாத
   -l, --log FILENAME     FILENAME ற்கு வழங்கியின் பதிவினை இயற்றவும் (அல்லது சேர்க்கவும்)
   -m SHUTDOWN-MODE   "விவேகமாக", "வேகமாக", அல்லது "உடனடியாக" இருக்கலாம்
   -o OPTIONS             போஸ்டகிரெஸுக்கு அனுப்ப உகந்த முனைய தேர்வுகள்
                         (வழங்கியில் இயக்க வல்ல)
   -p PATH-TO-POSTGRES    சாதாரணமாகத் தேவையில்லை
   -s, --silent           அச்சுசார் பிழைகள் மாத்திரம், தகவல் குறிப்புகள் அல்ல
   -w                     செயல் பூரத்தியாகும் வரைக் காத்திரு
   வேக        வெளிவரவு, முறையான நிறுத்தத் துடன்
   உடனடி   வெளிவரவு முழுமையான நிறுத்தமில்லாது; மீளத்துவங்கும் போது மீட்பதறகான முயற்சி மேற்கொள்ளப்படும்
   விவேக       வெளிவரவு. அனைத்து வாங்கிகளும் தொடர்பறிந்த பிறகு.
  முடிந்தது
  தவறியது
 %s வடிவமைப்புக் கோப்புகளை துவக்க, நிறுத்த, மீளத்துவங்க, மீளேற்றுவதற்கானப் பயனபாடு
போஸ்ட்கிரெஸ் வழங்கியொன்றின் நிலையினை அறியப் படுத்தவும் அல்லது போஸ்டகிரெஸ் பணியொன்றுக்கு சமிக்ஞைத் தரவும்.

 %s: PID கோப்பு "%s" இல்லை
 %s: மற்றொரு வழங்கி இயங்கிக் கொண்டிருக்கலாம்; ஆயினும் வழங்கியினைத் துவக்க முயந்சி மேற்கொள்ளப் படுகிறது
 %s: முதன்மைப் பயனராக இயக்க இயலாது
 வழங்கியின் பணிகளுக்கு உரிமையுள்ள (சலுகையற்ற) பயனராக (உ.ம்., "su")
நுழையவும்.
 %s: வழங்கியை மீளத் துவங்க இயலவில்லை; தனிப் பயனருக்கான வழங்கி இயங்கிக் கொண்டிருக்கிறது(PID: %ld)
 %s: வழங்கியை மீளத் துவங்க இயலவில்லை; தனிப் பயனருக்கான வழங்கி இயங்குகிறது (PID: %ld)
 %s: மைய அளவினை அமைக்க இயலவில்லை, வலிய வரையறையால் அனுமதிக்க முடியவில்லை.
 %s: வழங்கியினை நிறுத்த இயலவில்லை; தனிப் பயனருக்கான வழங்கி இயங்குகிறது (PID: %ld)
 %s: could not find own program executable
 %s: இயக்க வல்ல போஸ்ட்கிரெஸ் நிரல் கிடைக்கவில்லை
 %s: PID கோப்பினைத் திறக்க இயலவில்லை "%s": %s
 %s: "%s": சேவையைத் துவக்க இயலவில்லை. வழு குறி %d
 %s: சேவை மேளாலரைத் திறக்க இயலவில்லை
 %s: கோப்பினை வாசிக்க இயலவில்லை "%s"
 %s: "%s" சேவையைப் பதிவுச் செய்ய இயலவில்லை. வழுக் குறி %d
 %s: மீளேற்ற சமிக்ஞையைத் அனுப்ப இயலவில்லை (PID: %ld): %s
 %s: சமிக்ஞையினை அனுப்ப இயலவில்லை %d (PID: %ld): %s
 %s: நிறுத்துவதற்கான சமிக்ஞையை அனுப்ப இயலவில்லை (PID: %ld): %s
 %s: வழங்கியினை துவங்க இயலவில்லை
பதிவின் வெளியீட்டை ஆராயவும்.
 %s: வழங்கியினைத் துவக்க இயலவில்லை: வெளியேற்றக் குறியீடு %d
 %s: "%s": சேவையைத் துவக்க இயலவில்லை பிழை குறி %d
 %s: சேவையைத் திரும்பப் பெற இயலவில்லை "%s": பிழை குறி %d
 %s: PID கோப்பிலுள்ளத் தரவு பொருத்தமற்றது "%s"
 %s: முடி முறைக்கானத் துப்புகள் இல்லை
 %s: அமைவகற்று PGDATA சூழல் மாறியில் தரவுக் கள அடைவுக் குறிப்பிடப் படவில்லை
 %s: செயலெதுவும் குறிப்பிடப் படவில்லை
 %s: எந்த வழங்கியும் இயங்கவில்லை
 %s: வழங்கியின் பழைய செயல் (PID: %ld) பூர்த்தியானது போலத்தெரிகிறது
 %s: தேர்வுகள் கோப்பு "%s" கட்டாயம் ஒரு வரி மாத்திரமே கொண்டிருக்க வேண்டும்
 %s: நினைவுக்கு அப்பால்
 %s: வழங்கி நிற்க வில்லை
 %s: வழங்கி இயங்கிக்கொண்டிருக்கிறது (PID: %ld)
 %s: சேவை "%s" ஏறகனவே பதிவுச் செய்யப் பட்டுள்ளது
 %s: "%s" சேவைப் பதிவுச் செய்யப் படவில்லை
 %s: தனிப்பயனருக்கான வழங்கி இயங்கிக் கொண்டிருக்கிறது (PID: %ld)
 %s: ஏகப் பட்ட முனையத் துப்புகள் (முதலாவது "%s")
 %s: இனங்காண இயலாத செயல் முறை "%s"
 %s: இனங்கண்டுகொள்ள இயலாத நிறுத்தற் முறை "%s"
 %s: இனங்கண்டுகொள்ள இயலாத சமிக்ஞை பெயர் "%s"
 (இயல்பிருப்பு நிறுத்துவதற்காகக் காத்திருப்பது. துவக்க அல்லது மீளத்துவங்க அல்ல)

 -D தேர்வினை விட்டுவிட்டால், சூழல் மாறி PGDATA பயன்படுத்தப்படும்.
 வழங்கி பணி புரிகிறதா?
 தனிப் பயனருக்கான வழங்கியினை நிறுத்திவிட்டு மீண்டும் முயற்சிக்கவும்.
 வழங்கித் துவங்கிற்று இணைப்புக்களைப் பெற்றுக் கொண்டிருக்கிறது
 %s க்கு "postgres" நிரல் அவசியம் தேவைப் படுகிறது ஆயினும் "%s" அடைவினுள் 
 அது கிடைக்கவில்லை .
தங்களின் நிறுவலைச் சரி பாார்க்கவும்.
 "%s" ஆல் "postgres" நிரல் கண்டெடுக்கப் பட்டது 
ஆனால் %s னை ஒத்த வெளியீடு அல்ல.
தங்களின் நிறுவலைச் சரி பார்க்கவும்.
 வழங்கி துவங்கக் காத்திருந்து காலாவதியானது
 மேலும் தகவலறிய "%s --help" முயற்சி செய்யவும்.
 பயன்பாடு:
 வழங்கித் துவங்குவதற்காகக் காத்திருக்கப் படுகிறது...
 சேய் பணி வெளிவரவுக் குறி %d யுடன் வெளுவந்தது சேய் பணி இனந்தெரியா %d நிலையால் தடைப்பட்டது சேய் பணி விதிவிவக்கு 0x%X ஆல் தடைப்பட்டது சேய் பணி %d சமிக்ஞையால் தடைப்பட்டது சேய் பணி %s சமிக்ஞையால் தடைப்பட்டது அடைவினை "%s" க்கு மாற்ற இயலவில்லை இயக்கும்பொருட்டு "%s" னைக் கண்டெடுக்க இயலவில்லை தற்போதைய அடைவினைக் இனங்கான இயலவில்லை: %s இருமத்தினை வாசிக்க இயலவில்லை "%s" மாதிரி இணைப்பினை வாசிக்க இயலவில்லை "%s" வழங்கியினைத் துவங்க இயலவில்லை
 செல்லாத இருமம் "%s" வழங்கி நிறுத்தப் படுகிறது
 வழங்கிக்கு சமிக்ஞைத் தரப் பட்டது
 வழங்கி துவங்கியது
 வழங்கி துவங்கப் படுகிறது
 வழங்கி நின்றது
 எவ்வழியானும் வழங்கித் துவங்கப் படுகிறது
 வழங்கி நிற்கும் பொருட்டு காத்திருக்கப் படுகிறது... வழங்கியின் துவக்கத்திற்காகக் காத்திருக்கப்படுகிறது... 
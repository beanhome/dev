Þ    l      |     Ü      0	      1	     R	  &   d	     	     «	  -   Ê	     ø	     
  |   +
     ¨
  a   È
  K   *     v  A     !   Ó  3   õ  ?   )  ?   i  H   ©  D   ò  E   7  ?   }  >   ½  9   ü  B   6  <   y  z   ¶  0   1  F   b  >   ©  8   è  2   !  O   T  7   ¤     Ü     ã     ì  !   }  C     y   ã  C   ]  D   ¡  >   æ  A   %  *   g  /     %   Â  /   è  #        <  3   Z  0     ,   ¿  .   ì  3     -   O  0   }  5   ®  "   ä  $     J   ,     w       3   ª  0   Þ          "  !   A  $   c        -   ©  4   ×  %     $   2  "   W  F   z  F   Á       7     )   T  q   ~  f   ð  %   W  &   }     ¤  d   ¬       &   0  0   W  .     )   ·  )   á  "         .  (   O     x  !        µ     Í     á     ÷               )     9  "   Q     t  Ä    <   X       '   ©  4   Ñ  4      ,   ;      h   !         ¡      6!  n   V!  ]   Å!     #"  O   >"  %   "  :   ´"  >   ï"  V   .#  L   #  A   Ò#  >   $  H   S$  8   $  E   Õ$  F   %  <   b%     %  4   +&  Y   `&  A   º&  >   ü&  W   ;'  b   '  N   ö'     E(     N(  Ô   W(  $   ,)  T   Q)  ã   ¦)  l   *  _   ÷*  o   W+  K   Ç+  =   ,  @   Q,  *   ,  7   ½,  *   õ,  %    -  =   F-  9   -  5   ¾-  7   ô-  I   ,.  5   v.  =   ¬.  N   ê.  /   9/  7   i/  U   ¡/  5   ÷/  #   -0  ?   Q0  E   0     ×0  "   í0  '   1  2   81  1   k1  8   1  4   Ö1  &   2  !   22  $   T2  c   y2  J   Ý2     (3  @   H3  1   3  ½   »3     y4  6   5  *   P5     {5     5  2   6  8   D6  ?   }6  ;   ½6  4   ù6  =   .7  *   l7  *   7  )   Â7  -   ì7  *   8      E8  "   f8     8  +   ¡8     Í8     ß8     ú8  $   9  .   49  1   c9               5      6         Y                      (      9   .   #          e           '   R   [   W   K   <   ]   f      B   D   &       P   H          -   %              j   
   7       T   :                   G   A       4      C           \   *   c   Z   J                 d       `   	   F   @       !   "       ,   =      3       k               U   h      V                   S   L       1   $      ?   2       /      ^   O          N   l   8   +   >           b   i                 _             Q   M   g   E   X           a   0       )   I   ;           
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
                         (PostgreSQL server executable)
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
 waiting for server to shut down... waiting for server to start... Project-Id-Version: PostgreSQL 8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-09-09 16:34+0000
PO-Revision-Date: 2010-09-24 12:39-0400
Last-Translator: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
Language-Team: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 
ì¬ì©í  ì ìë ì¤ì§ì©(for kill) ìê·¸ë ì´ë¦:
 
ì¼ë° ìµìë¤:
 
ìë¹ì¤ ë±ë¡/ì ê±°ì© ìµìë¤:
 
start, restart ë ì¬ì©í  ì ìë ìµìë¤:
 
stop, restart ë ì¬ì© í  ì ìë ìµìë¤:
 
ì¤ë¥ë³´ê³ : <pgsql-bugs@postgresql.org>.
 
ì¤ì§ë°©ë² ì¤ëª:
   %s kill    ìê·¸ëì´ë¦ PID
   %s register   [-N ìë¹ì¤ ì´ë¦] [-U ì¬ì©ì ì´ë¦] [-P ìí¸] [-D ë°ì´í° ëë í°ë¦¬]
                    [-w] [-t ì´] [-o "ìµì"]
   %s reload  [-D DATADIR] [-s]
   %s restart [-w] [-t ì´] [-D ë°ì´í° ëë í°ë¦¬] [-s] [-m ì¤ì§ ëª¨ë]
                 [-o "ìµì"]
   %s start   [-w] [-t ì´] [-D ë°ì´í° ëë í°ë¦¬] [-s] [-l íì¼ ì´ë¦] [-o "ìµì"]
   %s status  [-D DATADIR]
   %s stop    [-W] [-t ì´] [-D ë°ì´í° ëë í°ë¦¬] [-s] [-m ì¤ì§ ëª¨ë]
   %s unregister [-N ìë¹ì¤ì´ë¦]
   --help                 ëìë§ì ë³´ì¬ì£¼ê³  ë§ì¹¨
   --version              ë²ì  ì ë³´ë¥¼ ë³´ì¬ì£¼ê³  ë§ì¹¨
   -D, --pgdata DATADIR   ë°ì´í°ë² ì´ì¤ ìë£ê° ì ì¥ëì´ìë ëë í°ë¦¬
   -N SERVICENAME  ìë¹ì¤ ëª©ë¡ì ë±ë¡ë  PostgreSQL ìë¹ì¤ ì´ë¦
   -P PASSWORD     ì´ ìë¹ì¤ë¥¼ ì¤íí  ì¬ì©ìì ìí¸
   -U USERNAME     ì´ ìë¹ì¤ë¥¼ ì¤íí  ì¬ì©ì ì´ë¦
   -W                     ììì´ ëë  ëê¹ì§ ê¸°ë¤ë¦¬ì§ ìì
   -c, --core-files       ì½ì´ ë¤í íì¼ì ë§ë¬
   -c, --core-files       ì´ íë«í¼ììë ì¬ì©í  ì ìì
   -l, --log íì¼ì´ë¦     ìë² ë¡ê·¸ë¥¼ ì´ íì¼ì ê¸°ë¡í¨
   -m ì¤ì§ë°©ë²   "smart", "fast", "immediate" ì¤ íë
   -o ìµìë¤              PostgreSQL ìë²íë¡ê·¸ë¨ì¸ postgres ì¤íí  ë
                         ì¬ì©í  ëªë ¹í ìµìë¤
   -p PATH-TO-POSTGRES    ë³´íµì íìì¹ ìì
   -s, --silent           ì¼ë°ì ì¸ ë©ìì§ë ë³´ì´ì§ ìê³ , ì¤ë¥ë§ ë³´ì¬ì¤
   -t SECS                -w ìµì ì¬ì© ì ëê¸° ìê°(ì´)
   -w                     ììì´ ëë  ëê¹ì§ ê¸°ë¤ë¦¼
   fast        í´ë¼ì´ì¸í¸ì ì°ê²°ì ê°ì ë¡ ëê³  ì ìì ì¼ë¡ ì¤ì§ ë¨
   immediate   ê·¸ë¥ ë¬´ì¡°ê±´ ì¤ì§í¨; ë¤ì ììí  ë ë³µêµ¬ ììì í  ìë ìì
   smart       ëª¨ë  í´ë¼ì´ì¸í¸ì ì°ê²°ì´ ëê¸°ê² ëë©´ ì¤ì§ ë¨
  ìë£
  ì¤í¨
 %s íë¡ê·¸ë¨ì PostgreSQL ìë¹ì¤ë¥¼ ìì, ì¤ì§, ì¬ìì, íê²½ì¤ì  ì¬ì ì©,
ìë² ìí ë³´ê¸°, ëë PostgreSQL íë¡ì¸ì¤ì í¹ì  ìê·¸ëì ë³´ë¼ ì ìë
íë¡ê·¸ë¨ìëë¤.

 %s: "%s" PID íì¼ì´ ììµëë¤
 %s: ë¤ë¥¸ ìë²ê° ê°ë ì¤ì¸ ê² ê°ì; ì´ì§¸ë  ìë² ê°ëì ìëí¨
 %s: rootë¡ ì´ íë¡ê·¸ë¨ì ì¤ííì§ ë§ì­ìì¤
ìì¤íê´ë¦¬ì ê¶íì´ ìë, ìë²íë¡ì¸ì¤ì ìì ì£¼ê° ë  ì¼ë° ì¬ì©ìë¡
ë¡ê·¸ì¸ í´ì("su", "runas" ê°ì ëªë ¹ ì´ì©) ì¤ííì­ìì¤.
 %s: ìë² íê²½ì¤ì ì ë¤ì ë¶ë¬ì¬ ì ìì; ë¨ì¼ ì¬ì©ì ìë²ê° ì¤í ì¤ì (PID: %ld)
 %s: ìë²ë¥¼ ë¤ì ìì í  ì ìì; ë¨ì¼ì¬ì©ì ìë²ê° ì¤í ì¤ì (PID: %ld)
 %s: ì½ì´ íì¼ í¬ê¸° íëë¥¼ ì¤ì í  ì ìì, íë ëì¤í¬ ì©ë ì´ê³¼ë¡ íì©ëì§ ìì
 %s: ìë² ì¤ì§ ì¤í¨; ë¨ì¼ ì¬ì©ì ìë²ê° ì¤í ì¤ (PID: %ld)
 %s: ì¤í ê°ë¥í íë¡ê·¸ë¨ì ì°¾ì ì ììµëë¤
 %s: ì¤í ê°ë¥í postgres íë¡ê·¸ë¨ì ì°¾ì ì ìì
 %s: "%s" PID íì¼ì ì´ ì ìì: %s
 %s: "%s" ìë¹ì¤ë¥¼ ì´ ì ìì: ì¤ë¥ ì½ë %d
 %s: ìë¹ì¤ ê´ë¦¬ìë¥¼ ì´ ì ìì
 %s: "%s" íì¼ì ì½ì ì ìì
 %s: "%s" ìë¹ì¤ë¥¼ ë±ë¡í  ì ìì: ì¤ë¥ ì½ë %d
 %s: reload ìê·¸ëì ë³´ë¼ ì ìì (PID: %ld): %s
 %s: %d ìê·¸ëì ë³´ë¼ ì ìì (PID: %ld): %s
 %s: stop ìê·¸ëì ë³´ë¼ ì ìì (PID: %ld): %s
 %s: ìë²ë¥¼ ìì í  ì ìì
ë¡ê·¸ ì¶ë ¥ì ì´í´ë³´ì­ìì¤.
 %s: ìë²ë¥¼ ììí  ì ìì: ì¢ë£ ì½ë %d
 %s: "%s" ìë¹ì¤ë¥¼ ììí  ì ìì: ì¤ë¥ ë²í¸ %d
 %s: "%s" ìë¹ì¤ë¥¼ ìë¹ì¤ ëª©ë¡ìì ëº ì ìì: ì¤ë¥ ì½ë %d
 %s: "%s" PID íì¼ì ìëª»ë ê°ì´ ìì
 %s: kill ììì íìí ì¸ìê° ë¹ ì¡ìµëë¤
 %s: -D ìµìë ìê³ , PGDATA íê²½ë³ìê°ë ì§ì ëì´ ìì§ ììµëë¤.
 %s: ìíí  ììì ì§ì íì§ ìììµëë¤
 %s: ê°ë ì¤ì¸ ìë²ê° ìì
 %s: ì´ì  ìë² íë¡ì¸ì¤(PID: %ld)ê° ìì´ì¡ìµëë¤
 %s: "%s" íê²½ì¤ì íì¼ì ë°ëì í ì¤ì ê°ì ¸ì¼íë¤?
 %s: ë©ëª¨ë¦¬ ë¶ì¡±
 %s: ìë²ë¥¼ ë©ì¶ì§ ëª»íì
 %s: ìë²ê° ì¤í ì¤ì (PID: %ld)
 %s: "%s" ìë¹ì¤ê° ì´ë¯¸ ë±ë¡ ëì´ ìì
 %s: "%s" ìë¹ì¤ê° ë±ë¡ëì´ ìì§ ìì
 %s: ë¨ì¼ ì¬ì©ì ìë²ê° ì¤í ì¤ì (PID: %ld)
 %s: ëë¬´ ë§ì ëªë ¹í ì¸ìë¤ (ìì "%s")
 %s: ì ì ìë ìì ëª¨ë "%s"
 %s: ìëª»ë ì¤ì§ ë°©ë² "%s"
 %s: ìëª»ë ìê·¸ë ì´ë¦ "%s"
 (ê¸°ë³¸ ì¤ì ì ì¤ì§ í  ëë ê¸°ë¤ë¦¬ê³ , ììì´ë ì¬ììí  ëë ì ê¸°ë¤ë¦¼.)
 -D ìµìì ì¬ì©íì§ ìì¼ë©°, PGDATA íê²½ë³ìê°ì ì¬ì©í¨.
 ìë²ê° ì¤í ì¤ìëê¹?
 ë¨ì¼ ì¬ì©ì ìë²ë¥¼ ë©ì¶ê³  ë¤ì ìëíì­ìì¤.
 ìë²ê° ììëìì¼ë©° ì°ê²°ì íì©í¨
 %s íë¡ê·¸ë¨ì "postgres" íë¡ê·¸ë¨ì íìë¡ í©ëë¤. ê·¸ë°ë°, ì´ íì¼ì´
"%s" íì¼ì´ ìë ëë í°ë¦¬ ìì ììµëë¤.
ì¤ì¹ ìíë¥¼ íì¸í´ ì£¼ì­ìì¤.
 "%s" íë¡ê·¸ë¨ì "postgres" íë¡ê·¸ë¨ì ì°¾ìì§ë§ ì´ íì¼ì
%s íë¡ê·¸ë¨ì ë²ì ê³¼ íë¦½ëë¤.
ì¤ì¹ ìíë¥¼ íì¸í´ ì£¼ì­ìì¤.
 ìë² ììì ê¸°ë¤ë¦¬ë ëì ìê° ì´ê³¼ë¨
 ë³´ë¤ ìì¸í ì¬ì©ë²ì "%s --help"
 ì¬ì©ë²:
 ê²½ê³ : ì¨ë¼ì¸ ë°±ì ëª¨ëê° íì± ìíìëë¤.
pg_stop_backup()ì´ í¸ì¶ë  ëê¹ì§ ì¢ë£ê° ìë£ëì§ ììµëë¤.

 ìë²ë¥¼ ììíê¸° ìí´ ê¸°ë¤ë¦¬ë ì¤...
 íì íë¡ì¸ì¤ê° ì¢ë£ëìì, ì¢ë£ ì½ë %d íì íë¡ì¸ì¤ê° ì¢ë£ëìì, ìì ìë ìí %d 0x%X ìì¸ì²ë¦¬ë¡ íì íë¡ì¸ì¤ê° ì¢ë£ëìì íì íë¡ì¸ì¤ê° ì¢ë£ëìì, ìê·¸ë %d %s ìê·¸ë ê°ì§ë¡ íì íë¡ì¸ì¤ê° ì¢ë£ëìì "%s" ëë í°ë¦¬ë¡ ì´ë í  ì ìì ì¤íí  "%s" íì¼ì ì°¾ì ì ìì íì¬ ëë í°ë¦¬ë¥¼ ì ì ìì: %s "%s" ë°ì´ëë¦¬ íì¼ì ì½ì ì ìì "%s" ì¬ë²ë¦­ ë§í¬ë¥¼ ì½ì ì ìì ìë²ë¥¼ ìì í  ì ìì
 ìëª»ë ë°ì´ëë¦¬ íì¼ "%s" ìë²ë¥¼ ë©ì¶¥ëë¤
 ìë²ê° ìì¤í ìê·¸ëì ë°ìì
 ìë² ììë¨
 ìë²ë¥¼ ììí©ëë¤
 ìë² ë©ì¶ìì
 ì´ì§¸ë  ìë²ë¥¼ ììí©ëë¤
 ìë²ë¥¼ ë©ì¶ê¸° ìí´ ê¸°ë¤ë¦¬ë ì¤... ìë²ë¥¼ ììíê¸° ìí´ ê¸°ë¤ë¦¬ë ì¤... 
��    l      |  �   �      0	      1	     R	  &   d	     �	     �	  -   �	     �	     
  |   +
     �
  a   �
  K   *     v  A   �  !   �  3   �  ?   )  ?   i  H   �  D   �  E   7  ?   }  >   �  9   �  B   6  <   y  z   �  0   1  F   b  >   �  8   �  2   !  O   T  7   �     �     �  �   �  !   }  C   �  y   �  C   ]  D   �  >   �  A   %  *   g  /   �  %   �  /   �  #        <  3   Z  0   �  ,   �  .   �  3     -   O  0   }  5   �  "   �  $     J   ,     w     �  3   �  0   �          "  !   A  $   c      �  -   �  4   �  %     $   2  "   W  F   z  F   �       7     )   T  q   ~  f   �  %   W  &   }     �  d   �       &   0  0   W  .   �  )   �  )   �  "         .  (   O     x  !   �     �     �     �     �               )     9  "   Q     t  �  �  $   X     }  &   �  &   �  &   �  /         4      L   �   k   $   �   f   !  O   �!     �!  G   �!  "   8"  8   ["  8   �"  6   �"  E   #  =   J#  >   �#  /   �#  9   �#  ,   1$  H   ^$  ?   �$  w   �$  )   _%  A   �%  >   �%  ,   
&  !   7&  H   Y&  0   �&     �&     �&  �   �&     u'  P   �'  v   �'  Q   W(  Q   �(  G   �(  K   C)     �)  *   �)  !   �)  -   �)  !   )*     K*  -   h*  .   �*  +   �*  ,   �*  3   +  .   R+  -   �+  -   �+  $   �+     ,  6   ",     Y,      u,  2   �,  (   �,     �,     -  $    -     E-     e-  3   �-  -   �-     �-     .     $.  =   D.  :   �.     �.  :   �.  "   /  e   9/  Y   �/  "   �/  *   0     G0  a   X0     �0  !   �0  '   �0  )   $1     N1     k1     �1  !   �1      �1     �1     2      2     72     R2     i2     }2     �2     �2     �2     �2     �2               5      6         Y                      (      9   .   #          e           '   R   [   W   K   <   ]   f      B   D   &       P   H          -   %              j   
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
POT-Creation-Date: 2010-09-09 16:27+0000
PO-Revision-Date: 2010-09-24 17:06-0400
Last-Translator: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
Language-Team: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 
kill可以使用的信號名稱：
 
一般選項：
 
註冊或移除註冊可用選項：
 
啟動或重新啟動可用選項：
 
停止或重新啟動可用選項：
 
回報錯誤至<pgsql-bugs@postgresql.org>。
 
可用關閉模式：
   %s kill    信號名稱 PID
   %s register   [-N 服務名稱] [-U 使用者名稱] [-P 密碼] [-D 資料目錄]
                    [-w] [-t 秒數] [-o "選項"]
   %s reload  [-D 資料目錄] [-s]
   %s restart [-w] [-t 秒數] [-D 資料目錄] [-s] [-m 關閉模式]
                 [-o "選項"]
   %s start   [-w] [-t 秒數] [-D 資料目錄] [-s] [-l 檔名] [-o "選項"]
   %s status  [-D 資料目錄]
   %s stop    [-W] [-t 秒數] [-D 資料目錄] [-s] [-m 關閉模式]
   %s unregister [-N 服務名稱]
   --help                 顯示這份說明然後結束
   --version              顯示版本資訊然後結束
   -D, --pgdata 資料目錄  存放資料庫的目錄
   -N 服務名稱     用來註冊PostgreSQL伺服器的服務名稱
   -P 密碼         用來註冊PostgreSQL伺服器的密碼
   -U 使用者       用來註冊PostgreSQL伺服器的帳號
   -W                     不等待操作完成
   -c, --core-files       允許 postgres 產生核心檔
   -c, --core-files       此平台不適用
   -l, --log 檔名         將伺服器log寫入(或附加至)檔案。
   -m 關閉模式   可以是 "smart"、"fast" 或 "immediate"
   -o 選項             要傳給 postgres 的指令列選項
                         (PostgreSQL 伺服器執行檔)
   -p PATH-TO-POSTGRES    通常不需要
   -s, --silent           只顯示錯誤，不顯示其他訊息
   -t 秒數                使用 -w 選項時的等候秒數
   -w                     等待操作完成
   fast        直接正常關閉
   immediate   立即結束，會導致下次啟動時需要復原程序
   smart       在所有用戶端斷線後關閉
  完成
  失敗
 %s 可以用來啟動、停止、重新啟動、重新載入設定檔、
報告PostgreSQL伺服器狀態，或送信號給PostgreSQL行程。

 %s：PID檔"%s"不存在
 %s: 可能有另一個伺服器正在執行，請嘗試強制啟動此伺服器
 %s：無法以root身份執行
請以將會擁有伺服務行程的(非特權)使用者登入(例如用"su"命令)。
 %s: 無法重新載入伺服器，單一使用者伺服器正在執行 (PID:%ld)
 %s: 無法重新啟動伺服器，單一使用者伺服器正在執行 (PID:%ld)
 %s: 無法設定核心檔案大小限制，因為固定限制不允許
 %s: 無法停止伺服器，單一使用者伺服器正在執行 (PID:%ld)
 %s：找不到程式執行檔
 %s: 找不到 postgres 程式的執行檔
 %s: 無法開啟 PID 檔 "%s":%s
 %s：無法開啟服務"%s"：錯誤代碼%d
 %s：無法開啟服務管理員
 %s：無法讀取檔案"%s"
 %s：無法註冊服務"%s"：錯誤代碼%d
 %s：無法傳送reload信號(PID：%ld)：%s
 %s：無法傳送信號 %d(PID：%ld)：%s
 %s：無法傳送stop信號(PID：%ld)：%s
 %s: 無法啟動伺服器
請檢查日誌輸出。
 %s: 無法啟動伺服器: 結束代碼為 %d
 %s: 無法啟動服務 "%s": 錯誤代碼 %d
 %s：無法移除服務"%s"：錯誤代碼%d
 %s: PID 檔 "%s" 中有無效資料
 %s：kill模式未指定參數
 %s：未指定資料目錄和設定環境變數PGDATA
 %s：未指定操作方式
 %s: 沒有伺服器正在執行
 %s: 舊的伺服器程序 (PID: %ld) 似乎遺漏
 %s：選項檔"%s"只能有一行內容
 %s：記憶體用盡
 %s: 伺服器未關閉
 %s: 伺服器正在執行 (PID:%ld)
 %s：服務"%s"已經被註冊
 %s：服務"%s"未被註冊
 %s: 單一使用者伺服器正在執行 (PID:%ld)
 %s：命令列參數過多(第一個是"%s")
 %s：無效的操作模式"%s"
 %s：無效的關閉模式"%s"
 %s：無效的信號名稱"%s"
 (預設是關閉時而非啟動或重新啟動時等待。)

 如果沒有使用選項 -D，改用環境變數PGDATA。
 伺服器是否正在執行?
 請結束單一使用者伺服器，然後再試一次。
 伺服器已啟動並接受連線
 %s 需要程式 "postgres"，但是在與"%s"相同的目錄中找不到。
請檢查你的安裝。
 "%s"已找到程式"postgres"，但是與 %s 的版本不符。
請檢查你的安裝。
 等候伺服器啟動發生逾時
 執行"%s --help"以顯示更多資訊。
 使用方法：
 警告: 線上備份模式作用中
必須呼叫 pg_stop_backup()，關閉作業才能完成。

 正在等候伺服器啟動...
 子行程結束，結束代碼 %d 子行程結束，不明狀態代碼 %d 子進程被例外(exception) 0x%X 終止 子行程被信號 %d 結束 子進程被信號 %s 終止 無法切換目錄至"%s" 未能找到一個 "%s" 來執行 無法識別目前的目錄：%s 無法讀取二進制碼 "%s" 無法讀取符號連結"%s" 無法啟動伺服器
 無效的二進制碼 "%s" 伺服器正在關閉
 已通知伺服器
 伺服器已啟動
 伺服器啟動中
 伺服器已停止
 正強制啟動伺服器
 正在等候伺服器關閉... 正在等候伺服器啟動... 